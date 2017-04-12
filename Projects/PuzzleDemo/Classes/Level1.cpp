#include "Level1.h"

#include "../../TestProject/Classes/Levels/OakTree.h"
#include "Levels\Stack.h"

Level1::Level1()
  : BasicLevel(sf::Vector2u( 1700, 900 ), sf::FloatRect(0, 0, 1700, 900 )),
  fader(0.1f, 0.1f)
{
  if (m_BGMusicBuffer.loadFromFile("./Projects/PuzzleDemo/Assets/Sound/Chamber-of-Jewels.ogg"))
    m_BGMusic.setBuffer(m_BGMusicBuffer);

  MainGUI = std::make_shared<tgui::Gui>(*Engine::currentRenderWindow);
  MenuTheme = std::make_shared<tgui::Theme>("./Projects/PuzzleDemo/Assets/UIThemes/TransparentGray.theme");
  font.loadFromFile("./Projects/TestProject/Fonts/Marvel-Regular.ttf");
  MainGUI->setFont(font);

  OakTreeLevelPtr    = std::make_shared<OakTreeLevel>();
  BallPuzzleLevelPtr = std::make_shared<BallStackLevel>();

  //Create some buttons
  LevelSelectButon = MenuTheme->load("button");
  LevelSelectButon->setPosition({ 25, 300 });
  LevelSelectButon->setSize({ 200, 55 });
  LevelSelectButon->connect("clicked", [this]() {this->ShowLevelSelectScreen(); });
  LevelSelectButon->setText("select test level");
  LevelSelectButon->setTextSize(20);
  LevelSelectButon->hide();
  //MainGUI->add(NewGameButton, "NewGameButton");

  OptionsPanel = MenuTheme->load("panel");
  OptionsPanel->setSize({ 1700, 900 });

  LoadGameButton = MenuTheme->load("button");
  LoadGameButton->setPosition({ 25, 425 });
  LoadGameButton->setSize({ 200, 55 });
  LoadGameButton->setText("load game");
  LoadGameButton->setTextSize(20);
  LoadGameButton->disable();
  LoadGameButton->getRenderer()->setTextColor(sf::Color(180, 180, 180));
  LoadGameButton->hide();
  //MainGUI->add(LoadGameButton, "LoadGameButton");

  AboutButton = MenuTheme->load("button");
  AboutButton->setPosition({ 25, 550 });
  AboutButton->setSize({ 200, 55 });
  AboutButton->connect("clicked", [this]() {this->ShowAboutScreen(); });
  AboutButton->setText("about");
  AboutButton->setTextSize(20);
  AboutButton->hide();
  //MainGUI->add(AboutButton, "AboutButton");

  OptionsButton = MenuTheme->load("button");
  OptionsButton->setPosition({ 25, 675 });
  OptionsButton->setSize({ 200, 55 });
  OptionsButton->connect("clicked", [this]()
  {
    this->MainPanel->disable();
    this->MainPanel->hideWithEffect(tgui::ShowAnimationType::SlideToLeft, sf::milliseconds(250));
    this->OptionsPanel->enable();
    this->OptionsPanel->showWithEffect(tgui::ShowAnimationType::SlideFromRight, sf::milliseconds(250));
  });

  OptionsButton->setText("options");
  OptionsButton->setTextSize(20);

  CloseButton = MenuTheme->load("button");
  CloseButton->setPosition({ 25, 800 });
  CloseButton->setSize({ 200, 55 });
  CloseButton->setText("quit");
  CloseButton->setTextSize(20);
  CloseButton->hide();
  CloseButton->connect("clicked", Engine::Shutdown);
  // MainGUI->add(CloseButton);

  tgui::Button::Ptr OptionsBack = MenuTheme->load("button");
  OptionsBack->setPosition({ 25, 425 });
  OptionsBack->setSize({ 200, 55 });
  OptionsBack->setText("back");
  OptionsBack->setTextSize(20);
  OptionsBack->connect("clicked", [this]()
  {
    this->OptionsPanel->disable();
    this->OptionsPanel->hideWithEffect(tgui::ShowAnimationType::SlideToRight, sf::milliseconds(250));
    this->MainPanel->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(250));
    this->MainPanel->enable();
  });
  OptionsPanel->add(OptionsBack);

  MainPanel = MenuTheme->load("panel");
  MainPanel->setSize({ 1700, 900 });
  MainPanel->add(LevelSelectButon);
  MainPanel->add(LoadGameButton);
  MainPanel->add(AboutButton);
  MainPanel->add(OptionsButton);
  MainPanel->add(CloseButton);

  LevelSelectPanel = MenuTheme->load("panel");
  LevelSelectPanel->setSize({ 1700, 900 });
  
  tgui::Button::Ptr OakTreeLevel = MenuTheme->load("button");
  OakTreeLevel->setPosition({ 25, 450 });
  OakTreeLevel->setSize({ 200, 55 });
  OakTreeLevel->setText("Oak Tree");
  OakTreeLevel->setTextSize(20);
  OakTreeLevel->connect("clicked", [this]() { Engine::SwitchLevel(this->OakTreeLevelPtr); });
  LevelSelectPanel->add(OakTreeLevel);

  tgui::Button::Ptr BallLevel = MenuTheme->load("button");
  BallLevel->setPosition({ 25, 575 });
  BallLevel->setSize({ 200, 25 });
  BallLevel->setText("Ball Puzzle");
  BallLevel->setTextSize(20);
  BallLevel->connect("clicked", [this]() {Engine::SwitchLevel(this->BallPuzzleLevelPtr); });
  LevelSelectPanel->add(BallLevel);

  LevelSelectBack = MenuTheme->load("button");
  LevelSelectBack->setPosition({ 25, 700 });
  LevelSelectBack->setSize({ 200, 55 });
  LevelSelectBack->setText("back");
  LevelSelectBack->setTextSize(20);
  LevelSelectBack->connect("clicked", [this]() {this->LevelSelectGoBack(); });
  LevelSelectPanel->add(LevelSelectBack);

  LevelSelectPanel->hide();

  OptionsPanel->hide();
  OptionsPanel->disable();

  MainGUI->add(MainPanel);
  MainGUI->add(OptionsPanel);
  MainGUI->add(LevelSelectPanel);

  texture.loadFromFile("./Projects/TestProject/Textures/particle.png");
  emitter.setEmissionRate(85.f);
  emitter.setParticleLifetime(sf::seconds(6));

  system.setTexture(texture);
  system.addEmitter(thor::refEmitter(emitter));

  emitter.setParticlePosition(sf::Vector2f(0, 0));
  emitter.setParticleScale(sf::Vector2f(0.4f, 0.3f));

  gradient[0.f] = sf::Color(0, 242, 255);
  gradient[0.5f] = sf::Color(0, 106, 112, 112);
  gradient[1.f] = sf::Color(0, 0, 0, 0);

  colorizer = new thor::ColorAnimation(gradient);

  system.addAffector(thor::AnimationAffector(*colorizer));
  system.addAffector(thor::AnimationAffector(fader));
  system.addAffector(thor::TorqueAffector(150.f));
  system.addAffector(thor::ForceAffector(sf::Vector2f(0.f, 50.f)));
  velocity = thor::PolarVector2f(200.f, -90.f);
}

