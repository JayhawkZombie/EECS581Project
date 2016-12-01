#include "../../Headers/Level/LevelLoader.h"
#include <regex>

namespace Engine
{

  LevelLoader::LevelLoader()
  {
    LayoutIDToTileID = new std::map<std::string, std::string>;
    TileIDs = new std::vector<std::string>;
    TileIDToTexture = new std::map<std::string, std::shared_ptr<sf::Texture>>;
    Lock = new std::mutex;
    FailedToLoad = false;
  }

  LevelLoader::~LevelLoader()
  {
    JoinThread();

    delete LayoutIDToTileID;
    delete TileIDs;
    delete TileIDToTexture;
    delete Lock;
  }

  void LevelLoader::Load(const std::string &lvlfile)
  {
    LevelFile = lvlfile;

    LoadLevelInformation(lvlfile);
  }

  void LevelLoader::JoinThread()
  {
    if (LOADER_THREAD.joinable())
      LOADER_THREAD.join();
  }

  bool LevelLoader::DoneLoading() const
  {
    return IsDoneSettingData;
  }

  void LevelLoader::LoadLevelInformation(const std::string &filename)
  {
    LevelFile = filename;

    LOADER_THREAD = std::thread(
      [this, filename]() {
      std::ifstream in(filename);
      this->LoadConfigInfo(in);
    }
    );
  }

  void LevelLoader::LoadFailure(std::ifstream &infile)
  {
    std::cerr << "Failure loading level. Able to read up to: " << infile.tellg() << std::endl;

    Lock->lock();
    TileIDs->clear();
    LayoutIDToTileID->clear();

    for (auto & tex : *TileIDToTexture)
      tex.second.reset();

    TileIDToTexture->clear();
    Lock->unlock();

    infile.clear();
    infile.close();
  }

  void LevelLoader::LoadConfigInfo(std::ifstream &infile)
  {
    if (infile.fail()) {
      LoadFailure(infile);
      return;
    }

    //Get the config info for the entire level
    ShadersEnabled = Util::GetBooleanConfig("Config", "ShadersEnabled", true, LevelFile, infile);
    NumLayers = Util::GetUnsignedIntConfig("Config", "NumLayers", 1, LevelFile, infile);
    LevelSizeX = Util::GetUnsignedIntConfig("Config", "LevelSizeX", 1, LevelFile, infile);
    LevelSizeY = Util::GetUnsignedIntConfig("Config", "LevelSizeY", 1, LevelFile, infile);
    TileSize = Util::GetUnsignedIntConfig("Config", "TileSize", 1, LevelFile, infile);
    TilesAcross = Util::GetUnsignedIntConfig("Config", "TilesAcross", 1, LevelFile, infile);
    StartingView = Util::GetFloatRectConfig("Config", "StartingView", sf::FloatRect(), LevelFile, infile);

    Scale.x = WindowSize.x / (TileSize * TilesAcross);
    Scale.y = WindowSize.y / (TileSize * TilesAcross);

    LoadTileInfo(infile);
    LoadLayerInfo(infile);
    LoadLayoutInfo(infile);
    FormalizeLayerLayouts();
    RequestLevelData();
    SetLevelData();
    DebugPrintData();
  }

  void LevelLoader::LoadLayerInfo(std::ifstream &infile)
  {

  }

