#include "DemoLoader.h"

#include "Projects\PuzzleDemo\Classes\Level1.h"

DemoLoadLevel::DemoLoadLevel()
  : BasicLevel(sf::Vector2u(1700, 900), sf::FloatRect(0, 0, 1700, 900))
{
  m_TestRing.SetColor(sf::Color::Red);
  m_TestRing.SetPosition(sf::Vector2f(500, 500));
  m_TestRing.SetRadius(40.f);

  m_NextLevel = std::make_shared<Level1>();
  m_SFMLCardFrontTexture = std::make_shared<sf::Texture>();
  m_SFMLCardFrontTexture->loadFromFile("./Projects/PuzzleDemo/Assets/Textures/Card Face - SFML.png");
  m_SFMLCardBackTexture = std::make_shared<sf::Texture>();
  m_SFMLCardBackTexture->loadFromFile("./Projects/PuzzleDemo/Assets/Textures/Card Back - SFML.png");
  m_SFMLCard.SetTextureFrontBack(m_SFMLCardFrontTexture, m_SFMLCardBackTexture, { 0, 0, 110, 150 }, { 0, 0 });
  
  m_SFMLCard.SetPosition(sf::Vector2f(550, 500));
  m_SFMLCard.SetDepth(40);
  m_SFMLCard.Center();
}

DemoLoadLevel::~DemoLoadLevel()
{
  m_TestRingTexture.reset();
}

void DemoLoadLevel::CleanUp()
{
}

void DemoLoadLevel::OnEnd()
{
}

void DemoLoadLevel::OnBegin()
{
  m_TestRing.FillTo(1.f, 2000.f);
  m_SFMLCard.Flip(750.f);
}

void DemoLoadLevel::OnShutDown()
{
}

void DemoLoadLevel::EventUpdate(sf::Event event)
{
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::W)
      m_TestRing.FillTo(1.f, 2000.f);
    else if (event.key.code == sf::Keyboard::S)
      m_TestRing.Empty(2000.f);
    else if (event.key.code == sf::Keyboard::C)
      m_TestRing.SetColor(sf::Color::White);
  }
}

void DemoLoadLevel::TickUpdate(const double & delta)
{
  m_TestRing.TickUpdate(delta);
  static sf::Clock _clock;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    m_SFMLCard.Rotate({ 0.f, 1.f, 0.f });
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    m_SFMLCard.Rotate({ 0.f, -1.f, 0.f });
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    m_SFMLCard.Rotate({ -1.f, 0.f, 0.f });
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    m_SFMLCard.Rotate({ 1.f, 0.f, 0.f });

  m_SFMLCard.TickUpdate(delta);
}

void DemoLoadLevel::HandleInputEvent(const Engine::UserEvent & evnt)
{
  if (evnt.EventType == Engine::UserEventType::MousePress) {
    Engine::SwitchLevel(m_NextLevel);
  }
  else if (evnt.EventType == Engine::UserEventType::KeyboardPress) {
    if (evnt.Key == sf::Keyboard::W)
      m_TestRing.FillTo(1.f, 1500.f);
    else if (evnt.Key == sf::Keyboard::S)
      m_TestRing.Empty(1500.f);
    else if (evnt.Key == sf::Keyboard::C)
      m_TestRing.SetColor(sf::Color::White);
  }
}

void DemoLoadLevel::Render(std::shared_ptr<sf::RenderTarget> Target)
{
}

void DemoLoadLevel::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
  m_TestRing.Render(Texture);
  m_SFMLCard.Render(Texture);
}

void DemoLoadLevel::SetNextLevel(std::shared_ptr<Engine::BasicLevel> NextLevel)
{
  m_NextLevel = NextLevel;
}

std::string DemoLoadLevel::GetClass() const
{
  return std::string("DemoLoadLevel");
}
