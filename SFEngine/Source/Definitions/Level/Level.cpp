#include "../../Headers/Level/Level.h"

namespace
{

}

namespace Engine
{

  Level::Level(const std::string &levelFile)
  {
    LevelFile = levelFile;
    Playable = false;


    Handler.BindCallback(
      Events::KeyPressed,
      [this](const sf::Keyboard::Key &k)
    {
      this->HandleKeyEvent(k);
    }
    );

    ResourceManager->RequestFont("./SFEngine/Samples/Fonts/OpenSans-Regular.ttf", "./SFEngine/Samples/Fonts/OpenSans-Regular.ttf",
                                 [this](std::shared_ptr<sf::Font> f, const std::string &s) {this->ReceiveFont(f, s); });

    GlobalLightSource *GlobalLight = new GlobalLightSource;
    GlobalLight->SetColor(sf::Color::Transparent);
    GlobalLight->SetIntensity(25);

    Environment.AddGlobalLight("LevelGlobalLight", new GlobalLightSource);

    /**
     * Just for testing
     */
    //Player *player = new Player;
    //player->Collsion.Position = sf::Vector2f(250, 250);
   // player->Collsion.Size = sf::Vector2f(50, 75);
   // player->MoveTo(sf::Vector2f(250, 250));
    //Environment.AddActor("MainPlayerActor", player);
    //Environment.SetPlayer("MainPlayerActor");

    //PlayerActor.Collsion.Position = sf::Vector2f(250, 250);
    //PlayerActor.Collsion.Size = sf::Vector2f(50, 75);
    //PlayerActor.MoveTo(sf::Vector2f(250, 250));

    CollisionBoxes.push_back({});
    CollisionBoxes.push_back({});

    CollisionBoxes[0].Position = sf::Vector2f(100, 100);
    CollisionBoxes[0].Size = sf::Vector2f(50, 50);

    CollisionBoxes[1].Position = sf::Vector2f(300, 300);
    CollisionBoxes[1].Size = sf::Vector2f(150, 100);
  }

  Level::~Level()
  {
    if (LOADER.joinable())
      LOADER.join();
  }

  void Level::ReceiveFont(std::shared_ptr<sf::Font> font, const std::string &ID)
  {
    LevelWaitingFont = font;
    if (font.get()) {
      LevelWaitingText.setFont(*LevelWaitingFont.get());
    }
  }

  void Level::AddActor(const std::string &ID, GenericActor *src)
  {
    Environment.AddActor(ID, src);
  }

  void Level::AddLight(const std::string &ID, GenericLightSource *src)
  {
    Environment.AddLight(ID, src);
  }

  void Level::AddGlobalLight(const std::string &ID, GlobalLightSource *src)
  {
    Environment.AddGlobalLight(ID, src);
  }

  void Level::IsReady() const
  {

  }

}
