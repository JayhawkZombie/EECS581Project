#include "../../Headers/Level/LevelEnvironment.h"

namespace Engine
{

  GridCell::GridCell()
    : LevelPosition({ 0,0 }), ScreenPosition({ -10000, -10000 })
  {

  }

  void GridCell::TickUpdate(const double &delta)
  {
    BGTile.TickUpdate(delta);
  }

}
