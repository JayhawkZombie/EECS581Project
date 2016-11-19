#include "../../Headers/UI/ClickButton.h"

namespace Engine
{
  namespace UI
  {
    std::shared_ptr<ClickButton> ClickButton::Create()
    {
      return std::make_shared<ClickButton>();
    }


    ClickButton::ClickButton()
    {
      ReadyToRender = false;

      ButtonShape = std::make_shared<sf::RectangleShape>();
      ButtonFont = std::make_shared<sf::Font>();
      ButtonTexture = std::shared_ptr<sf::Texture>();
      ButtonHighlightedTexture = std::shared_ptr<sf::Texture>();
      ButtonPressedTexture = std::shared_ptr<sf::Texture>();
      ButtonText = std::make_shared<sf::Text>();

      //ButtonFont->loadFromFile("./SFEngine/Samples/Fonts/Raleway-Light.ttf");
      //ButtonTexture->loadFromFile("./SFEngine/Samples/Textures/UI/ButtonBG.png");
      //ButtonHighlightedTexture->loadFromFile("./SFEngine/Samples/Textures/UI/ButtonBGHovered.png");
      //ButtonPressedTexture->loadFromFile("./SFEngine/Samples/Textures/UI/ButtonBGPressed.png");
      ResourceManager->RequestTexture("./SFEngine/Samples/Textures/UI/ButtonBG.png", "ButtonBG", [this](std::shared_ptr<sf::Texture> t, const std::string &ID) {this->GetBGTexture(t, ID); });
      ResourceManager->RequestTexture("./SFEngine/Samples/Textures/UI/ButtonBGHovered.png", "ButtonHighlight", [this](std::shared_ptr<sf::Texture> t, const std::string &ID) {this->GetHighlightedTexture(t, ID); });
      ResourceManager->RequestTexture("./SFEngine/Samples/Textures/UI/ButtonBGPressed.png", "ButtonPressed", [this](std::shared_ptr<sf::Texture> t, const std::string &ID) {this->GetPressedTexture(t, ID); });
      ResourceManager->RequestFont("./SFEngine/Samples/Fonts/Raleway-Light.ttf", "ButtonFont", [this](std::shared_ptr<sf::Font> f, const std::string &ID) {this->GetFont(f, ID); });
      


      ButtonText->setFillColor(sf::Color::White);
      ButtonText->setFont(*ButtonFont.get());
      ButtonText->setString("Test String");
      //ButtonShape->setTexture(ButtonTexture.get());

      RenderTarget tgt;
      tgt.SetDrawable(ButtonShape);
      tgt.SetDrawBounds(Render::DefaultBounds());

      AddRenderTarget(std::string("ButtonBG"), ButtonShape);

      RenderTarget txtTarget;
      txtTarget.SetDrawable(ButtonText);
      txtTarget.SetDrawBounds(Render::DefaultBounds());

      AddRenderTarget(std::string("ButtonText"), ButtonText);
      
      KeyTarget kTgt;
      kTgt.Keys.set(sf::Keyboard::Return);
      kTgt.OnKeyPress = [this](const sf::Keyboard::Key &k) {this->HandleKeyPress(k); };
      kTgt.OnKeyRelease = [this](const sf::Keyboard::Key &k) {this->HandleKeyRelease(k); };

      AddKeyTarget(std::string("KeyTarget"), kTgt);
      
      MouseTarget mtgt;
      mtgt.MouseBounds = ButtonShape->getGlobalBounds();

      
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

    }

    void ClickButton::SerializeOut(std::ostream &out)
    {

    }

    void ClickButton::GetFont(std::shared_ptr<sf::Font> fnt, const std::string &ID)
    {
      std::cerr << "Whoooo! Setting button font" << std::endl;
      ButtonFont = fnt;
      ButtonText->setFont(*ButtonFont.get());
      ReadyToRender = (GotBGTexture && GotHighlightedTexture && GotPressedTexture);
      if (ReadyToRender) {
        State.set(Active);
        Align();
      }
    }

    void ClickButton::GetBGTexture(std::shared_ptr<sf::Texture> tex, const std::string &ID)
    {
      std::cerr << "Whoooo! Setting button BG texture" << std::endl;
      ButtonTexture = tex;
      GotBGTexture = true;
      ButtonShape->setTexture(ButtonTexture.get());
      ReadyToRender = (GotBGTexture && GotHighlightedTexture && GotPressedTexture);
      if (ReadyToRender) {
        State.set(Active);
        Align();
      }
    }

    void ClickButton::GetHighlightedTexture(std::shared_ptr<sf::Texture> tex, const std::string &ID)
    {
      std::cerr << "Whoooo! Setting highlighted texture" << std::endl;
      ButtonHighlightedTexture = tex;
      GotHighlightedTexture = true;
      ReadyToRender = (GotBGTexture && GotHighlightedTexture && GotPressedTexture);
      if (ReadyToRender) {
        State.set(Active);
        Align();
      }
    }

    void ClickButton::GetPressedTexture(std::shared_ptr<sf::Texture> tex, const std::string &ID)
    {
      std::cerr << "Whoooo! Setting pressed texture" << std::endl;
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
      ButtonShape->setPosition(v2fPostion);
      ButtonShape->setSize(v2fSize);

      ButtonText->setCharacterSize(14);
      float xDiff, yDiff;
      float textWidth = ButtonText->getGlobalBounds().width;
      float textHeight = ButtonText->getGlobalBounds().height;

      xDiff = (v2fSize.x - textWidth) / 2.f;
      yDiff = (v2fSize.y - textHeight) / 2.f;
      ButtonText->setPosition(
        xDiff > 0 ?
          sf::Vector2f(v2fPostion.x + xDiff, v2fPostion.y + yDiff)
        : sf::Vector2f(v2fPostion)
      );

      RenderTargets["ButtonBG"].SetDrawBounds(ButtonShape->getGlobalBounds());
      RenderTargets["ButtonText"].SetDrawBounds(ButtonShape->getGlobalBounds());
      sf::FloatRect r = ButtonShape->getGlobalBounds();

      MouseTargets["ButtonMouseRegion"].MouseBounds = ButtonShape->getGlobalBounds();
    }

    void ClickButton::HandleMouseOver(const sf::Vector2i &v)
    {
      if (ReadyToRender)
        ButtonShape->setTexture(ButtonHighlightedTexture.get());
    }

    void ClickButton::HandleMouseExit(const sf::Vector2i &pos)
    {
      if (ReadyToRender)
        ButtonShape->setTexture(ButtonTexture.get());
    }

    void ClickButton::HandleMouseMovement(const sf::Vector2i &pos)
    {
      //std::cerr << "<<<Mouse moved on button" << std::endl;
    }

    void ClickButton::HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &b)
    {
      if (ReadyToRender)
        ButtonShape->setTexture(ButtonPressedTexture.get());
    }

    void ClickButton::HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &b)
    {
      if (ReadyToRender)
        ButtonShape->setTexture(ButtonTexture.get());
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
      
    }

    void ClickButton::OnShutDown()
    {

    }

  }
}
