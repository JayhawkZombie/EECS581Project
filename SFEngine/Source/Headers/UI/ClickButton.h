#ifndef SFENGINE_UI_CLICK_BUTTON_H
#define SFENGINE_UI_CLICK_BUTTON_H

#include "BaseUIElement.h"

namespace Engine
{
  namespace UI
  {
    class ClickButton : public BaseUIElement
    {
    public:
      static std::shared_ptr<ClickButton> Create();

      ClickButton();
      ClickButton(const ClickButton &) = delete;
      ~ClickButton();
      
      virtual void TickUpdate(const double &delta);
      virtual void Render();
      virtual void OnShutDown();

      virtual void SetSize(const sf::Vector2f &size);
      virtual void SetPosition(const sf::Vector2f &Position);
      virtual void Align();

    protected:
      std::shared_ptr<sf::RectangleShape> ButtonShape;
      std::shared_ptr<sf::Texture> ButtonTexture;
      std::shared_ptr<sf::Text> ButtonText;
      std::shared_ptr<sf::Font> ButtonFont;
      
      sf::Color ButtonColor;
    };
  }
}




#endif
