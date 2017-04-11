#ifndef SFENGINE_UI_MACROS_H
#define SFENGINE_UI_MACROS_H

#include <TGUI\TGUI.hpp>

//Fuck off Microsoft with your namespace pollution
#ifdef _WINDEF_
#undef _WINDEF_
#undef TEXT
#undef __TEXT
#endif

#define TGUI_ELEMENT_CREATE(ELEMENT, NAME, THEME, _SIZE, POSITION, TEXT, TEXTSIZE, GUI)          \
ELEMENT = THEME->load("button");                                                                 \
ELEMENT->setPosition(POSITION);                                                                  \
ELEMENT->setText(TEXT);                                                                          \
ELEMENT->setSize(_SIZE);                                                                         \
GUI->add(ELEMENT, NAME);                                                                         \

#endif
