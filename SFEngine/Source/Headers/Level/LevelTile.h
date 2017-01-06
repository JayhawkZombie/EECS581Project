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
    LevelTile(const LevelTile &other);
    ~LevelTile();

    void Render();
    void TickUpdate(const double &delta);
    void OnShutDown();
    virtual void SerializeOut(std::ofstream &out) override;
    virtual void SerializeIn(std::ifstream &in) override;

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