Level1::~Level1()
{
  
}

void Level1::TickUpdate(const double & delta)
{
  static sf::Clock thorClock;
  m_WeatherSystem.TickUpdate(delta);

  static sf::Time _time = sf::seconds(0);
  static sf::Clock _clock;
  static bool shown = false;
  if (!shown) {
    shown = true;
    LevelSelectButon->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
    LoadGameButton->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
    AboutButton->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
    CloseButton->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
    MainPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(150));
  }
  emitter.setParticlePosition(thor::Distributions::rect({ 1700 / 2.f, 900 / 2.f }, { 1700 / 2.f, 900 / 2.f }));
  system.update(fClock.restart());
  MainGUI->updateTime(_clock.restart());
}

void Level1::Render(std::shared_ptr<sf::RenderTarget> Target)
{
}

void Level1::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
  Texture->clear(sf::Color::Transparent);
  Texture->draw(system);

  m_WeatherSystem.Render(Texture);
  MainGUI->draw();
}

void Level1::OnShutDown()
{
}

void Level1::HandleInputEvent(const Engine::UserEvent & evnt)
{
  if (evnt.EventType == Engine::UserEventType::KeyboardPress) {
    if (evnt.Key == sf::Keyboard::Key::Escape)
      m_Paused = !m_Paused;
  }
}

void Level1::EventUpdate(sf::Event event)
{
  MainGUI->handleEvent(event);
}

void Level1::OnBegin()
{
  std::cerr << "Level1::OnBegin()" << std::endl;
  m_BGMusic.setLoop(true);
  m_BGMusic.play();
}

void Level1::OnEnd()
{
  m_BGMusic.stop();
}

void Level1::CreateNewGame()
{
}

void Level1::LoadSaveGame()
{
}

void Level1::EraseSaveGame()
{
}

void Level1::ShowAboutScreen()
{
}

void Level1::ShowLevelSelectScreen()
{
  MainPanel->hideWithEffect(tgui::ShowAnimationType::SlideToLeft, sf::milliseconds(250));
  MainPanel->disable();

  LevelSelectPanel->showWithEffect(tgui::ShowAnimationType::SlideFromRight, sf::milliseconds(250));
  LevelSelectPanel->enable();
}

void Level1::LevelSelectGoBack()
{
  MainPanel->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(250));
  MainPanel->enable();

  LevelSelectPanel->hideWithEffect(tgui::ShowAnimationType::SlideToRight, sf::milliseconds(250));
  LevelSelectPanel->disable();
}

