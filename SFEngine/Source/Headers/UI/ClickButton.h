#ifndef SFENGINE_UI_CLICK_BUTTON_H
#define SFENGINE_UI_CLICK_BUTTON_H

#include "BaseUIElement.h"

namespace Engine
{
  namespace UI
  {
    /**
     * ClickButton
     * Basic button that is clickable
     *  If callbacks are bound, events will be passed to the button whenever an action occurs on it
     */
    class ClickButton : public BaseUIElement
    {
    public:
      static std::shared_ptr<ClickButton> Create();
      TYPEDEF_PARENT_CLASS(Engine::UI::BaseUIElement);

      ClickButton();
      ClickButton(const ClickButton &) = delete;
      ~ClickButton();
      
      virtual void TickUpdate(const double &delta) override;
      virtual void Render() override;
      virtual void OnShutDown() override;
      virtual void SerializeOut(std::ostream &out) override;

      virtual void SetSize(const sf::Vector2f &size);
      virtual void SetPosition(const sf::Vector2f &Position);
      virtual void Align();

    protected:
      virtual void HandleMouseOver(const sf::Vector2i &pos);
      virtual void HandleMouseExit(const sf::Vector2i &pos);
      virtual void HandleMouseMovement(const sf::Vector2i &pos);
      virtual void HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &b);
      virtual void HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &b);
      virtual void HandleFocusGained(const sf::Vector2i &pos);
      virtual void HandleFocusLost(const sf::Vector2i &pos);
      virtual void HandleKeyPress(const sf::Keyboard::Key &key);
      virtual void HandleKeyRelease(const sf::Keyboard::Key &key);

      void GetBGTexture(std::shared_ptr<sf::Texture> tex, const std::string &ID);
      void GetHighlightedTexture(std::shared_ptr<sf::Texture> tex, const std::string &ID);
      void GetPressedTexture(std::shared_ptr<sf::Texture> tex, const std::string &ID);
      void GetFont(std::shared_ptr<sf::Font> fnt, const std::string &ID);

      std::shared_ptr<sf::RectangleShape> ButtonShape;
      std::shared_ptr<sf::Texture> ButtonTexture;
      std::shared_ptr<sf::Texture> ButtonHighlightedTexture;
      std::shared_ptr<sf::Texture> ButtonPressedTexture;
      std::shared_ptr<sf::Text> ButtonText;
      std::shared_ptr<sf::Font> ButtonFont;

      bool GotBGTexture;
      bool GotHighlightedTexture;
      bool GotPressedTexture;
      
      sf::Color ButtonColor;
    };
  }
}




#endif
