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
      ButtonText = std::make_shared<sf::Text>();

      ButtonFont->loadFromFile("./SFEngine/Samples/Fonts/OpenSans-Regular.ttf");
      ButtonTexture->loadFromFile("./SFEngine/Samples/Textures/UI/ButtonBG.png");

      ButtonText->setColor(sf::Color::White);
      ButtonShape->setTexture(ButtonTexture.get());

      RenderTarget tgt;
      tgt.SetDrawable(ButtonShape);
      tgt.SetDrawBounds(Render::DefaultBounds());

      AddRenderTarget(std::string("ButtonBG"), ButtonShape);
    }

    ClickButton::~ClickButton()
    {

    }

    void ClickButton::Align()
    {
      ButtonShape->setPosition(v2fPostion);
      ButtonShape->setSize(v2fSize);

      ButtonText->setCharacterSize(10);
      ButtonText->setPosition(sf::Vector2f(v2fPostion.x + 10, v2fPostion.y + 10));
      ButtonText->setString("Test String");

      RenderTargets["ButtonBG"].SetDrawBounds(ButtonShape->getGlobalBounds());
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
      Render::RenderShape(ButtonShape.get());
      Render::RenderText(ButtonText.get());
    }

    void ClickButton::OnShutDown()
    {

    }

  }
}