  void LevelLoader::LoadTileInfo(std::ifstream &infile)
  {
    //Regexs to use for parsing
    static std::regex_iterator<std::string::iterator> reg_end;
    static std::string Pair("(<[^>]*>)");
    static std::string PairPieces("(([^\\W,]+)(?=,)[\\W])*([\\w]+)");

    NumTiles = Util::GetUnsignedIntConfig("Tiles", "NumTiles", 1, LevelFile, infile);
    std::string braced = Util::GetBracedConfig("Tiles", "Tiles", "{}", LevelFile, infile);

    try
    {
      static std::regex PairsText(Pair);
      static std::regex PairsPiecesMatch(PairPieces);

      std::regex_iterator<std::string::iterator> reg_iter(braced.begin(), braced.end(), PairsText);
      std::regex_iterator<std::string::iterator> RegEnd;

      while (reg_iter != RegEnd) {
        std::string str(reg_iter->str());

        std::regex_iterator<std::string::iterator> pieces(str.begin(), str.end(), PairsPiecesMatch);

        //There should always be an even number of these
        //They look like <LayoutID, TileID>
        if (pieces->size() % 2 != 0) {
          std::cerr << "Error: Invalid number of items found when parsing string tile info" << std::endl;
          return;
        }

        while (pieces != RegEnd) {
          //First (layout ID)
          std::string p1 = pieces->str();
          ++pieces;
          //Second(tile ID)
          std::string p2 = pieces->str();
          ++pieces;

          (*LayoutIDToTileID)[p1] = p2;
        }

        reg_iter++;
      } //end while
      
    }
    catch (std::exception &e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
      LoadFailure(infile);
      return;
    }
    LoadTilesData(infile);
  }

  void LevelLoader::LoadTilesData(std::ifstream &infile)
  {
    std::size_t pos = 0;
    std::regex_iterator<std::string::iterator> regend;
    for (auto & pair : *LayoutIDToTileID) {
      std::string Tag = pair.second;
      std::string LayoutID = pair.first;

      std::string FilePath = Util::GetStringConfig(Tag, "FilePath", "", LevelFile, infile);
      bool _trav = Util::GetBooleanConfig(Tag, "Traversable", false, LevelFile, infile);
      bool _anim = Util::GetBooleanConfig(Tag, "Animated", false, LevelFile, infile);
      std::size_t _framecnt = Util::GetUnsignedIntConfig(Tag, "NumFrames", 1, LevelFile, infile);
      std::string FrameList = Util::GetBracedConfig(Tag, "Frames", "{}", LevelFile, infile);

      TileInfos.push_back({});

      TileInfos[pos].FilePath = FilePath;
      TileInfos[pos].TileID = Tag;
      TileInfos[pos].LayoutID = LayoutID;
      TileInfos[pos].Tranversible = _trav;
      TileInfos[pos].IsAnimated = _anim;

      TileInformation.emplace(
        std::piecewise_construct,
        std::make_tuple(Tag),
        std::make_tuple(TileInfos[pos])
      );

      try
      {
        std::string vecstr("([0-9]+)");
        std::regex vecreg(vecstr);

        if (!_anim) {
          //only one item should be in that list
          std::regex_iterator<std::string::iterator> iter(FrameList.begin(), FrameList.end(), vecreg);
          sf::IntRect rect;

          while (iter != regend) {
            rect.left = std::stoul(iter->str());
            rect.top = std::stoul(iter->str());
            rect.width = std::stoul(iter->str());
            rect.height = std::stoul(iter->str());
            ++iter;
          }

          TileInfos[pos].TextureRect = rect;
        } //if animated
        else {
          std::regex_iterator<std::string::iterator> iter(FrameList.begin(), FrameList.end(), vecreg);
          sf::IntRect rect;

          //Every 4 of these should equate to a vector
          while (iter != regend) {
            rect.left = std::stoul(iter->str()); ++iter;
            rect.top = std::stoul(iter->str()); ++iter;
            rect.width = std::stoul(iter->str()); ++iter;
            rect.height = std::stoul(iter->str()); ++iter;

            TileInfos[pos].Frames.push_back(rect);
          }
        } //else (from if animated)
        ++pos;
      }
      catch (std::exception &e)
      {
        std::cerr << "Error parsing tile data: " << e.what() << std::endl;
        LoadFailure(infile);
        return;
      }
    }
  }

