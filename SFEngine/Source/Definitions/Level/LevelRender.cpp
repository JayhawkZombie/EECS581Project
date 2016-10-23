#include "../../Headers/Level/Level.h"

namespace Engine
{
  void Level::Render()
  {
    Environment.Render();

    if (Playable) {
      
      for (auto player : Environment.LevelActors) {
        Render::RenderShape(&player->ActorRectangle);
      }

      sf::RectangleShape shape;
      shape.setFillColor(sf::Color::Transparent);
      shape.setOutlineColor(sf::Color::Black);
      shape.setOutlineThickness(3);

      for (auto & box : CollisionBoxes) {
        shape.setPosition(box.Position);
        shape.setSize(box.Size);

        Render::RenderShape(&shape);
      }

    }
    
    PlayerActor.Render();
  } //Render()
}
