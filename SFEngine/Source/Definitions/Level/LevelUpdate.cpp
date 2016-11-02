#include "../../Headers/Level/Level.h"

namespace Engine
{
  void Level::TickUpdate(const double &delta)
  {
    ResourceLock->lock();

    if (!ReadyToPlay) {
      float progress = 100.f * (TexturesReceived / NumTextures);
      LoadingTexturesBar.setSize({ 20, progress });
      LoadingTexturesBar.setPosition({ 50, 400 });
    }
    else {
      Environment.TickUpdate(delta);
    }

    ResourceLock->unlock();
  }

}