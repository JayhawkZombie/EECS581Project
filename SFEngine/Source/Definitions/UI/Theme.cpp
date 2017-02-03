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
      {100, 35}, //ButtonSizeNormal
      {75, 35}, //ButtonSizeMedium
      {200, 75}, //ButtonSizeLarge

      {sf::Color(61, 61, 61)}, //ButtonColorNormal
      {sf::Color(89, 89, 89)}, //ButtonColorHighlighted
      {sf::Color(35, 35, 35)}, //ButtonColorPressed
      {sf::Color(55, 44, 56)}, //ButtonColorDisabled

      {sf::Color(142, 142, 142)}, //ButtonOutlineColorNormal
      {sf::Color(183, 183, 183)}, //ButtonOutlineColorHighlighted
      {sf::Color(79, 79, 79)}, //ButtonOutlineColorPressed
      {sf::Color(142, 142, 142)}, //ButtonOutlineColorDisabled

      {sf::Color(40, 40, 40, 200)}, //MenuBackgroundColorNormal
      {sf::Color(56, 0, 9, 200)}, //MenuBackgroundColorDisabled

      {sf::Color(56, 56, 56, 200)}, //MenuOutlineColorNormal
      {sf::Color(0, 0, 0, 100)}, //MenuOutlineColorDisabled

      {sf::Color(40, 40, 40)}, //WidgetBackgroundColorNormal
      {sf::Color(0, 27, 38)}, //WidgetBackgroundColorDisabled

      {sf::Color(153, 153, 153)}, //TextColorNormal
      {sf::Color(63, 45, 53)}, //TextColorDisabled
      {sf::Color(124, 0, 16)}, //TextColorError

      12, //TextSizeSmall
      14, //TextSizeNormal
      18, //TextSizeMedium
      22, //TextSizeLarge

      TextAlignment::CenterJustified, //ButtonTextAlignment
      TextAlignment::TopCenterJustified, //WidgetTextAlignment
      TextAlignment::TopCenterJustified, //MenuTextAlignment

      sf::Color(48, 48, 48), //CheckBoxBackgroundColor
      {25, 25}, //CheckBoxSize

      sf::Color(142, 142, 142), //TextInputBackgroundColor
      3, //TextInputPadding

      sf::IntRect(0, 161, 400, 160), //ButtonOverlayNormal
      sf::IntRect(0, 0, 400, 160), //ButtonOverlayHighlighted
      sf::IntRect(0, 322, 400, 160), //ButtonOVerlayPressed

      sf::Color(123, 123, 123, 200), //ListBackgroundColorNormal
      sf::Color(132, 132, 132, 150), //ListOutlineColorNormal
      sf::Color(173, 173, 173, 150), //ListOutlineColorHighlighted

      sf::Vector2f(200, 25), //ButtonSizeThin
      sf::Vector2f(70, 25), //ToolBarButtonSize
      sf::Vector2f(100, 15) //ToolBarDropDownButtonSize
    };

  }

}