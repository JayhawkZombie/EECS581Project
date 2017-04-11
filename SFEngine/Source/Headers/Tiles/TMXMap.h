#ifndef SFENGINE_TMX_MAP_H
#define SFENGINE_TMX_MAP_H

#include "../../../ThirdParty/json/json.h"

#include "../BasicIncludes.h"

namespace
{
  std::map<std::string, unsigned int> TexToID;
}

namespace Engine
{

  namespace TMX
  {

    struct TileAnimationFrame {
      double       m_Duration;
      unsigned int m_Frame;
    };

    class Tile
    {
    public:
      sf::IntRect  m_TexCoords;
      unsigned int m_GlobalID;
      bool         m_IsAnimated = false;
      std::vector<TileAnimationFrame> m_AnimationFrames;
    };

    class TileSet
    {
    public:
      TileSet() = default;

      void Parse(const Json::Value &JsonDoc);
      void InitTileInfo();
      void ParseTileProperties(const Json::Value &JsonDoc);
    protected:
      static void ParseAnimatedTile(const Json::Value &JsonDoc, TileSet *set);


      std::string  m_Name;
      unsigned int m_Columns;
      unsigned int m_FirstGid;
      std::string  m_Image;
      unsigned int m_ImageHeight;
      unsigned int m_ImageWidth;
      unsigned int m_TileCount;
      unsigned int m_TileHeight;
      unsigned int m_TileWidth;
      std::shared_ptr<sf::Texture> m_Texture;
      std::map<unsigned int, Engine::TMX::Tile> m_Tiles;
    };

    /*
      Layer - Holds the layout of the tiles

      A Layer will contain static tiles (non-animated) and
        dynamic tiles (animated)
      The static tiles never need to be updated, and only the animated tiles will be updated every frame.

      A mapping will exist from every known texture alias to the tiles on this layer that use tiles from that alias
      Another mapping will hold the grunt of the data about every individual tile
    */
    class Layer
    {
    public:
      Layer() = delete;
      Layer(const Json::Value &JsonDoc, std::vector<Engine::TMX::TileSet> &TileSets);
      ~Layer();

    protected:
      /*
        This is what will be rendered, for each texture alias known
        -- Every texture alias loaded is given an ID and this will map from that 
           to a sf::VertexArray containing the position and texcoords for every
           tile to be rendered from that alias on this layer

           If a tile is animated, that tile will be aware of where it is in that array and will be able to update itself
      */
      std::map<unsigned int, sf::VertexArray> m_TexToTiles;

      /*
        We will map from the global id given to each tile to the tile itself
      */
      std::map<unsigned int, Engine::TMX::Tile> m_Tiles;

      /*
        We will maintain a set of tiles that are animated
          This way we can iterate over only these tiles and update only those that we absolutely have to update
      */
      std::set<unsigned int> m_AnimatedTiles;
    };

    class Map
    {
    public:
      Map() = delete;
      Map(const std::string &file);
      ~Map();

    protected:
      unsigned int m_Height;
      unsigned int m_Width;
      std::string  m_Orientation = "orthogonal";
      std::string  m_RenderOrder = "left-down";

      std::vector<Engine::TMX::TileSet> m_TileSets;
    };

  }

}

#endif
