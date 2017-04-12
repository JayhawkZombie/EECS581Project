#include "Stack.h"
#include "../../../../SFEngine/Source/Headers/Physics/Collider.h"

BallStackLevel::BallStackLevel()
  : BasicLevel(sf::Vector2u(1700, 900), sf::FloatRect(0, 0, 1700, 900))
{
  if (!m_BGMusic.openFromFile("./Projects/PuzzleDemo/Assets/Sound/Defending-the-Princess-Haunted.ogg")) {
    std::cerr << "Unable to load background music for PuzzleBall level" << std::endl;
  }
  if (m_TimeSlowDownBuffer.loadFromFile("./Projects/PuzzleDemo/Assets/Sound/109210__benboncan__slowdown.wav"))
    m_TimeSlowDownSound.setBuffer(m_TimeSlowDownBuffer);

  if (m_TimeSpeedUpBuffer.loadFromFile("./Projects/PuzzleDemo/Assets/Sound/123438__anomalous-underdog__slowdown-short-up.wav"))
    m_TimeSpeedUpSound.setBuffer(m_TimeSpeedUpBuffer);

  if (m_BallSpawnBuffer.loadFromFile("./Projects/PuzzleDemo/Assets/Sound/BallSpawn.ogg"))
    m_BallSpawnSound.setBuffer(m_BallSpawnBuffer);

  //m_GameMenu = std::make_shared<tgui::Gui>(*Engine::currentRenderWindow);
  m_MenuFont.loadFromFile("./Projects/TestProject/Fonts/Marvel-Regular.ttf");
  //m_GameMenu->setFont(m_MenuFont);

  m_PipeLeftWall = Engine::BuildSegmentMesh('n', sf::Vector2i(450 + 325, 0), sf::Vector2i(450 + 325, 400));
  m_PipeWallRight = Engine::BuildSegmentMesh('n', sf::Vector2i(1250 - 325, 0),   sf::Vector2i(1250 - 325,        400));
  m_PipeDropBlock = Engine::BuildSegmentMesh('n', sf::Vector2i(450  + 325, 400), sf::Vector2i(450  + 325 + 150,  400));
  Segments.push_back(m_PipeLeftWall);
  Segments.push_back(m_PipeWallRight);
  Segments.push_back(m_PipeDropBlock);

  m_BallKillerBolt = std::make_shared<Engine::LightningBolt>();

  Engine::AssignBoundaries(900, 1700);
  Gravity->x = 0;
  Gravity->y = 0.0f;

  Engine::SetGravity(Gravity);

  Segments.push_back(Engine::BuildSegmentMesh('n', sf::Vector2i(450,  0),   sf::Vector2i(450,       300))); //Left wall of resiv.
  Segments.push_back(Engine::BuildSegmentMesh('n', sf::Vector2i(1250, 0),   sf::Vector2i(1250,      300))); //Right wall of resiv.
  Segments.push_back(Engine::BuildSegmentMesh('n', sf::Vector2i(450,  300), sf::Vector2i(450 + 325, 400))); //Left sloped wall of resiv.
  Segments.push_back(Engine::BuildSegmentMesh('n', sf::Vector2i(1250, 300), sf::Vector2i(925,       400))); //Right sloped wall of resiv.
  Segments.push_back(Engine::BuildSegmentMesh('n', sf::Vector2i(450 + 300, 600), sf::Vector2i(450 + 300, 900)));
  Segments.push_back(Engine::BuildSegmentMesh('n', sf::Vector2i(450 + 500, 600), sf::Vector2i(450 + 500, 900)));

  m_BallKillerBolt->Spark({ 750, 600 }, { 950, 600 });
  m_BallKillerBolt->SetPosition({ 750, 600 });
  m_BallKillerBolt->SetSize({ 200, 50 });

  auto m_BoltCollider = Engine::Collider2D::CreatePolygonMesh(4, 300, 0, sf::Vector2f(950, 600), sf::Vector2f(0, 0), 0.01f, 0.0f, sf::Color::Transparent);
  m_BoltCollider->SetCollisionCallback([this](std::weak_ptr<Engine::Collider2D> Collider) {this->CheckBallAndBolt(Collider); });
  m_BoltCollider->SetObjectPtr(m_BallKillerBolt.get());
  m_BallKillerBolt->AddCollider(m_BoltCollider);
  SpawnAutoGeneratedObject(m_BallKillerBolt, "BallKillerBolt");

  m_LevelTheme = std::make_shared<tgui::Theme>("./Projects/PuzzleDemo/Assets/UIThemes/TransparentGray.theme");

  m_PausePanel = m_LevelTheme->load("panel");
  m_PausePanel->setSize({ 1700, 900 });
  
  m_QuitButton = m_LevelTheme->load("button");
  m_QuitButton->setSize({ 150, 35 });
  m_QuitButton->setPosition({ 775, 432.5 });
  m_QuitButton->setText("quit");
  m_QuitButton->connect("clicked", []() { Engine::LoadMainLevel(); });

  m_PausePanel->add(m_QuitButton);
  m_PausePanel->enable();
  m_PausePanel->hide();
  //m_GameMenu->add(m_PausePanel);

  Engine::GUI->add(m_PausePanel);

  Engine::CurrentLevel = this;
}

