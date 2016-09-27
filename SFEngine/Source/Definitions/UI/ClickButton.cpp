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
      ButtonShape = std::make_shared<sf::RectangleShape>();
      ButtonFont = std::make_shared<sf::Font>();
      ButtonTexture = std::make_shared<sf::Texture>();
      ButtonHighlightedTexture = std::make_shared<sf::Texture>();
      ButtonPressedTexture = std::make_shared<sf::Texture>();
      ButtonText = std::make_shared<sf::Text>();

      ButtonFont->loadFromFile("./SFEngine/Samples/Fonts/Raleway-Light.ttf");
      ButtonTexture->loadFromFile("./SFEngine/Samples/Textures/UI/ButtonBG.png");
      ButtonHighlightedTexture->loadFromFile("./SFEngine/Samples/Textures/UI/ButtonBGHovered.png");
      ButtonPressedTexture->loadFromFile("./SFEngine/Samples/Textures/UI/ButtonBGPressed.png");

      ButtonText->setColor(sf::Color::White);
      ButtonText->setFont(*ButtonFont.get());
      ButtonText->setString("Test String");
      ButtonShape->setTexture(ButtonTexture.get());

      RenderTarget tgt;
      tgt.SetDrawable(ButtonShape);
      tgt.SetDrawBounds(Render::DefaultBounds());

      AddRenderTarget(std::string("ButtonBG"), ButtonShape);

      RenderTarget txtTarget;
      txtTarget.SetDrawable(ButtonText);
      txtTarget.SetDrawBounds(Render::DefaultBounds());

      AddRenderTarget(std::string("ButtonText"), ButtonText);

      
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
      
    }

    ClickButton::~ClickButton()
    {

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
      ButtonShape->setTexture(ButtonHighlightedTexture.get());
    }

    void ClickButton::HandleMouseExit(const sf::Vector2i &pos)
    {
      ButtonShape->setTexture(ButtonTexture.get());
    }

    void ClickButton::HandleMouseMovement(const sf::Vector2i &pos)
    {
      std::cerr << "<<<Mouse moved on button" << std::endl;
    }

    void ClickButton::HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &b)
    {
      ButtonShape->setTexture(ButtonPressedTexture.get());
    }

    void ClickButton::HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &b)
    {
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

    void ClickButton::SetPosition(const sf::Vector2f &position)
    {
      v2fPostion = position;
      Align();
    }

    void ClickButton::SetSize(const sf::Vector2f &size)
    {
      v2fSize = size;
      Align();
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
