#include "../../Headers/Level/Level.h"

namespace Engine
{

  void Level::TickUpdate(const double &delta)
  {
    OldActorPos = PlayerActor.Position;
    PlayerActor.TickUpdate(delta);

    CheckCollisions();
  }

  void Level::OnShutDown()
  {
    Environment.BackgroundTiles->ClearGrid();
  }

}