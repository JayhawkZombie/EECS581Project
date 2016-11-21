#include "../../Headers/Level/Level.h"
#include <regex>

std::string RegexString_BracedText("(?<=\\{)[^\\}]*(?=\\})");

namespace Engine
{

  void Level::LoadLevelInformation(const std::string &filename)
  {
    try
    {
      std::regex BracedText(RegexString_BracedText);

    }
    catch (std::exception &e)
    {
      std::cerr << "There was an error loading the level information from the file: \"" << LevelFile << "\"" << std::endl;
      std::cerr << "The following message was reported: " << e.what() << std::endl;
    }
  }

  void Level::LoadConfigInfo(std::ifstream &_IN)
  {
    LoadingInformation.ShadersEnabled = Util::GetBooleanConfig("Config", "ShadersEnabled", true, LevelFile, _IN);
    LoadingInformation.NumLayers = Util::GetUnsignedIntConfig("Config", "NumLayers", 1, LevelFile, _IN);
    LoadingInformation.LevelSizeX = Util::GetUnsignedIntConfig("Config", "LevelSizeX", 1, LevelFile, _IN);
    LoadingInformation.LevelSizeY = Util::GetUnsignedIntConfig("Config", "LevelSizeY", 1, LevelFile, _IN);
    LoadingInformation.TileSize = Util::GetUnsignedIntConfig("Config", "TileSize", 1, LevelFile, _IN);
    LoadingInformation.TilesAcross = Util::GetUnsignedIntConfig("Config", "TilesAcross", 1, LevelFile, _IN);
    LoadingInformation.StartingView = Util::GetFloatRectConfig("Config", "StartingView", sf::FloatRect(), LevelFile, _IN);

    LoadTileInfo(_IN);
    LoadLayerInfo(_IN);
    RequestLevelData();
    SetLevelData();
  }

  void Level::LoadLayerInfo(std::ifstream &_IN)
  {
    std::string LayerTag{ "" };

    for (std::size_t layer = 0; layer < LoadingInformation.NumLayers; ++layer) {
      std::cerr << "Loading level layer: " << layer << std::endl;
      LayerTag = "Layer" + std::to_string(layer);

      LoadingInformation.LayersInfo.push_back({});
      LoadingInformation.LayersInfo[layer].Height = Util::GetUnsignedIntConfig(LayerTag, "Height", 1, LevelFile, _IN);
      LoadingInformation.LayersInfo[layer].Width = Util::GetUnsignedIntConfig(LayerTag, "Width", 1, LevelFile, _IN);
      LoadingInformation.LayersInfo[layer].RawLayout = Util::GetBracedConfig(LayerTag, "TileLayout", "{}", LevelFile, _IN);
      //std::cerr << "Raw layout: \n" << LoadingInformation.LayersInfo[layer].RawLayout << std::endl;
    }
  }

