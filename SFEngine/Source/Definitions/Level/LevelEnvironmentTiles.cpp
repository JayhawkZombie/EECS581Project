#include "../../Headers/Level/LevelEnvironment.h"

namespace Engine
{

  Tile::Tile()
    : IsAnimated(false), TotalAnimationDuration(0), CurrentAnimationDuration(0), FrameDelta(0), CurrentFrame(0)
  {

  }

  void Tile::TickUpdate(const double &delta)
  {
    if (IsAnimated) {
      CurrentAnimationDuration += delta;

      if (CurrentAnimationDuration >= FrameDelta) {
        CurrentAnimationDuration = 0;
        ++CurrentFrame;
        if (CurrentFrame >= NumFrames)
          CurrentFrame = 0;

        TileSprite.setTextureRect(Frames[CurrentFrame]);
      }
      
    }
  }

  void Tile::Render()
  {
    Render::RenderSprite(&TileSprite);
  }

}
