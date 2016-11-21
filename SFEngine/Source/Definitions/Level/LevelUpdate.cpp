#include "../../Headers/Level/Level.h"

namespace Engine
{
  void Level::TickUpdate(const double &delta)
  {
    ResourceLock->lock();

    if (!ReadyToPlay) {

    }
    else {
      Environment.TickUpdate(delta);
    }

    ResourceLock->unlock();


  }

}