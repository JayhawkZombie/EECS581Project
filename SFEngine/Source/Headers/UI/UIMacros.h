#ifndef SFENGINE_UI_MACROS_H
#define SFENGINE_UI_MACROS_H

#include <TGUI\TGUI.hpp>

//Fuck off Microsoft with your namespace pollution
#ifdef _WINDEF_
#undef _WINDEF_
#undef TEXT
#undef __TEXT
#endif

#define ELEMENT_PTR
#define ELEMENT_POSITION
#define ELEMENT_TEXT
#define ELEMENT_SIZE
#define ELEMENT_THEME
#define ELEMENT_PARENT_GUI
#define ELEMENT_NAME
#define ELEMENT_TEXT_SIZE
#define ELEMENT_DURATION
#define ELEMENT_TO_SHOW
#define ELEMENT_TO_HIDE

#define __TGUI_ELEMENT_PLACE(ELEMENT, POSITION, _SIZE, GUI, NAME)    \
ELEMENT->setPosition(POSITION);                                      \
ELEMENT->setSize(_SIZE);                                             \
GUI->add(ELEMENT, NAME)

#define TGUI_ELEMENT_BUTTON_CREATE(ELEMENT, NAME, THEME, _SIZE, POSITION, TEXT, TEXTSIZE, GUI)   \
ELEMENT = THEME->load("button");                                                                 \
ELEMENT->setText(TEXT);                                                                          \
ELEMENT->setTextSize(TEXTSIZE);                                                                  \
__TGUI_ELEMENT_PLACE(ELEMENT, POSITION, _SIZE, GUI, NAME);                                       \

#define TGUI_ELEMENT_BUTTON_CREATE_HIDDEN(ELEMENT, NAME, THEME, _SIZE, POSITION, TEXT, TEXTSIZE, GUI)   \
TGUI_ELEMENT_BUTTON_CREATE(ELEMENT, NAME, THEME, _SIZE, POSITION, TEXT, TEXTSIZE, GUI)                  \
ELEMENT->hide();                                                                                        \

#define TGUI_ELEMENT_LABEL_CREATE(ELEMENT, NAME, THEME, _SIZE, POSITION, TEXT, TEXTSIZE, GUI)    \
ELEMENT = THEME->load("label");                                                                  \
ELEMENT->setText(TEXT);                                                                          \
__TGUI_ELEMENT_PLACE(ELEMENT, POSITION, _SIZE, GUI, NAME);                                       \

#define TGUI_ELEMENT_PANEL_CREATE(ELEMENT, NAME, THEME, _SIZE, POSITION, GUI)                    \
ELEMENT = THEME->load("panel");                                                                  \
__TGUI_ELEMENT_PLACE(ELEMENT, POSITION, _SIZE, GUI, NAME);                                       \

#define TGUI_PANEL_SWITCH_TRANSITION(PANEL_SHOW, PANEL_HIDE, DURATION)          \
PANEL_HIDE->hideWithEffect(tgui::ShowAnimationType::SlideToRight, DURATION);    \
PANEL_HIDE->disable();                                                          \
PANEL_SHOW->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, DURATION);   \
PANEL_SHOW->enable();                                                           \

#define TGUI_PANEL_SWITCH_TRANSITION_SHOW_LEFT_HIDE_RIGHT(PANEL_SHOW, PANEL_HIDE, DURATION)   \
PANEL_HIDE->hideWithEffect(tgui::ShowAnimationType::SlideToRight, DURATION);                  \
PANEL_HIDE->disable();                                                                        \
PANEL_SHOW->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, DURATION);                 \
PANEL_SHOW->enable();                                                                         

#define TGUI_PANEL_SWITCH_TRANSITION_SHOW_RIGHT_HIDE_LEFT(PANEL_SHOW, PANEL_HIDE, DURATION)   \
PANEL_HIDE->hideWithEffect(tgui::ShowAnimationType::SlideToLeft, DURATION);                   \
PANEL_HIDE->disable();                                                                        \
PANEL_SHOW->showWithEffect(tgui::ShowAnimationType::SlideFromRight, DURATION);                \
PANEL_SHOW->enable();                                                                         \

#define TGUI_CONNECT_MAKE_LAMBDA_MACRO(ELEMENT, SIGNAL, MACRO_CALL)             \
ELEMENT->connect(SIGNAL,  [this](){ MACRO_CALL; });                             \


#endif
