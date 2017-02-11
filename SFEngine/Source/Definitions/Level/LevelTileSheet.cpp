#include "../../Headers/Level/Level.h"

namespace Engine
{

  std::shared_ptr<TileSheet> TileSheet::Decode(std::ifstream &in)
  {
    //Read the path to the texture first

    //Read the length of the string representing the path
    std::string path = "";
    DeserializeString(path, in);
    if (path.empty() || path.find('.') == std::string::npos)
      throw FormattingError({ ExceptionCause::DataParseError }, EXCEPTION_MESSAGE("Failed to parse path for tile sheet"));

    //Now get the number of frames
    std::uint32_t FrameCount = 0;
    DeserializeUint32(FrameCount, in);

    if (FrameCount > MaxTilesPerSheet)
      throw ValueException({ ExceptionCause::ValueTooLarge }, EXCEPTION_MESSAGE("Frame count exceeds maximum allowed per sheet"));

    std::string tilename{ "" };
    float Left{ 0 }, Top{ 0 }, Width{ 0 }, Height{ 0 };
    std::uint32_t MeshType = 0;
    sf::Vertex TopLeft, TopRight, BottomRight, BottomLeft;
    sf::VertexArray TileRect = sf::VertexArray(sf::Quads, 4);

    std::map<std::string, sf::VertexArray> Tiles;
    for (std::uint32_t count = 0; count < FrameCount; ++count) {
      //read the name for the tile
      DeserializeString(tilename, in);
      if (tilename.empty())
        throw FormattingError({ ExceptionCause::DataParseError }, EXCEPTION_MESSAGE("Tile name is empty"));

      DeserializeFloat(Left, in);
      DeserializeFloat(Top, in);
      DeserializeFloat(Width, in);
      DeserializeFloat(Height, in);
      DeserializeUint32(MeshType, in);

      //OK, add this to the map
      TopLeft.texCoords = { Left, Top };
      TopRight.texCoords = { Left + Width, Top };
      BottomRight.texCoords = { Left + Width, Top + Height };
      BottomLeft.texCoords = { Left, Top + Height };

      TileRect[0].texCoords = TopLeft.texCoords;
      TileRect[1].texCoords = TopRight.texCoords;
      TileRect[2].texCoords = BottomRight.texCoords;
      TileRect[3].texCoords = BottomLeft.texCoords;

      Tiles[tilename] = TileRect;
    }

    std::shared_ptr<sf::Texture> Texture = std::make_shared<sf::Texture>();
    if (!Texture->loadFromFile(path))
      throw ConstructionException({ ExceptionCause::ConstructionError }, EXCEPTION_MESSAGE("Failed to load tile sheet texture"));

    std::shared_ptr<TileSheet> Sheet = std::make_shared<TileSheet>();
    Sheet->Sheet = Texture;
    Sheet->Tiles = Tiles;

    return Sheet;
  }

  void TileSheet::GenerateBlankSheet(float SizeX, float SizeY, float CellSizeX, float CellSizeY)
  {
    float xpos = 0.f, ypos = 0.f;

    sf::VertexArray varr = sf::VertexArray(sf::Quads, 4);

    while (ypos <= SizeY) {
      while (xpos <= SizeX) {
        varr[0].position = { xpos, ypos };
        varr[1].position = { xpos + CellSizeX, ypos };
        varr[2].position = { xpos + CellSizeX, ypos + CellSizeY };
        varr[3].position = { xpos, ypos + CellSizeY };

        RenderedVerts.append(varr[0]);
        RenderedVerts.append(varr[1]);
        RenderedVerts.append(varr[2]);
        RenderedVerts.append(varr[3]);
      }
    }
  }
  
}
