#include "../../Headers/Level/Level.h"
#include "../../Headers/Engine/Console.h"

namespace Engine
{
  void Level::TickUpdate(const double &delta)
  {
    static double cumulative = 0.f;
    cumulative += delta;

#ifdef WITH_EDITOR
    //Update editor related objects
    for (auto & anim : EditorGraphAnimations)
      anim.second->TickUpdate(delta);
#endif
    TileMap.update(lvlData, 20);
    //Only want to update the physics 60 times per second, since it does not time itself ((((UGH))))
    
    for (auto & obj : Objects)
      obj->TickUpdate(delta);

    if (cumulative > updateInterval) {

      if (DoUpdatePhysics && TestObjects.size() > 0 && TestSegments.size() > 0)
        UpdatePhysics(TestObjects, TestSegments);

      for (auto & obj : Objects)
        obj->PhysicsUpdate();

      cumulative = 0.f;
    }

    //if (cumulative > updateInterval && DoUpdatePhysics && TestObjects.size() > 0 && TestSegments.size() > 0) {
    //  
    //  UpdatePhysics(TestObjects, TestSegments);
    //}
    //if (cumulative > updateInterval) {
    //  for (auto & object : Objects) {
    //    object->TickUpdate(delta);
    //  }
    //  
    //}
  }

}