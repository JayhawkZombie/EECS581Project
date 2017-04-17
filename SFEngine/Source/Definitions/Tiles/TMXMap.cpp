#include "Tiles\TMXMap.h"

namespace Engine
{

  namespace TMX
  {

    /*
      TMX MAP
    */

    Map::Map(const std::string & file)
    {
      std::ifstream in(file);
      if (!in) {
        throw StreamException({ ExceptionCause::StreamFailure }, EXCEPTION_MESSAGE("Failed to open json"));
      }

      Json::Value JsonDoc;
      in >> JsonDoc;

      m_Height      = JsonDoc["height"].asUInt();
      m_Width       = JsonDoc["width"].asUInt();
      m_Orientation = JsonDoc["orientation"].asString();
      m_RenderOrder = JsonDoc["renderorder"].asString();

      auto tile_sheets_count = JsonDoc["tilesets"].size();

      m_TileSets.reserve(tile_sheets_count);
      for (std::size_t i = 0; i < tile_sheets_count; ++i) {
        m_TileSets.push_back({});
        m_TileSets.back().Parse(JsonDoc["tilesets"][i]);
      }
    }

    Map::~Map()
    {
    }

    /*
      TMX LAYER
    */
    Layer::Layer(const Json::Value &JsonDoc, std::vector<Engine::TMX::TileSet> &TileSets)
    {

    }

    /*
      TMX TILE SET
    */

    void TileSet::Parse(const Json::Value & JsonDoc)
    {
      m_Columns     = JsonDoc["columns"].asUInt();
      m_FirstGid    = JsonDoc["firstgid"].asUInt();
      m_Image       = JsonDoc["image"].asString();
      m_ImageHeight = JsonDoc["imageheight"].asUInt();
      m_ImageWidth  = JsonDoc["imagewidth"].asUInt();
      m_Name        = JsonDoc["name"].asString();
      m_TileHeight  = JsonDoc["tileheight"].asUInt();
      m_TileWidth   = JsonDoc["tilewidth"].asUInt();
      m_TileCount   = JsonDoc["tilecount"].asUInt();
      m_Texture     = Engine::LoadTexture(m_Image, m_Image);

      InitTileInfo();
      ParseTileProperties(JsonDoc);
    }

    void TileSet::InitTileInfo()
    {

      unsigned int tiles_across = (unsigned int)(m_ImageWidth / m_TileWidth);
      unsigned int tiles_high = (unsigned int)(m_ImageHeight / m_TileHeight);

      int left = 0, top = 0;
      
      int tile_idx = m_FirstGid;

      for (unsigned int i = 0; i < m_TileCount; ++i, ++tile_idx) {
        m_Tiles[tile_idx] = {};
        m_Tiles[tile_idx].m_GlobalID = tile_idx;

        m_Tiles[tile_idx].m_TexCoords = sf::IntRect(left, top, m_TileWidth, m_TileHeight);
        
        if (left > m_TileWidth) {
          left = 0;
          top += m_TileHeight;
        }
        if (top > m_TileHeight)
          top = 0;

        left += m_TileWidth;
      }

    }

    void TileSet::ParseTileProperties(const Json::Value & JsonDoc)
    {
      /*
        If this tileset has "tiles" as a memebr, it has custom properties
      */
      if (JsonDoc.isMember("tiles")) {

        auto size = JsonDoc["tiles"].size();

        /*
          Then for each tile listen in this array, parse the custom properties
        */
        for (int i = 0; i < size; ++i) {
          if (JsonDoc["tiles"][i].isMember("animation"))
            ParseAnimatedTile(JsonDoc["tiles"][i], this);
        }

      }

    }

    void TileSet::ParseAnimatedTile(const Json::Value & JsonDoc, TileSet * set)
    {
      unsigned int tile_idx = JsonDoc.asUInt();
      auto frame_count = JsonDoc["animation"].size();

      set->m_Tiles[tile_idx].m_IsAnimated = true;
      set->m_Tiles[tile_idx].m_AnimationFrames.reserve(frame_count);

      unsigned int duration = 0;
      unsigned int anim_tile_id = 0;

      for (int i = 0; i < frame_count; ++i) {
        duration     = JsonDoc["animation"][i]["duration"].asUInt();
        anim_tile_id = JsonDoc["animation"][i]["tileid"].asUInt();
      }

    }

  }

}
