#ifndef SFENGINE_UI_CREATIONMACROS_H
#define SFENGINE_UI_CREATIONMACROS_H

#include "Widget.h"

/**
*  Custom macros to assist in creating elements
*/

/**
*  Create an attribute for the element, which will then contain getters and setters
*/

#define UI_ATTRIBUTE(AttrType, AttrName)\
protected:\
AttrType _##AttrName;\
AttrType Get##AttrName() const\
{\
    return this->_##AttrName;\
}\
void Set##AttrName(const AttrType &InType)\
{\
  this->_##AttrName = InType;\
}

#endif