  void LevelLoader::LoadLayoutInfo(std::ifstream &infile)
  {
    std::string LayerTag{ "" };

    for (std::size_t layer = 0; layer < NumLayers; ++layer) {
      std::cerr << "Loading level layer: " << layer << std::endl;
      LayerTag = "Layer" + std::to_string(layer);

      LayersInfo.push_back({});
      LayersInfo[layer].Height = Util::GetUnsignedIntConfig(LayerTag, "Height", 1, LevelFile, infile);
      LayersInfo[layer].Width = Util::GetUnsignedIntConfig(LayerTag, "Width", 1, LevelFile, infile);
      LayersInfo[layer].RawLayout = Util::GetBracedConfig(LayerTag, "TileLayout", "{}", LevelFile, infile);
    }
  }

  void LevelLoader::RequestLevelData()
  {
    for (auto & tile : TileInfos) {
      ResourceManager->RequestTexture(tile.FilePath, tile.TileID,
                                      [this](std::shared_ptr<sf::Texture> t, const std::string &s)
      {
        if (this->TileIDToTexture->find(s) == TileIDToTexture->end()) {
          (*this->TileIDToTexture).operator[](s) = t; //Because the syntax doesn't want to work, so screw it
          this->NumTexturesReceived++;
        }
          
      }
      );
    }
  }

  void LevelLoader::FormalizeLayerLayouts()
  {
    /*
      Take the layer from looking like "T T O L O WLF S S F S QW TR W Q F G"
      to looking like
      T T O L WLF
      S S F S QW 
      ...
    */

    for (std::size_t i = 0; i < NumLayers; ++i) {
      std::stringstream SS(LayersInfo[i].RawLayout);

      std::string temp;

      std::vector<std::string> V;
      V.resize(LayersInfo[i].Width);
      LayersInfo[i].FormalLayout.reserve(LayersInfo[i].Height);

      //Gotta fix this
      int x = 0, y = 0;
      while (SS >> temp) {
        V.push_back(temp);
        ++x;

      if (x >= LayersInfo[i].Width) {
        x = 0;
        ++y;
        LayersInfo[i].FormalLayout.push_back(V);
      }
      }


    }

  }

  void LevelLoader::ReceiveLevelTexture(std::shared_ptr<sf::Texture> texture, const std::string &ID)
  {

  }

