#include "Level1.h"

Level1::Level1()
  : BasicLevel(sf::Vector2u( 1700, 900 ), sf::FloatRect(0, 0, 1700, 900 )),
  fader(0.1f, 0.1f)
{
  MainGUI = std::make_shared<tgui::Gui>(*Engine::currentRenderWindow);
  MenuTheme = std::make_shared<tgui::Theme>("./Projects/TestProject/UIThemes/TransparentGray.theme");
  font.loadFromFile("./Projects/TestProject/Fonts/Marvel-Regular.ttf");
  MainGUI->setFont(font);

  //Create some buttons
  NewGameButton = MenuTheme->load("button");
  NewGameButton->setPosition({ 25, 25 });
  NewGameButton->setSize({ 200, 75 });
  NewGameButton->connect("clicked", [this]() {this->CreateNewGame(); });
  NewGameButton->setText("new game");
  NewGameButton->setTextSize(20);
  NewGameButton->hide();
  //MainGUI->add(NewGameButton, "NewGameButton");

  OptionsPanel = MenuTheme->load("panel");
  OptionsPanel->setSize({ 1700, 900 });

  LoadGameButton = MenuTheme->load("button");
  LoadGameButton->setPosition({ 25, 225 });
  LoadGameButton->setSize({ 200, 75 });
  LoadGameButton->setText("load game");
  LoadGameButton->setTextSize(20);
  LoadGameButton->disable();
  LoadGameButton->getRenderer()->setTextColor(sf::Color(180, 180, 180));
  LoadGameButton->hide();
  //MainGUI->add(LoadGameButton, "LoadGameButton");

  AboutButton = MenuTheme->load("button");
  AboutButton->setPosition({ 25, 425 });
  AboutButton->setSize({ 200, 75 });
  AboutButton->connect("clicked", [this]() {this->ShowAboutScreen(); });
  AboutButton->setText("about");
  AboutButton->setTextSize(20);
  AboutButton->hide();
  //MainGUI->add(AboutButton, "AboutButton");

  OptionsButton = MenuTheme->load("button");
  OptionsButton->setPosition({ 25, 625 });
  OptionsButton->setSize({ 200, 75 });
  OptionsButton->connect("clicked", [this]()
  {
    this->MainPanel->disable();
    this->MainPanel->hideWithEffect(tgui::ShowAnimationType::SlideToLeft, sf::milliseconds(500));
    this->OptionsPanel->enable();
    this->OptionsPanel->showWithEffect(tgui::ShowAnimationType::SlideFromRight, sf::milliseconds(500));
  });

  OptionsButton->setText("options");
  OptionsButton->setTextSize(20);

  CloseButton = MenuTheme->load("button");
  CloseButton->setPosition({ 25, 825 });
  CloseButton->setSize({ 200, 75 });
  CloseButton->setText("quit");
  CloseButton->setTextSize(20);
  CloseButton->hide();
  CloseButton->connect("clicked", Engine::Shutdown);
  // MainGUI->add(CloseButton);

  tgui::Button::Ptr OptionsBack = MenuTheme->load("button");
  OptionsBack->setPosition({ 25, 425 });
  OptionsBack->setSize({ 200, 75 });
  OptionsBack->setText("back");
  OptionsBack->setTextSize(20);
  OptionsBack->connect("clicked", [this]()
  {
    this->OptionsPanel->disable();
    this->OptionsPanel->hideWithEffect(tgui::ShowAnimationType::SlideToRight, sf::milliseconds(500));
    this->MainPanel->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
    this->MainPanel->enable();
  });
  OptionsPanel->add(OptionsBack);

  MainPanel = MenuTheme->load("panel");
  MainPanel->setSize({ 1700, 900 });
  MainPanel->add(NewGameButton);
  MainPanel->add(LoadGameButton);
  MainPanel->add(AboutButton);
  MainPanel->add(OptionsButton);
  MainPanel->add(CloseButton);

  OptionsPanel->hide();
  OptionsPanel->disable();

  MainGUI->add(MainPanel);
  MainGUI->add(OptionsPanel);

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

  m_BoltTopLeft.TickUpdate(delta);
  m_BoltTopRight.TickUpdate(delta);
  m_BoltBottomLeft.TickUpdate(delta);
  m_BoltBottomRight.TickUpdate(delta);

  m_WeatherSystem.TickUpdate(delta);
  for (int i = 0; i < 32; ++i)
    m_CrawlBolts[i].TickUpdate(delta);

  static sf::Time _time = sf::seconds(0);
  static sf::Clock _clock;
  static bool shown = false;
  if (!shown) {
    shown = true;
    NewGameButton->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
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
  m_BoltTopLeft.Render(Texture);
  m_BoltTopRight.Render(Texture);
  m_BoltBottomLeft.Render(Texture);
  m_BoltBottomRight.Render(Texture);

  m_WeatherSystem.Render(Texture);
  for (int i = 0; i < 32; ++i)
    m_CrawlBolts[i].Render(Texture);
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
    else if (evnt.Key == sf::Keyboard::Key::Up)
      m_LightningStorm->IncreaseIntensity(1);
    else if (evnt.Key == sf::Keyboard::Key::Down)
      m_LightningStorm->DecreaseIntensity(1);
  }
  else if (evnt.EventType == Engine::UserEventType::MousePress) {
    if (!m_BoltTopLeft.IsAlive() && !m_BoltTopRight.IsAlive() && !m_BoltBottomLeft.IsAlive() && !m_BoltBottomRight.IsAlive()) {
      m_BoltTopLeft.Spark({ 0, 0 }, static_cast<sf::Vector2f>(evnt.CurrentMousePosition));
      m_BoltTopRight.Spark({ 1700, 0 }, static_cast<sf::Vector2f>(evnt.CurrentMousePosition));
      m_BoltBottomLeft.Spark({ 0, 900 }, static_cast<sf::Vector2f>(evnt.CurrentMousePosition));
      m_BoltBottomRight.Spark({ 1700, 900 }, static_cast<sf::Vector2f>(evnt.CurrentMousePosition));

      
    }
  }
}

