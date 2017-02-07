#include "../../Headers/Level/Level.h"

namespace Engine
{
  void Level::TickUpdate(const double &delta)
  {

    if (TestLevelMeshes.size() > 0 && TestSegments.size() > 0)
      UpdatePhysics(TestLevelMeshes, TestSegments);

  }

}