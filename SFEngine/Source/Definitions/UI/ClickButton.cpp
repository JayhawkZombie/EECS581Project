#include "../../Headers/UI/ClickButton.h"
#include <memory>
namespace Engine
{
  namespace UI
  {
    std::shared_ptr<ClickButton> ClickButton::Create()
    {
      auto ptr = std::make_shared<ClickButton>();

      return ptr;
    }


    ClickButton::ClickButton()
      :
      ButtonTextString("DefaultText"),
      ButtonTextSize(std::shared_ptr<std::size_t>(new std::size_t)),
      ButtonFont(std::shared_ptr<sf::Font>(new sf::Font))
    {
      ReadyToRender = false;
      ButtonFont->loadFromFile("./SFEngine/Samples/Fonts/Raleway-Light.ttf");
      ButtonText.setFillColor(sf::Color::White);
      ButtonText.setString("DefaultText");
      glFlush();

      ButtonTexture = std::shared_ptr<sf::Texture>(new sf::Texture);
      ButtonHighlightedTexture = std::shared_ptr<sf::Texture>(new sf::Texture);
      ButtonPressedTexture = std::shared_ptr<sf::Texture>(new sf::Texture);
      ButtonTexture->loadFromFile("./SFEngine/Samples/Textures/UI/ButtonBG.png");
      SetBGTexture(ButtonTexture, "ButtonBGTexture");

      ButtonHighlightedTexture->loadFromFile("./SFEngine/Samples/Textures/UI/ButtonBGHovered.png");
      SetHighlightedTexture(ButtonHighlightedTexture, "ButtonHLTexture");

      ButtonPressedTexture->loadFromFile("./SFEngine/Samples/Textures/UI/ButtonBGPressed.png");
      SetPressedTexture(ButtonPressedTexture, "ButtonPRTexture");
      
      if (ButtonFont)
        ButtonText.setFont(*ButtonFont);

      KeyTarget kTgt;
      kTgt.Keys.set(sf::Keyboard::Return);
      kTgt.OnKeyPress = [this](const sf::Keyboard::Key &k) {this->HandleKeyPress(k); };
      kTgt.OnKeyRelease = [this](const sf::Keyboard::Key &k) {this->HandleKeyRelease(k); };

      AddKeyTarget(std::string("KeyTarget"), kTgt);
      
      MouseTarget mtgt;
      mtgt.MouseBounds = ButtonShape.getGlobalBounds();

      
      mtgt.MouseExitCallback = [this](const sf::Vector2i &v) { this->HandleMouseExit(v); if (OnMouseExit) OnMouseExit(v); };
      mtgt.MouseMovementCallback = [this](const sf::Vector2i &pos) { this->HandleMouseMovement(pos); if (OnMouseMove) OnMouseMove(pos); };
      mtgt.MouseOverCallback = [this](const sf::Vector2i &pos) { this->HandleMouseOver(pos); if (OnMouseOver) OnMouseOver(pos); };
      mtgt.MousePressCallback = [this](const sf::Vector2i &v, const sf::Mouse::Button &b) { this->HandleMousePress(v, b); if (OnMousePress) OnMousePress(v, b); };
      mtgt.MouseReleaseCallback = [this](const sf::Vector2i &v, const sf::Mouse::Button &b) { this->HandleMouseRelease(v, b); if (OnMouseRelease) OnMouseRelease(v, b); };
      mtgt.FocusGainedCallback = [this](const sf::Vector2i &v) { this->HandleFocusGained(v); if (OnFocusGained) OnFocusGained(v); };
      mtgt.FocusLostCallback = [this](const sf::Vector2i &v) { this->HandleFocusLost(v); if (OnFocusLost) OnFocusLost(v); };

      AddMouseTarget(std::string("ButtonMouseRegion"), mtgt);
      GotBGTexture = GotHighlightedTexture = GotPressedTexture = false;
      State.reset(Active);
    }

    ClickButton::~ClickButton()
    {
      if (ButtonFont)
        ButtonFont.reset();

      if (ButtonTextSize)
        ButtonTextSize.reset();
    }

    void ClickButton::SerializeOut(std::ofstream &out)
    {

    }

    void ClickButton::SerializeIn(std::ifstream & in)
    {
    }

    void ClickButton::SetText(const std::string &str)
    {
      //*ButtonTextString = str;
      //
      //if (ButtonText)
      //  ButtonText.setString(*ButtonTextString);
      //glFlush();
    }

    void ClickButton::SetTextSize(std::size_t size)
    {
      *ButtonTextSize = size;
      ButtonText.setCharacterSize(size);
      glFlush();
    }

