#include "../../Headers/Level/Level.h"

namespace Engine
{

  void Level::TickUpdate(const double &delta)
  {
    PlayerActor.TickUpdate(delta);

    CheckCollisions();
  }

  void Level::OnShutDown()
  {
    
  }

}