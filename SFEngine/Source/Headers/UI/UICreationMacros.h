#ifndef SFENGINE_UI_CREATION_MACROS_H
#define SFENGINE_UI_CREATION_MACROS_H


namespace Engine
{

#define UIMenu std::shared_ptr<UI::MenuWidget>
#define UIMenuScreen std::shared_ptr<UI::MenuScreen>
#define UIButton std::shared_ptr<UI::ClickButtonBase>
#define UITextInput std::shared_ptr<UI::TextInput>
#define UIIntSpinner std::shared_ptr<UI::IntSpinner>
#define UITextLabel std::shared_ptr<UI::TextLabel>

#define MakeButtonNormal(BUTTON, LAYER, HELPER, POSITION, _SIZE, THEME, TEXTURE)\
BUTTON = Engine::UI::ClickButtonBase::Create(LAYER, HELPER, POSITION, _SIZE, TEXTURE);\
BUTTON->SetBGColor(THEME.ButtonColorNormal);\
BUTTON->SetBGColorHighlighted(THEME.ButtonColorHighlighted);\
BUTTON->SetBGColorPressed(THEME.ButtonColorPressed);\
BUTTON->SetBGOutlineColor(THEME.ButtonOutlineColorNormal);\
BUTTON->SetBGOutlineColorHighlighted(THEME.ButtonOutlineColorHighlighted);

#define MakeMenu(MENU, LAYER, HELPER)\
MENU = Engine::UI::MenuWidget::Create(LAYER, HELPER, MENU##Position, MENU##Size);

#define MakeMenuDefaultScreen(SCREEN, THEME, MENU)\
MakeMenuScreen(SCREEN, THEME, MENU);\
UI::MenuWidget::SetDefaultScreen(SCREEN, MENU);

#define AddMenuScreen(MENU, SCREEN)\
Engine::UI::MenuWidget::AddScreen(SCREEN, MENU);

#define MakeMenuScreen(SCREEN, THEME, MENU)\
SCREEN = Engine::UI::MenuScreen::Create();\
SCREEN->SetBGColor(THEME.MenuBackgroundColorNormal);\
SCREEN->SetBGPosition(MENU##ScreenPosition);\
SCREEN->SetBGSize(MENU##ScreenSize);\

#define MakeButtonWithText(BUTTON, LAYER, HELPER, POSITION, _SIZE, __TEXT__, __FONT__, THEME)\
BUTTON = Engine::UI::ClickButtonBase::Create(LAYER, HELPER, POSITION, THEME.ButtonSizeThin, nullptr);\
BUTTON->SetBGColor(THEME.ButtonColorNormal);\
BUTTON->SetBGColorHighlighted(THEME.ButtonColorHighlighted);\
BUTTON->SetBGColorPressed(THEME.ButtonColorPressed);\
BUTTON->SetBGOutlineColor(THEME.ButtonOutlineColorNormal);\
BUTTON->SetBGOutlineColorHighlighted(THEME.ButtonOutlineColorHighlighted);\
auto BUTTON##_label_##BUTTON = Engine::UI::TextLabel::Create(BUTTON, HELPER, THEME.ButtonTextAlignment, std::string(__TEXT__), THEME.TextColorNormal, __FONT__, THEME.TextSizeNormal, BUTTON->GlobalWidgetBounds.GlobalBounds, {0, 0});

#define MakeMenuScreenButtonNormal(BUTTON, SCREEN, MENU, POSITION, THEME, __TEXT__, __FONT__, TEXTURE)\
BUTTON = Engine::UI::ClickButtonBase::Create(SCREEN->ScreenLayer, SCREEN->ScreenHelper, POSITION, THEME.ButtonSizeNormal, TEXTURE);\
BUTTON->SetBGColor(THEME.ButtonColorNormal);\
BUTTON->SetBGColorHighlighted(THEME.ButtonColorHighlighted);\
BUTTON->SetBGColorPressed(THEME.ButtonColorPressed);\
BUTTON->SetBGOutlineColor(THEME.ButtonOutlineColorNormal);\
BUTTON->SetBGOutlineColorHighlighted(THEME.ButtonOutlineColorHighlighted);\
auto BUTTON##label = Engine::UI::TextLabel::Create(BUTTON, BUTTON->Helper, THEME.ButtonTextAlignment, std::string(__TEXT__), THEME.TextColorNormal, __FONT__, THEME.TextSizeNormal, BUTTON->GlobalWidgetBounds.GlobalBounds, {0, 0});

#define MakeMenuScreenButtonBack(BUTTON, SCREEN)\
BUTTON->MouseReleaseCB = [this](){this->SCREEN->CloseScreen();};

#define MakeMenuButtonClose(BUTTON, MENU)\
BUTTON->MouseReleaseCB = [this](){this->MENU->CloseMenu();};

#define MakeMenuButtonOpen(BUTTON, MENU)\
BUTTON->MouseReleaseCB = [this](){UI::MenuWidget::OpenMenu(this->MENU);};

#define MakeMenuScreenTransition(BUTTON, MENU, TOSCREEN)\
BUTTON->MouseReleaseCB = [this](){this->MENU->ShowScreen(this->TOSCREEN);};

}

#endif
