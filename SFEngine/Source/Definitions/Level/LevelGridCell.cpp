#include "../../Headers/Level/LevelEnvironment.h"

#include "../../Headers/Actor/Actor.h"

namespace Engine
{

  GridCell::GridCell()
    : LevelPosition({ 0,0 }), ScreenPosition({ -10000, -10000 })
  {

  }

  void GridCell::TickUpdate(const double &delta)
  {
    BGTile.TickUpdate(delta);

    for (auto & object : Objects) {
      object->LevelGridCellUpdate(delta);
      object->PreviousPhysicsState = object->CurrentPhysicsState;
    }

    for (auto & actor : Actors) {
      actor->LevelGridCellUpdate(delta);
      actor->PreviousPhysicsState = actor->CurrentPhysicsState;
    }

  }

  void GridCell::PhysicsUpdate()
  {
    for (auto & actor : Actors) {

      for (auto & object : Objects) {

        if (Physics::DoObjectsOverlap(actor.get(), object.get())) {
          OverlapAction action = object->OnActorOverlap(actor.get());
          std::cerr << "Actor overlapped object" << std::endl;
          switch (action)
          {
            case OverlapAction::KILL_ACTOR:
              break;
            case OverlapAction::DISALLOW_ACTOR_OVERLAP:
              actor->PhysicsUpdate(actor->PreviousPhysicsState);
          }
        }

      }

    }
  }

  void GridCell::Render(std::function<void(sf::Vector2f &LC, sf::Vector2f &WC)> conversion)
  {
    Render::RenderSprite(&BGTile.TileSprite);

    for (auto & object : Objects) {
      sf::Vector2f WinPos;
      sf::Vector2f LC = object->CurrentPhysicsState.GetLevelPosition();
      conversion(WinPos, LC);

      object->CurrentPhysicsState.SetScreenPosition(WinPos);
      object->Render();
    }

    for (auto & actor : Actors) {
      sf::Vector2f WinPos;
      sf::Vector2f LC = actor->CurrentPhysicsState.GetLevelPosition();
      conversion(WinPos, LC);

      actor->CurrentPhysicsState.SetScreenPosition(WinPos);
      actor->Render();
    }

  }

  void GridCell::EndOfFrame()
  {
    for (auto & object : Objects)
      object->EndOfFrame();

    for (auto & actor : Actors)
      actor->EndOfFrame();
  }

}
