#ifndef SFENGINE_WIDGET_COLLISION_HELPERS_H
#define SFENGINE_WIDGET_COLLISION_HELPERS_H

#include <SFML/Graphics.hpp>

#include "Widget.h"
#include "../Utils/CollisionHelpers.h"


namespace Engine
{


  namespace UI
  {


    bool DidMouseOver(SharedWidgetPointer Widget, const InputEvent &IEvent);
    bool DidMouseLeave(SharedWidgetPointer Widget, const InputEvent &IEvent);
    bool DidMouseMove(SharedWidgetPointer Widget, const InputEvent &IEvent);
    bool DidMousePress(SharedWidgetPointer Widget, const InputEvent &IEvent);
    bool DidMouseRelease(SharedWidgetPointer Widget, const InputEvent &IEvent);
    bool DidBeginDrag(SharedWidgetPointer Widget, const InputEvent &IEvent);
    bool DidContinueDrag(SharedWidgetPointer Widget, const InputEvent &IEvent);
    bool DidEndDrag(SharedWidgetPointer Widget, const InputEvent &IEvent);


  }


}

#endif
