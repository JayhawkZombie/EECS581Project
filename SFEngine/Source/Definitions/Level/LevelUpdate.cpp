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

    //Only want to update the physics 60 times per second, since it does not time itself ((((UGH))))
    if (cumulative > updateInterval && DoUpdatePhysics && TestObjects.size() > 0 && TestSegments.size() > 0) {
      cumulative = 0.f;
      UpdatePhysics(TestObjects, TestSegments);
    }
	for (auto & object : Objects) {
		object->TickUpdate(delta);
	}
  }

}