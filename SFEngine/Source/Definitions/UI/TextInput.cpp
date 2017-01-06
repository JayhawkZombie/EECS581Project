#include "../../Headers/UI/TextInput.h"

namespace Engine
{


  namespace UI
  {

    TextInput::TextInput()
      :
      DefaultText("Input"),
      DefaultTextColor(sf::Color::White),
      DefaultTextSize(14),
      DefaultBackgroundWidth(100.f),
      DefaultBackgroundHeight(35.f),
      DefaultBackgroundColor(sf::Color(99, 99, 99)),
      DefaultOverlayColor(sf::Color(191, 191, 191, 157)),
      TextColorInFocus(sf::Color(224, 224, 224)),
      TextColorOutOfFocus(sf::Color(173, 190, 216))
    {
      Text = DefaultText;
      TextColor = DefaultTextColor;

      RenderedText.setString(DefaultText);
      RenderedText.setFillColor(DefaultTextColor);
      RenderedText.setCharacterSize(DefaultTextSize);
      RenderedText.setPosition({ 200, 200 });
      glFlush();

      Background.setPosition({ 200, 200 });
      Background.setSize({ DefaultBackgroundWidth, DefaultBackgroundHeight });
      Background.setFillColor(DefaultBackgroundColor);
      
      Overlay.setFillColor(DefaultOverlayColor);

      MouseTarget mtgt;
      mtgt.MouseBounds = Background.getGlobalBounds();
      mtgt.MouseExitCallback = [this](const sf::Vector2i &v) { this->HandleMouseExit(v); if (OnMouseExit) OnMouseExit(v); };
      mtgt.MouseMovementCallback = [this](const sf::Vector2i &pos) { this->HandleMouseMovement(pos); if (OnMouseMove) OnMouseMove(pos); };
      mtgt.MouseOverCallback = [this](const sf::Vector2i &pos) { this->HandleMouseOver(pos); if (OnMouseOver) OnMouseOver(pos); };
      mtgt.MousePressCallback = [this](const sf::Vector2i &v, const sf::Mouse::Button &b) { this->HandleMousePress(v, b); if (OnMousePress) OnMousePress(v, b); };
      mtgt.MouseReleaseCallback = [this](const sf::Vector2i &v, const sf::Mouse::Button &b) { this->HandleMouseRelease(v, b); if (OnMouseRelease) OnMouseRelease(v, b); };
      mtgt.FocusGainedCallback = [this](const sf::Vector2i &v) { this->HandleFocusGained(v); if (OnFocusGained) OnFocusGained(v); };
      mtgt.FocusLostCallback = [this](const sf::Vector2i &v) { this->HandleFocusLost(v); if (OnFocusLost) OnFocusLost(v); };

      AddMouseTarget(std::string("InputMouseTarget"), mtgt);

      KeyTarget ktgt;
      ktgt.Keys.set();

      ktgt.OnKeyPress = [this](const sf::Keyboard::Key &key) { this->HandleKeyPress(key); };
      ktgt.OnKeyRelease = [this](const sf::Keyboard::Key &key) { this->HandleKeyRelease(key); };

      AddKeyTarget(std::string("InputKeyTarget"), ktgt);
    }

    TextInput::~TextInput()
    {

    }

    //Add some methods to get/set text for the input
    std::string TextInput::GetText() const
    {
      return Text;
    }

    void TextInput::SetText(const std::string &str)
    {
      Text = str;
      RenderedText.setString(Text);
      glFlush();
    }

    //add some methods to set the font/text style for the input
    void TextInput::SetTextSize(std::size_t size)
    {
      TextSize = size;
      RenderedText.setCharacterSize(TextSize);
      glFlush();
    }

    void TextInput::SetTextColor(sf::Color color)
    {
      TextColor = color;
      RenderedText.setFillColor(TextColor);
    }

    void TextInput::SetFont(const std::string &fontpath)
    {
      ResourceManager->RequestFont(fontpath, fontpath,
                                   [this](std::shared_ptr<sf::Font> fnt, const std::string &ID) 
                                   { 
                                     this->TextFont = fnt; 
                                     this->RenderedText.setFont(*fnt);
                                   }
                                   );
    }

    void TextInput::SetDefaultString(const std::string &str)
    {
      DefaultText = str;
    }

    void TextInput::SetDefaultStringColor(sf::Color color)
    {
      DefaultTextColor = color;
    }

    void TextInput::TickUpdate(const double &delta)
    {

    }

    void TextInput::Render()
    {
      Render::RenderShape(&Background);
      Render::RenderText(&RenderedText);
      Render::RenderShape(&Overlay);
    }

    void TextInput::OnShutDown()
    {

    }

    void TextInput::SerializeOut(std::ofstream &out)
    {

    }

    void TextInput::SerializeIn(std::ifstream & in)
    {
    }

    void TextInput::CenterText()
    {

    }

    void TextInput::HandleMouseOver(const sf::Vector2i &pos) 
    {
    
    }

    void TextInput::HandleMouseExit(const sf::Vector2i &pos) 
    {
    
    }

    void TextInput::HandleMouseMovement(const sf::Vector2i &pos) 
    {
    
    }

    void TextInput::HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &b) 
    {
    
    }

    void TextInput::HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &b) 
    {
    
    }

    void TextInput::HandleFocusGained(const sf::Vector2i &pos) 
    {
      std::cerr << "Input gained focus" << std::endl;
      InFocus = true;

      RenderedText.setFillColor(TextColorInFocus);
      Overlay.setFillColor(sf::Color::Transparent);
    }

    void TextInput::HandleFocusLost(const sf::Vector2i &pos) 
    {
      std::cerr << "Input lost focus" << std::endl;
      InFocus = false;

      RenderedText.setFillColor(TextColorOutOfFocus);
      Overlay.setFillColor(OverlayColor);
    }

    bool TextInput::RespondsTo(const Events &evnt) const
    {
      return true; //just for now
    }

    bool TextInput::IsPrintable(const sf::Keyboard::Key &key)
    {
      return(
        (key <= sf::Keyboard::Num9) || (key >= sf::Keyboard::LBracket && key <= sf::Keyboard::Space)
        || (key >= sf::Keyboard::Add && key <= sf::Keyboard::Divide) || (key >= sf::Keyboard::Numpad0 && key <= sf::Keyboard::Numpad9));
    }

    void TextInput::HandleTextEntered(const sf::Keyboard::Key &key)
    {
      if (IsPrintable(key))
        HandleDisplayKey(key);
      else
        HandleNonDisplayKey(key);
    }

    void TextInput::HandleNonDisplayKey(const sf::Keyboard::Key &key)
    {

    }

    void TextInput::HandleDisplayKey(const sf::Keyboard::Key &key)
    {
      Text += key;
    }

    void TextInput::HandleKeyPress(const sf::Keyboard::Key &key) 
    {
      std::cerr << "Input response to key press" << std::endl;
    }

    void TextInput::HandleKeyRelease(const sf::Keyboard::Key &key) 
    {
      std::cerr << "Input response to key release" << std::endl;
    }


  }


}
