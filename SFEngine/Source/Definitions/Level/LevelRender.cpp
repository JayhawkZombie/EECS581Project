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

      sf::RectangleShape shape;
      shape.setFillColor(sf::Color::Transparent);
      shape.setOutlineColor(sf::Color::Black);
      shape.setOutlineThickness(3);

      for (auto & box : CollisionBoxes) {
        shape.setPosition(box.Position);
        shape.setSize(box.Size);

        Render::RenderShape(&shape);
      }

      PlayerActor.Render();
    } //end else
  } //Render()
}
