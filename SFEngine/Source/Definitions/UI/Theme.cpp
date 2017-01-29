#include "../../Headers/UI/Theme.h"

namespace Engine
{

  namespace UI
  {

    /*
        struct Theme
    {
      sf::Vector2f ButtonSizeSmall, ButtonSizeNormal, ButtonSizeMedium, ButtonSizeLarge;
      sf::Color ButtonColorNormal, ButtonColorHighlighted, ButtonColorPressed, ButtonColorDisabled;

      sf::Color ButtonOutlineColorNormal, ButtonOutlineColorHighlighted, ButtonOutlineColorPressed, ButtonOutlineColorDisabled;

      sf::Color MenuBackgroundColorNormal, MenuBackgroundColorDisabled;
      sf::Color MenuOutlineColorNormal, MenuOutlineColorDisabled;
      sf::Color WidgetBackgroundColorNormal, MenuBackgroundColorDisabled;
      sf::Color TextColorNormal, TextColorDisabled, TextColorError;
      unsigned int TextSizeSmall, TextSizeNormal, TextSizeMedium, TextSizeLarge;
      TextAlignment ButtonTextAlignment, WidgetTextAlignment, MenuTextAlignment;
    };
    */
    Theme DefaultDarkTheme{
      {50, 15}, //ButtonSizeSmall
      {100, 40}, //ButtonSizeNormal
      {75, 35}, //ButtonSizeMedium
      {200, 75}, //ButtonSizeLarge

      {sf::Color(23, 47, 51)}, //ButtonColorNormal
      {sf::Color(23, 80, 130)}, //ButtonColorHighlighted
      {sf::Color(23, 26, 43)}, //ButtonColorPressed
      {sf::Color(58, 26, 28)}, //ButtonColorDisabled

      {sf::Color(26, 50, 68)}, //ButtonOutlineColorNormal
      {sf::Color(15, 29, 40)}, //ButtonOutlineColorHighlighted
      {sf::Color(39, 77, 107)}, //ButtonOutlineColorPressed
      {sf::Color(107, 0, 19)}, //ButtonOutlineColorDisabled
      
      {sf::Color(51, 51, 51)}, //MenuBackgroundColorNormal
      {sf::Color(56, 0, 9)}, //MenuBackgroundColorDisabled
      
      {sf::Color(48, 48, 48, 100)}, //MenuOutlineColorNormal
      {sf::Color(0, 0, 0, 100)}, //MenuOutlineColorDisabled
      
      {sf::Color(0, 65, 91)}, //WidgetBackgroundColorNormal
      {sf::Color(0, 27, 38)}, //WidgetBackgroundColorDisabled
      
      {sf::Color(214, 214, 214)}, //TextColorNormal
      {sf::Color(63, 45, 53)}, //TextColorDisabled
      {sf::Color(124, 0, 16)}, //TextColorError
      
      10, //TextSizeSmall
      14, //TextSizeNormal
      18, //TextSizeMedium
      22, //TextSizeLarge
      
      TextAlignment::CenterJustified, //ButtonTextAlignment
      TextAlignment::TopCenterJustified, //WidgetTextAlignment
      TextAlignment::TopCenterJustified //MenuTextAlignment
    };

  }

}