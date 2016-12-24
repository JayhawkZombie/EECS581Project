#ifndef SFENGINE_LEVEL_TILE_H
#define SFENGINE_LEVEL_TILE_H


#include "LevelObject.h"
#include "../Actor/Player.h"
#include "../Lights/GenericLightSource.h"
#include "../Lights/GlobalLightSource.h"
#include "../Utils/SpriteSheet.h"


namespace Engine
{

  class LevelTile : public LevelObject
  {
  public:
    LevelTile();
    ~LevelTile();

    void Render();
    void TickUpdate(const double &delta);
    void OnShutDown();
    void SerializeOut(std::ostream &out);

    void SetISAnimated(bool anim);
    void SetIsTraversible(bool trav);
    void SetTextureFrameIndices(std::vector<std::size_t> frames);
    std::vector<std::size_t> GetFrameIndices() const;

    void SetTileSheet(std::shared_ptr<SpriteSheet> sheet);
    std::shared_ptr<SpriteSheet> GetTileSheet() const;

    bool GetIsAnimated() const;
    bool GetIsTraversible() const;

  private:
    std::shared_ptr<SpriteSheet> TileSheet;
    std::vector<std::size_t> FrameIndices;

    bool IsAnimated;
    bool IsTraversible;
    double AnimationDuration;
    double FrameTime;
    double CurrentAnimationDuration;
    std::size_t CurrentFrame;
    std::string LayoutID;
  };
  
}


#endif