BallStackLevel::~BallStackLevel()
{
}

void BallStackLevel::TickUpdate(const double & delta)
{
  BasicLevel::TickUpdate(delta);

  static sf::Clock GUITimer;

  //m_GameMenu->updateTime(GUITimer.restart());
}

void BallStackLevel::Render(std::shared_ptr<sf::RenderTarget> Target)
{
}

void BallStackLevel::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
  //m_GameMenu->draw();

  BasicLevel::RenderOnTexture(Texture);

  for (auto & seg : Segments)
    seg->draw(*Texture);
}

void BallStackLevel::OnShutDown()
{
}

void BallStackLevel::HandleInputEvent(const Engine::UserEvent & evnt)
{
  if (evnt.EventType == Engine::UserEventType::KeyboardPress) {
    if (evnt.IsButtonPressed(sf::Keyboard::Escape))
      if (m_Paused)
        HideMenu();
      else
        ShowMenu();
  }
  else if (!m_Paused) {
    if (evnt.EventType == Engine::UserEventType::MousePress)
      HandleUserClick(evnt.CurrentMousePosition);
  }
}

void BallStackLevel::EventUpdate(sf::Event event)
{
  //m_GameMenu->handleEvent(event);
}

void BallStackLevel::OnBegin()
{
  m_BGMusic.play();
  m_BallSpawnSound.play();

  SpawnBall();
}

void BallStackLevel::OnEnd()
{
  m_BGMusic.stop();

  BasicLevel::OnEnd();
}

void BallStackLevel::Reset()
{
}

void BallStackLevel::UpdateObjectPhysics()
{
  BasicLevel::UpdateObjectPhysics();

  m_BallKillerBolt->Spark({ 750, 600 }, { 950, 600 });
}

void BallStackLevel::HandleUserClick(sf::Vector2i Pos)
{

}

void BallStackLevel::CheckBallAndBolt(std::weak_ptr<Engine::Collider2D> Collider)
{
}

void BallStackLevel::LaunchBall()
{
}

void BallStackLevel::SpawnBall()
{
  std::shared_ptr<PuzzleBall> Ball = std::make_shared<PuzzleBall>();
  Ball->AddCollider(Engine::Collider2D::CreateCircularMesh(
    Engine::MeshType::Ball, sf::Vector2f(835, 40), sf::Vector2f(0, 0), 30, 3.f, 0.4f, sf::Color::Blue));
  SpawnAutoGeneratedObject(Ball, "PuzzleBall");
  m_CurrentBall = Ball;
}

void BallStackLevel::KillBall()
{
  m_CurrentBall.reset();
}

void BallStackLevel::ShowMenu()
{
  m_Paused = true;
  m_PausePanel->enable();
  m_PausePanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(250));
  m_QuitButton->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(250));
}

void BallStackLevel::HideMenu()
{
  m_Paused = false;
  m_PausePanel->disable();
  m_PausePanel->hideWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(250));
  m_QuitButton->hideWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(250));
}