void Level1::EventUpdate(sf::Event event)
{
  MainGUI->handleEvent(event);
}

void Level1::OnBegin()
{
  TriggerCrawlingLightning();
}

void Level1::TriggerCrawlingLightning()
{
  m_drawflare = false;

  sf::Vector2f TopMid    = { 1700.f / 2.f, 0.f         };
  sf::Vector2f TopLeft   = { 0.f         , 0.f         };
  sf::Vector2f TopRight  = { 1700.f      , 0.f         };
  sf::Vector2f BtmRight  = { 1700.f      , 900.f       };
  sf::Vector2f BtmLeft   = { 0.f         , 900.f       };
  sf::Vector2f LeftMid   = { 0.f,          900.f / 2.f };
  sf::Vector2f RightMid  = { 1700.f,       900.f / 2.f };
  sf::Vector2f BottomMid = { 1700.f / 2.f, 900.f       };
  sf::Vector2f Center    = { 1700.f / 2.f, 900.f / 2.f };
  /*
    Letter layout
    S
        (0, 0)
        *___________________________* (214, 0)
        |      (22, 22)             |
        |     *____________________*| (214, 22)
        |     | (22, 44)
        |     |*____________________* (214, 44)
        |              (192, 66)    |
        |_____________________*     |
  (0, 88)                     |     |
        *____________________*|     |
        |                (192, 88)  |
(0, 110)|*_________________________*| (214, 110)
   */

  sf::Vector2f S1  = { 0,   0 };
  sf::Vector2f S2  = { 214, 0 };
  sf::Vector2f S3  = { 214, 22 };
  sf::Vector2f S4  = { 22,  22 };
  sf::Vector2f S5  = { 22,  44 };
  sf::Vector2f S6  = { 214, 44 };
  sf::Vector2f S7  = { 214, 110 };
  sf::Vector2f S8  = { 0,   110 };
  sf::Vector2f S9  = { 0,   88 };
  sf::Vector2f S10 = { 192, 88 };
  sf::Vector2f S11 = { 192, 66 };
  sf::Vector2f S12 = { 0,   66 };

  sf::Vector2f F1  = { 0,   0 };
  sf::Vector2f F2  = { 214, 0 };
  sf::Vector2f F3  = { 214, 22 };
  sf::Vector2f F4  = { 22,  22 };
  sf::Vector2f F5  = { 22,  44 };
  sf::Vector2f F6  = { 214, 44 };
  sf::Vector2f F7  = { 214, 66 };
  sf::Vector2f F8  = { 22,  66 };
  sf::Vector2f F9  = { 22,  110 };
  sf::Vector2f F10 = { 0,   110 };

  sf::Vector2f E1  = { 0,   0 };
  sf::Vector2f E2  = { 214, 0 };
  sf::Vector2f E3  = { 214, 22 };
  sf::Vector2f E4  = { 22,  22 };
  sf::Vector2f E5  = { 22,  44 };
  sf::Vector2f E6  = { 214, 44 };
  sf::Vector2f E7  = { 214, 66 };
  sf::Vector2f E8  = { 22,  66 };
  sf::Vector2f E9  = { 22,  88 };
  sf::Vector2f E10 = { 214, 88 };
  sf::Vector2f E11 = { 214, 110 };
  sf::Vector2f E12 = { 0,   110 };

  sf::Vector2f N1 = { 0,   0 };
  sf::Vector2f N2 = { 110, 0 };
  sf::Vector2f N3 = { 110, 110 };
  sf::Vector2f N4 = { 88,  110 };
  sf::Vector2f N5 = { 88,  22 };
  sf::Vector2f N6 = { 22,  22 };
  sf::Vector2f N7 = { 22,  110 };
  sf::Vector2f N8 = { 0,   110 };

  sf::Vector2f G1  = { 0,   0 };
  sf::Vector2f G2  = { 214, 0 };
  sf::Vector2f G3  = { 214, 22 };
  sf::Vector2f G4  = { 22,  22 };
  sf::Vector2f G5  = { 22,  88 };
  sf::Vector2f G6  = { 192, 88 };
  sf::Vector2f G7  = { 192, 66 };
  sf::Vector2f G8  = { 80,  66 };
  sf::Vector2f G9  = { 80,  44 };
  sf::Vector2f G10 = { 214, 44 };
  sf::Vector2f G11 = { 214, 110 };
  sf::Vector2f G12 = { 0,   110 };

  sf::Vector2f I1 = { 0,  0 };
  sf::Vector2f I2 = { 22, 0 };
  sf::Vector2f I3 = { 22, 110 };
  sf::Vector2f I4 = { 0,  110 };

  float Scale = 1.18f;

  sf::Vector2f STopLeft  = { 0, 500 };
  sf::Vector2f FTopLeft  = STopLeft  + sf::Vector2f(Scale * 214, 0) + sf::Vector2f(Scale * 22, 0);
  sf::Vector2f ETopLeft  = FTopLeft  + sf::Vector2f(Scale * 214, 0) + sf::Vector2f(Scale * 22, 0);
  sf::Vector2f NTopLeft  = ETopLeft  + sf::Vector2f(Scale * 214, 0) + sf::Vector2f(Scale * 22, 0);
  sf::Vector2f GTopLeft  = NTopLeft  + sf::Vector2f(Scale * 110, 0) + sf::Vector2f(Scale * 22, 0);
  sf::Vector2f ITopLeft  = GTopLeft  + sf::Vector2f(Scale * 214, 0) + sf::Vector2f(Scale * 22, 0);
  sf::Vector2f N2TopLeft = ITopLeft  + sf::Vector2f(Scale * 22,  0) + sf::Vector2f(Scale * 22, 0);
  sf::Vector2f E2TopLeft = N2TopLeft + sf::Vector2f(Scale * 110, 0) + sf::Vector2f(Scale * 22, 0);

  std::vector<sf::Vector2f> STrace = {
    //Letter S tracing
    STopLeft + Scale * S8,   STopLeft + Scale * S9,   STopLeft + Scale * S10,
    STopLeft + Scale * S11,  STopLeft + Scale * S12,  STopLeft + Scale * S1,
    STopLeft + Scale * S2,   STopLeft + Scale * S3,   STopLeft + Scale * S4,
    STopLeft + Scale * S5,   STopLeft + Scale * S6,   STopLeft + Scale * S7,
    STopLeft + Scale * S8
  };

  std::vector<sf::Vector2f> STrace2 = {
    //Letter S tracing, path 2
    STopLeft + Scale * S8,  STopLeft + Scale * S7,   STopLeft + Scale * S6,
    STopLeft + Scale * S5,  STopLeft + Scale * S4,   STopLeft + Scale * S3,
    STopLeft + Scale * S2,  STopLeft + Scale * S1,   STopLeft + Scale * S12,
    STopLeft + Scale * S11, STopLeft + Scale * S10,  STopLeft + Scale * S9,
    STopLeft + Scale * S8
  };

  std::vector<sf::Vector2f> FTrace = {
    FTopLeft + Scale * F10, FTopLeft + Scale * F9, FTopLeft + Scale * F8,
    FTopLeft + Scale * F7,  FTopLeft + Scale * F6, FTopLeft + Scale * F5,
    FTopLeft + Scale * F4,  FTopLeft + Scale * F3, FTopLeft + Scale * F2,
    FTopLeft + Scale * F1,  FTopLeft + Scale * F10
  };

  std::vector<sf::Vector2f> FTrace2 = {
    FTopLeft + Scale * F10, FTopLeft + Scale * F1, FTopLeft + Scale * F2,
    FTopLeft + Scale * F3,  FTopLeft + Scale * F4, FTopLeft + Scale * F5,
    FTopLeft + Scale * F6,  FTopLeft + Scale * F7, FTopLeft + Scale * F8,
    FTopLeft + Scale * F9,  FTopLeft + Scale * F10
  };

  std::vector<sf::Vector2f> ETrace = {
    ETopLeft + Scale * E12, ETopLeft + Scale * E11, ETopLeft + Scale * E10,
    ETopLeft + Scale * E9,  ETopLeft + Scale * E8,  ETopLeft + Scale * E7,
    ETopLeft + Scale * E6,  ETopLeft + Scale * E5,  ETopLeft + Scale * E4,
    ETopLeft + Scale * E3,  ETopLeft + Scale * E2,  ETopLeft + Scale * E1,
    ETopLeft + Scale * E12
  };

  std::vector<sf::Vector2f> ETrace2 = {
    ETopLeft + Scale * E12, ETopLeft + Scale * E1,  ETopLeft + Scale * E2,
    ETopLeft + Scale * E3,  ETopLeft + Scale * E4,  ETopLeft + Scale * E5,
    ETopLeft + Scale * E6,  ETopLeft + Scale * E7,  ETopLeft + Scale * E8,
    ETopLeft + Scale * E9,  ETopLeft + Scale * E10, ETopLeft + Scale * E11,
    ETopLeft + Scale * E12
  };

  std::vector<sf::Vector2f> NTrace = {
    NTopLeft + Scale * N7, NTopLeft + Scale * N8, NTopLeft + Scale * N1,
    NTopLeft + Scale * N2, NTopLeft + Scale * N3, NTopLeft + Scale * N4,
    NTopLeft + Scale * N5, NTopLeft + Scale * N6, NTopLeft + Scale * N7,
    NTopLeft + Scale * N8, NTopLeft + Scale * N1, NTopLeft + Scale * N2,
    NTopLeft + Scale * N3
  };

  std::vector<sf::Vector2f> NTrace2 = {
    NTopLeft + Scale * N4, NTopLeft + Scale * N3, NTopLeft + Scale * N2,
    NTopLeft + Scale * N1, NTopLeft + Scale * N8, NTopLeft + Scale * N7,
    NTopLeft + Scale * N6, NTopLeft + Scale * N5, NTopLeft + Scale * N4,
    NTopLeft + Scale * N3, NTopLeft + Scale * N2, NTopLeft + Scale * N1,
    NTopLeft + Scale * N8
  };

  std::vector<sf::Vector2f> GTrace = {
    GTopLeft + Scale * G12,
    GTopLeft + Scale * G1,  GTopLeft + Scale * G2,  GTopLeft + Scale * G3,
    GTopLeft + Scale * G4,  GTopLeft + Scale * G5,  GTopLeft + Scale * G6,
    GTopLeft + Scale * G7,  GTopLeft + Scale * G8,  GTopLeft + Scale * G9,
    GTopLeft + Scale * G10, GTopLeft + Scale * G11, GTopLeft + Scale * G12
  };

  std::vector<sf::Vector2f> GTrace2 = {
    GTopLeft + Scale * G1,
    GTopLeft + Scale * G12, GTopLeft + Scale * G11, GTopLeft + Scale * G10,
    GTopLeft + Scale * G9,  GTopLeft + Scale * G8,  GTopLeft + Scale * G7,
    GTopLeft + Scale * G6,  GTopLeft + Scale * G5,  GTopLeft + Scale * G4,
    GTopLeft + Scale * G3,  GTopLeft + Scale * G2,  GTopLeft + Scale * G1
  };

  std::vector<sf::Vector2f> ITrace = {
    ITopLeft + Scale * I4, ITopLeft + Scale * I1, 
    ITopLeft + Scale * I2, ITopLeft + Scale * I3,
    ITopLeft + Scale * I4, ITopLeft + Scale * I1,
    ITopLeft + Scale * I2, ITopLeft + Scale * I3
  };

  std::vector<sf::Vector2f> ITrace2 = {
    ITopLeft + Scale * I4, ITopLeft + Scale * I3,
    ITopLeft + Scale * I2, ITopLeft + Scale * I1,
    ITopLeft + Scale * I4, ITopLeft + Scale * I3,
    ITopLeft + Scale * I2, ITopLeft + Scale * I1
  };

  std::vector<sf::Vector2f> N2Trace = {
    N2TopLeft + Scale * N7, N2TopLeft + Scale * N8, N2TopLeft + Scale * N1,
    N2TopLeft + Scale * N2, N2TopLeft + Scale * N3, N2TopLeft + Scale * N4,
    N2TopLeft + Scale * N5, N2TopLeft + Scale * N6, N2TopLeft + Scale * N7,
    N2TopLeft + Scale * N8, N2TopLeft + Scale * N1, N2TopLeft + Scale * N2,
    N2TopLeft + Scale * N3
  };

  std::vector<sf::Vector2f> N2Trace2 = {
    N2TopLeft + Scale * N4, N2TopLeft + Scale * N3, N2TopLeft + Scale * N2,
    N2TopLeft + Scale * N1, N2TopLeft + Scale * N8, N2TopLeft + Scale * N7,
    N2TopLeft + Scale * N6, N2TopLeft + Scale * N5, N2TopLeft + Scale * N4,
    N2TopLeft + Scale * N3, N2TopLeft + Scale * N2, N2TopLeft + Scale * N1,
    N2TopLeft + Scale * N8
  };

  std::vector<sf::Vector2f> E2Trace = {
    E2TopLeft + Scale * E12, E2TopLeft + Scale * E11, E2TopLeft + Scale * E10,
    E2TopLeft + Scale * E9,  E2TopLeft + Scale * E8,  E2TopLeft + Scale * E7,
    E2TopLeft + Scale * E6,  E2TopLeft + Scale * E5,  E2TopLeft + Scale * E4,
    E2TopLeft + Scale * E3,  E2TopLeft + Scale * E2,  E2TopLeft + Scale * E1,
    E2TopLeft + Scale * E12
  };

  std::vector<sf::Vector2f> E2Trace2 = {
    E2TopLeft + Scale * E12, E2TopLeft + Scale * E1,  E2TopLeft + Scale * E2,
    E2TopLeft + Scale * E3,  E2TopLeft + Scale * E4,  E2TopLeft + Scale * E5,
    E2TopLeft + Scale * E6,  E2TopLeft + Scale * E7,  E2TopLeft + Scale * E8,
    E2TopLeft + Scale * E9,  E2TopLeft + Scale * E10, E2TopLeft + Scale * E11,
    E2TopLeft + Scale * E12
  };

  m_CrawlBolts[0].Spark(STrace);

  m_CrawlBolts[1].Spark(STrace);

  m_CrawlBolts[2].Spark(STrace2);

  m_CrawlBolts[3].Spark(STrace2);



  m_CrawlBolts[4].Spark(FTrace);

  m_CrawlBolts[5].Spark(FTrace);

  m_CrawlBolts[6].Spark(FTrace2);

  m_CrawlBolts[7].Spark(FTrace2);


  m_CrawlBolts[8].Spark(ETrace);

  m_CrawlBolts[9].Spark(ETrace);

  m_CrawlBolts[10].Spark(ETrace2);

  m_CrawlBolts[11].Spark(ETrace2);



  m_CrawlBolts[12].Spark(NTrace);

  m_CrawlBolts[13].Spark(NTrace);

  m_CrawlBolts[14].Spark(NTrace2);

  m_CrawlBolts[15].Spark(NTrace2);



  m_CrawlBolts[16].Spark(GTrace);

  m_CrawlBolts[17].Spark(GTrace);

  m_CrawlBolts[18].Spark(GTrace2);

  m_CrawlBolts[19].Spark(GTrace2);



  m_CrawlBolts[20].Spark(ITrace);

  m_CrawlBolts[21].Spark(ITrace);

  m_CrawlBolts[22].Spark(ITrace2);

  m_CrawlBolts[23].Spark(ITrace2);



  m_CrawlBolts[24].Spark(N2Trace);

  m_CrawlBolts[25].Spark(N2Trace);

  m_CrawlBolts[26].Spark(N2Trace2);

  m_CrawlBolts[27].Spark(N2Trace2);



  m_CrawlBolts[28].Spark(E2Trace);

  m_CrawlBolts[29].Spark(E2Trace);

  m_CrawlBolts[30].Spark(E2Trace2);

  m_CrawlBolts[31].Spark(E2Trace2);
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

