#include "../../Headers/Level/Level.h"

namespace Engine
{
  void Level::Render()
  {
    if (!Playable) {
      Render::RenderText(&LevelWaitingText);
    }
    else {
      LevelWaitingText.setString("Done loading!");

      Render::RenderSprite(BackgroundLayer.BGSprite);

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

      Render::RenderText(&LevelWaitingText);

      PlayerActor.Render();
    } //end else
  } //Render()
}
