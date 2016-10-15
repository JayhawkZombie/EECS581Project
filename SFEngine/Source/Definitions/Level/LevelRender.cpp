#include "../../Headers/Level/Level.h"

namespace Engine
{
  void Level::Render()
  {
    if (!IsReady()) {
      Render::RenderText(&LevelWaitingText);
    }
    else {
      LevelWaitingText.setString("Done loading!");

      for (auto & layer : Layers) {
        
        Render::RenderSprite(layer->BGSprite);
        
      } //for (auto & layer : Layers)

      Render::RenderText(&LevelWaitingText);
    } //end else
  } //Render()
}