  void LevelLoader::SetLevelData()
  {
    while (NumTexturesReceived < NumTiles) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (auto & tile : TileInfos) {
      auto it = TileIDToTexture->find(tile.TileID);
      if (it != TileIDToTexture->end()) {
        tile.Texture = (*TileIDToTexture)[tile.TileID];
      }
    }

    for (std::size_t i = 0; i < NumLayers; ++i) {
      Layers.push_back(std::shared_ptr<Engine::LoaderLayer>(new Engine::LoaderLayer));

      //Eww, why? Maybe reconsider this...
      Layers[i]->Tiles = std::shared_ptr<std::vector<std::vector<LevelTileResource>>>(new std::vector<std::vector<LevelTileResource>>);
      Layers[i]->Tiles->resize(NumTiles);

      std::string TileLayoutID, TileID;

      std::vector<LevelTileResource> tilevector;

      tilevector.resize(NumTiles);
      //Oh no
      for (std::size_t y = 0; y < LayersInfo[i].Height; ++y) {
        //Clear the vector (but keep the pre-allocated memory space)
        tilevector.clear();

        for (std::size_t x = 0; x < LayersInfo[i].Width; ++x) {
          //Get the LayoutID and use that to get the TileID (so we can get the texture from the manager)
          TileLayoutID = LayersInfo[i].FormalLayout[y][x];
          TileID = (*LayoutIDToTileID)[TileLayoutID];

          //UGH, oh god it looks so horrible
          //IF the we were able to find the tile in our known tiles, then we can create the renderable tile
          auto it = TileInformation.find(TileID);
          if (it != TileInformation.end()) {

            LevelTileResource tile(new LevelTile{ 
              it->second.TileID, 
              it->second.Texture, 
              it->second.IsAnimated, 
              it->second.Frames, 
              sf::Vector2f(TileSize, TileSize), 
              sf::Vector2f(TileSize * x, TileSize * y), 
              it->second.AnimationDuration }
            );

            //Set the attributes
            //tile->SetAnimationDuration(it->second.AnimationDuration);
            //tile->SetID(it->second.TileID); 
            //tile->SetPosition(sf::Vector2f(TileSize * x, TileSize *y));
            //tile->SetTexture(it->second.Texture);
            //tile->SetTextureFrames(it->second.Frames);
            //tile->CreateSprite();

            tilevector.push_back(tile);
            //I'm so sorry
            //auto ptr = Layers[i]->Tiles.get();
            //(*ptr)[y][x]->SetAnimationDuration(it->second.AnimationDuration);
            //(*ptr)[y][x]->SetID(it->second.TileID);
            //(*ptr)[y][x]->SetPosition(sf::Vector2f(TileSize * x, TileSize * y));
            //(*ptr)[y][x]->SetSize(sf::Vector2f(TileSize, TileSize));
            //(*ptr)[y][x]->SetTexture(it->second.Texture);
            //(*ptr)[y][x]->SetTextureFrames(it->second.Frames);
            //(*ptr)[y][x]->CreateSprite();
          } //if (it != TileInformation.end())
        } //for x = 0 -> Width

        //Add the vector of tiles for the current row to the Tiles for the layer
        Layers[i]->Tiles->push_back(tilevector);
      } //For y = 0 -> Height
    }

    IsDoneSettingData = true;
  }

  void LevelLoader::LoadLayerData(std::ifstream &infile)
  {

  }

  void LevelLoader::LoadObjectData(std::ifstream &infile)
  {

  }

  void LevelLoader::LoadLights(std::ifstream &infile)
  {

  }

  void LevelLoader::LoadVolumes(std::ifstream &infile)
  {

  }

  void LevelLoader::LoadActors(std::ifstream &infile)
  {

  }

  void LevelLoader::DebugPrintData()
  {

    std::cerr << "Level data loaded: \n";
    std::cerr << "NumLayers: " << NumLayers << "\n";
    std::cerr << "NumTiles: " << NumTiles << "\n";
    std::cerr << "LevelSize: " << LevelSizeX << " by " << LevelSizeY << std::endl;

    for (auto & layer : LayersInfo) {
      std::cerr << "\tLayer: \n";

      for (int x = 0; x < LevelSizeX; ++x) {
        std::cerr << "\t";
        for (int y = 0; y < LevelSizeY; ++y) {
          std::cerr << layer.FormalLayout[y][x] << " ";
        }
        std::cerr << std::endl;
      }

    }

    std::cerr << "Tile Data: \n";

    for (auto & tile : TileInformation) {
      std::cerr << "TileID: " << tile.second.TileID << "\n";
      std::cerr << "LayoutID: " << tile.second.LayoutID << "\n";
      std::cerr << "Animated: " << (tile.second.IsAnimated ? "True" : "False") << "\n";
      std::cerr << "Traversible: " << (tile.second.Tranversible ? "True" : "False") << "\n";
      std::cerr << "Frames: ";
      for (auto & frame : tile.second.Frames)
        std::cerr << "(" << frame.left << ", " << frame.top << ", " << frame.width << ", " << frame.height << ") ";
    }

  }

  void LevelLoader::TestRender()
  {
    if (!IsDoneSettingData)
      return;

    for (auto & layer : Layers) {
      
      for (auto i = 0; i < LayersInfo[0].Height; ++i) {
        for (auto j = 0; j < LayersInfo[0].Width; ++j) {
          
          Render::RenderSprite((*layer->Tiles)[i][j]->GetSpritePtr());

        }
      }

    }
  }
}
