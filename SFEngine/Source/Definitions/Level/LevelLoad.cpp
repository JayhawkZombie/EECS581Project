#include "../../Headers/Level/Level.h"

namespace
{
  std::map<std::string, std::shared_ptr<sf::Texture>> IDToTexture;
  std::size_t numTextures = 0;
  std::size_t texsReceived = 0;
  std::pair<std::string, std::string> *Maps;
  std::size_t numLayers = 0;
  std::size_t currentLayer = 0;
  std::size_t tileWidth, tileHeight;
  std::size_t tileSizeX, tileSizeY;
  std::string **Layout;
  bool ReadyToDraw = false;
}

namespace Engine
{


  void Level::ReceiveTexture(const std::string &ID, std::shared_ptr<sf::Texture> texture)
  {
    IDToTexture[ID] = texture;
    ++texsReceived;

    tileSizeY = texture.get()->getSize().y;
    tileSizeX = texture.get()->getSize().x;

    if (texsReceived == numTextures) {
      ReadyToDraw = true;
      if (LOADER.joinable())
        LOADER.join();
      __DrawTiles();
      delete[] Maps;
    }
  }

  void Level::__DrawTiles()
  {
    BackgroundLayer.BackgroundTexture.create(
      tileSizeX * tileWidth, tileSizeY * tileHeight
    );

    sf::Sprite spr;
    BackgroundLayer.BackgroundTexture.clear();

    for (std::size_t ROW = 0; ROW < tileWidth; ++ROW) {
      for (std::size_t COL = 0; COL < tileHeight; ++COL) {
        spr.setPosition(sf::Vector2f(tileSizeX * COL, tileSizeY * ROW));
        if (IDToTexture[Layout[ROW][COL]].get()) {
          spr.setTexture(*IDToTexture[Layout[ROW][COL]]);
          BackgroundLayer.BackgroundTexture.draw(spr);
        }
      } //end COL
    }//end ROW

    BackgroundLayer.BackgroundTexture.display();
    BackgroundLayer.BGSprite->setTexture(BackgroundLayer.BackgroundTexture.getTexture());
    BackgroundLayer.BGSprite->setTextureRect(sf::IntRect(0, 0, tileSizeX * tileWidth, tileSizeY * tileHeight));
    sf::Vector2f scale;
    scale.x = (WindowSize.x) / (tileSizeX * tileWidth);
    scale.y = (WindowSize.y) / (tileSizeY * tileHeight);
    BackgroundLayer.BGSprite->setScale(scale);

    Playable = true;

    for (std::size_t ROW = 0; ROW < tileHeight; ++ROW) {
      delete[] Layout[ROW];
    }
    delete[] Layout;
    IDToTexture.clear();
  } //__DrawTiles()

  void Level::LoadLevel()
  {

    LOADER = std::thread(
      [this]() { this->__LoadLevel(); }
    );
    //__LoadLevel();
  }

  void Level::__LoadLevel()
  {
    std::ifstream IN(LevelFile);
    if (!IN) {
      std::cerr << "Error. Failure opening level file: \"" << LevelFile << "\"" << std::endl;
      return;
    }

    //Read in the number of Layers we will have
    numLayers = Util::GetUnsignedIntConfig("Config", "NumLayers", 1, LevelFile, IN);

    std::string layerstring = "Layer";
    __ReadLoadTextures(0, IN);

  }

  void Level::__LoadLayout(std::ifstream &IN)
  {
    std::string bracedtext = Util::GetBracedConfig("Layer0/Layout", "TileLayout", "{}", "testmap.ini", IN);

    std::size_t TilesAcross = Util::GetUnsignedIntConfig("Layer0/Layout", "Width", 0, "testmap.ini", IN);
    std::size_t TilesUp = Util::GetUnsignedIntConfig("Layer0/Layout", "Height", 0, "testmap.ini", IN);

    tileHeight = TilesUp;
    tileWidth = TilesAcross;

    Layout = new std::string*[TilesUp]; //RowCount
    for (std::size_t COL = 0; COL < TilesUp; ++COL) {
      Layout[COL] = new std::string[TilesAcross];
    }

    bracedtext.erase(0, 1);
    bracedtext.erase(bracedtext.size() - 1);

    std::stringstream stream(bracedtext);
    std::string temp;
    std::size_t currRow{ 0 }, currCol{ 0 };

    while (stream >> temp) {
      Layout[currRow][currCol] = temp;
      ++currCol;

      if (currCol == TilesAcross) {
        ++currRow;
        currCol = 0;
      }
    }
  }

  void Level::__ReadLoadTextures(const std::size_t &layer, std::ifstream &IN)
  {
    std::string layerstring = "Layer" + std::to_string(layer);
    std::size_t texCount = Util::GetUnsignedIntConfig(layerstring + "/Textures", "NumTextures", 0, LevelFile, IN);
    numTextures = texCount;

    std::string bracedText = Util::GetBracedConfig(layerstring + "/Textures", "Textures", "{}", LevelFile, IN);
    Maps = new std::pair<std::string, std::string>[texCount];

    std::size_t currentPos = 0;
    std::size_t beg, end;
    for (int i = 0; i < texCount; i++) {
      //Get position of the end of the "pair", ie the string <...>
      beg = bracedText.find_first_of("<", currentPos + 1);
      end = bracedText.find_first_of(">", beg + 1);

      Maps[i] = Util::GetPairText(bracedText, beg);
      currentPos = bracedText.find_first_of(",", end + 1);

      ResourceManager->RequestTexture(
        Maps[i].second, Maps[i].first,
        [this](std::shared_ptr<sf::Texture> t, const std::string &ID) {this->ReceiveTexture(ID, t); }
      );
    }

    __LoadLayout(IN);

    return;
  }

}