    void ClickButton::SetFont(std::shared_ptr<sf::Font> fnt, const std::string &ID)
    {
      
      //ButtonFont = fnt;
      //ButtonText.setFont(*ButtonFont);
      ReadyToRender = (GotBGTexture && GotHighlightedTexture && GotPressedTexture);
      if (ReadyToRender) {
        State.set(Active);
        Align();
      }
    }

    void ClickButton::SetBGTexture(std::shared_ptr<sf::Texture> tex, const std::string &ID)
    {
      ButtonTexture = tex;
      GotBGTexture = true;
      ButtonShape.setTexture(ButtonTexture.get());
      ReadyToRender = (GotBGTexture && GotHighlightedTexture && GotPressedTexture);
      if (ReadyToRender) {
        State.set(Active);
        Align();
      }
    }

    void ClickButton::SetHighlightedTexture(std::shared_ptr<sf::Texture> tex, const std::string &ID)
    {
      ButtonHighlightedTexture = tex;
      GotHighlightedTexture = true;
      ReadyToRender = (GotBGTexture && GotHighlightedTexture && GotPressedTexture);
      if (ReadyToRender) {
        State.set(Active);
        Align();
      }
    }

    void ClickButton::SetPressedTexture(std::shared_ptr<sf::Texture> tex, const std::string &ID)
    {
      ButtonPressedTexture = tex;
      GotPressedTexture = true;
      ReadyToRender = (GotBGTexture && GotHighlightedTexture && GotPressedTexture);
      if (ReadyToRender) {
        State.set(Active);
        Align();
      }
    }

    void ClickButton::Align()
    {
      ButtonShape.setPosition(v2fPostion);
      ButtonShape.setSize(v2fSize);

      if (!ButtonFont)
        return;

      ButtonText.setCharacterSize(*ButtonTextSize);
      ButtonText.setString(ButtonTextString);
      glFlush();


      float xDiff, yDiff;
      float textWidth = ButtonText.getGlobalBounds().width;
      float textHeight = ButtonText.getGlobalBounds().height;

      xDiff = (v2fSize.x - textWidth) / 2.f;
      yDiff = (v2fSize.y - textHeight) / 2.f;
      ButtonText.setPosition(
        xDiff > 0 ?
          sf::Vector2f(v2fPostion.x + xDiff, v2fPostion.y + yDiff)
        : sf::Vector2f(v2fPostion)
      );

      //RenderTargets["ButtonBG"].SetDrawBounds(ButtonShape->getGlobalBounds());
      //RenderTargets["ButtonText"].SetDrawBounds(ButtonShape->getGlobalBounds());
      sf::FloatRect r = ButtonShape.getGlobalBounds();

      MouseTargets["ButtonMouseRegion"].MouseBounds = ButtonShape.getGlobalBounds();
    }

    void ClickButton::HandleMouseOver(const sf::Vector2i &v)
    {
      if (ReadyToRender)
        ButtonShape.setTexture(ButtonHighlightedTexture.get());
    }

    void ClickButton::HandleMouseExit(const sf::Vector2i &pos)
    {
      if (ReadyToRender)
        ButtonShape.setTexture(ButtonTexture.get());
    }

    void ClickButton::HandleMouseMovement(const sf::Vector2i &pos)
    {
      //std::cerr << "<<<Mouse moved on button" << std::endl;
    }

    void ClickButton::HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &b)
    {
      if (ReadyToRender)
        ButtonShape.setTexture(ButtonPressedTexture.get());
    }

    void ClickButton::HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &b)
    {
      if (ReadyToRender)
        ButtonShape.setTexture(ButtonTexture.get());
    }

    void ClickButton::HandleFocusGained(const sf::Vector2i &pos)
    {
      //std::cerr << "<<<Button Gained Focus" << std::endl;
    }

    void ClickButton::HandleFocusLost(const sf::Vector2i &pos)
    {
      //std::cerr << "<<<Button Lost Focus" << std::endl;
    }

    void ClickButton::HandleKeyPress(const sf::Keyboard::Key &key)
    {
      std::cerr << key << " pressed on button " << std::endl;
    }

    void ClickButton::HandleKeyRelease(const sf::Keyboard::Key &key)
    {
      std::cerr << key << " released on button " << std::endl;
    }

    void ClickButton::MakeRequests()
    {


    }

    void ClickButton::SetPosition(const sf::Vector2f &position)
    {
      v2fPostion = position;
    }

    void ClickButton::SetSize(const sf::Vector2f &size)
    {
      v2fSize = size;
    }

    void ClickButton::TickUpdate(const double &delta)
    {

    }

    void ClickButton::Render()
    {
      if (!ReadyToRender)
        return;

      Render::RenderShape(&ButtonShape);
      Render::RenderText(&ButtonText);
    }

    void ClickButton::OnShutDown()
    {

    }

  }
}
