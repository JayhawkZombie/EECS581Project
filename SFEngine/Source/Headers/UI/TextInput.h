#ifndef SFENGINE_TEXT_INPUT_H
#define SFENGINE_TEXT_INPUT_H



#include "BaseUIElement.h"

namespace Engine
{

  namespace UI
  {


    class TextInput : public BaseUIElement
    {
    public:
      TextInput();
      virtual ~TextInput();

      virtual void TickUpdate(const double &delta) override;
      virtual void Render() override;
      virtual void OnShutDown() override;
      virtual void SerializeOut(std::ofstream &out) override;
      virtual void SerializeIn(std::ifstream &in) override;

      //Add some methods to get/set text for the input
      std::string GetText() const;
      void SetText(const std::string &str);

      //add some methods to set the font/text style for the input
      void SetTextSize(std::size_t size);
      void SetTextColor(sf::Color color);
      void SetFont(const std::string &fontpath);

      void SetDefaultString(const std::string &str);
      void SetDefaultStringColor(sf::Color color);

      virtual bool RespondsTo(const Events &evnt) const override;

    protected:
      bool ListeningForKeys = true;

      sf::Text RenderedText;
      std::shared_ptr<sf::Font> TextFont;
      std::size_t TextSize;
      std::size_t DefaultTextSize;
      float DefaultBackgroundWidth;
      float DefaultBackgroundHeight;

      sf::RectangleShape Background;
      sf::RectangleShape Overlay;

      std::string Text;
      std::string DefaultText;

      sf::Color TextColor;
      sf::Color DefaultTextColor;
      sf::Color TextColorInFocus;
      sf::Color TextColorOutOfFocus;

      sf::Color BackgroundColor;
      sf::Color DefaultBackgroundColor;

      sf::Color OverlayColor;
      sf::Color DefaultOverlayColor;

      //method to make the text centered nicely
      void CenterText();

      //override the methods from the base class
      virtual void HandleMouseOver(const sf::Vector2i &pos) override;
      virtual void HandleMouseExit(const sf::Vector2i &pos) override;
      virtual void HandleMouseMovement(const sf::Vector2i &pos) override;
      virtual void HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &b) override;
      virtual void HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &b) override;
      virtual void HandleFocusGained(const sf::Vector2i &pos) override;
      virtual void HandleFocusLost(const sf::Vector2i &pos) override;
      virtual void HandleKeyPress(const sf::Keyboard::Key &key) override;
      virtual void HandleKeyRelease(const sf::Keyboard::Key &key) override;
      virtual void HandleTextEntered(const sf::Keyboard::Key &key) override;

      //method to handle special keys (like Enter, Backspace, etc)
      bool IsPrintable(const sf::Keyboard::Key &key);
      void HandleNonDisplayKey(const sf::Keyboard::Key &k);

      //method to handle diaplayable keys (letters, numbers, etc)
      void HandleDisplayKey(const sf::Keyboard::Key &key);

    };


  }

}


#endif