  void Level::LoadTileInfo(std::ifstream &_IN)
  {
    static std::regex_iterator<std::string::iterator> reg_end;
    static std::string Pair("(<[^>]*>)");
    static std::string PairPieces("(([^\\W,]+)(?=,)[\\W])*([\\w]+)");
    
    LoadingInformation.NumTiles = Util::GetUnsignedIntConfig("Tiles", "NumTiles", 1, LevelFile, _IN);
    std::string braced = Util::GetBracedConfig("Tiles", "Tiles", "{}", LevelFile, _IN);

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
        if (pieces->size() % 2 != 0) {
          std::cerr << "Error: Invalid number of items found when parsing string tile info" << std::endl;
          return;
        }

        while (pieces != RegEnd) {
          //First (layout ID)
          std::string p1 = pieces->str();
          ++pieces;

          std::string p2 = pieces->str();
          ++pieces;

          LoadingInformation.LayoutIDToTileID[p1] = p2;
        }

        reg_iter++;
      } //end while
    }
    catch (std::exception &e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }
    LoadTilesData(_IN);
  }

  void Level::LoadObjectData(std::ifstream &_IN)
  {

  }

  void Level::LoadLayoutInfo(std::ifstream &_IN)
  {

  }

  void Level::LoadLayerData(std::ifstream &_IN)
  {

  }

  void Level::LoadTilesData(std::ifstream &_IN)
  {
    std::size_t pos = 0;
    std::regex_iterator<std::string::iterator> regend;
    for (auto & pair : LoadingInformation.LayoutIDToTileID) {
      std::string Tag = pair.second;
      std::string LayoutID = pair.first;

      LoadingInformation.TileInfos.push_back({});
      
      std::string FilePath = Util::GetStringConfig(Tag, "FilePath", "", LevelFile, _IN);
      bool _trav = Util::GetBooleanConfig(Tag, "Traversable", false, LevelFile, _IN);
      bool _anim = Util::GetBooleanConfig(Tag, "Animated", false, LevelFile, _IN);
      std::size_t _framecnt = Util::GetUnsignedIntConfig(Tag, "NumFrames", 1, LevelFile, _IN);
      std::string FrameList = Util::GetBracedConfig(Tag, "Frames", "{}", LevelFile, _IN);

      LoadingInformation.TileInfos[pos].FilePath = FilePath;
      LoadingInformation.TileInfos[pos].TileID = Tag;
      LoadingInformation.TileInfos[pos].LayoutID = LayoutID;
      LoadingInformation.TileInfos[pos].Traversible = _trav;
      LoadingInformation.TileInfos[pos].Animated = _anim;

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

          LoadingInformation.TileInfos[pos].TextureRect = rect;
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

            LoadingInformation.TileInfos[pos].AnimationFrames.push_back(rect);
          }
        } //else (from if animated)
        ++pos;
      }
      catch (std::exception &e)
      {
        std::cerr << "Error parsing tile data: " << e.what() << std::endl;
      }
    }
  }

  void Level::RequestLevelData()
  {
    for (auto & tile : LoadingInformation.TileInfos) {
      ResourceManager->RequestTexture(tile.FilePath, tile.TileID,
                                      [this](std::shared_ptr<sf::Texture> t, const std::string &s)
      {
        if (this->TileIDToTexture.find(s) == TileIDToTexture.end())
          this->TileIDToTexture[s] = t;
      }
      );
    }
  }

  void Level::FormalizeLayerLayouts()
  {
    for (auto & layer : LoadingInformation.LayersInfo) {
      std::string *str = &layer.RawLayout;
      str->erase(str->begin());
      str->erase(str->back());

      std::stringstream SS(*str);

      std::string temp{ "" };
      while (SS >> temp) {
        layer.LayerLayout.push_back(temp);
      }

    }
  }

  void Level::SetLevelData()
  {
    FormalizeLayerLayouts();

    for (std::size_t layer = 0; layer < Environment.Layers.size(); ++layer) {
      Environment.Layers.push_back({});

      
      std::size_t SizeX = LoadingInformation.LayersInfo[layer].Width;
      std::size_t SizeY = LoadingInformation.LayersInfo[layer].Height;
      std::string LayoutID = "";
      std::string TileID = "";

      auto *_layer = &Environment.Layers[layer];
      GridCell *cell = nullptr;

      for (std::size_t _y = 0; _y < SizeY; ++_y) {
        for (std::size_t _x = 0; _x < SizeX; ++_x) {
          LayoutID = LoadingInformation.LayersInfo[layer].RawLayout[LoadingInformation.LevelSizeX * _y + _x];
          TileID = LoadingInformation.LayoutIDToTileID[LayoutID];

          if (_y < _layer->Grid.MatHeight && _x < _layer->Grid.MatWidth) {
            cell = &_layer->Grid.Mat[_y][_x];

            if (cell) {
              _layer->Grid.Mat[_y][_x].LevelPosition = sf::Vector2f(_x * LoadingInformation.TileSize, _y * LoadingInformation.TileSize);
              _layer->Grid.Mat[_y][_x].BGTile.TileID = TileID;
            }
          } // if (_y < height && _x < width)


        } //for _x = 0 -> SizeX
      } //for _y = 0 -> SizeY


    } //for layer = 0 -> Env.Layers.size


  }

}
