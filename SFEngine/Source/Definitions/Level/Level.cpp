#include "../../Headers/Level/Level.h"

namespace Engine
{

  Level::Level()
  {
    ReadCorrectly = true;
    BGHeight = 0;
    BGWidth = 0;
    ReadyToDraw = false;

    LevelWaitingText.setString(std::string("Waiting for level to load..."));
    LevelWaitingText.setPosition(sf::Vector2f(200, 200));
    LevelWaitingText.setCharacterSize(12);
    ResourceManager->RequestFont("./SFEngine/Samples/Fonts/OpenSans-Regular.ttf", "./SFEngine/Samples/Fonts/OpenSans-Regular.ttf",
                                 [this](std::shared_ptr<sf::Font> f, const std::string &s) {this->ReceiveFont(f, s); });

    COND_VAR = std::shared_ptr<std::condition_variable>(new std::condition_variable);
    MUTEX = std::shared_ptr<std::mutex>(new std::mutex);
    CHECK_READY_MUTEX = std::shared_ptr<std::mutex>(new std::mutex);

    Handler.BindCallback(
      Events::KeyPressed,
      [this](const sf::Keyboard::Key &k)
      {
        this->HandleKeyEvent(k);
      }
    );

  }

  Level::Level(const Level &lvl)
    : Level()
  {

  }

  Level::~Level()
  {
    if (LOADER.joinable())
      LOADER.join();

    if (DRAWER.joinable())
      DRAWER.join();
  }

  void Level::ReceiveFont(std::shared_ptr<sf::Font> font, const std::string &ID)
  {
    LevelWaitingFont = font;
    if (font.get()) {
      LevelWaitingText.setFont(*LevelWaitingFont.get());
    }
  }

  void Level::RequestTextures()
  {
    //Go through all the known textures we have
    //and make a request to the resource manager for each of them

    for (auto & tex : KnownTextures) {
      ResourceManager->RequestTexture(tex, tex,
                                      [this](std::shared_ptr<sf::Texture> t, const std::string &s) {this->ReceiveTexture(t, s); }
      );
    } //for (tex : KnownTextures)
  }

  void Level::ReceiveTexture(std::shared_ptr<sf::Texture> texture, const std::string &ID)
  {
    static std::size_t texturesReceived = 0;

    texturesReceived++;
    if (texturesReceived > KnownTextures.size()) {
      std::cerr << "Engine::Level::ReceiveTexture : Unexpected texture sent, ID = \"" << ID << "\"" << std::endl;
      return;
    }

    std::cerr << "RECEIVED TEXTURE: \"" << ID << "\"" << std::endl;

    IDToTexture.emplace(
      std::piecewise_construct,
      std::make_tuple(ID),
      std::make_tuple(texture)
    );

    if (IDToTexture.size() == KnownTextures.size()) {
      ReadyToDraw = true;
      COND_VAR->notify_all();
    }

  }

  void Level::DrawToRenderTexture()
  {

    while (!ReadyToDraw) {
      std::unique_lock<std::mutex> lock(*MUTEX);
      COND_VAR->wait(lock);
    }
    std::cerr << "All textures received. Drawing to render texture" << std::endl;

    sf::Sprite spr;
    std::size_t texWidth{ 0 }, texHeight{ 0 };
    sf::Vector2u textureSize =
      IDToTexture[KnownTextures[0]]->getSize();

    Layers.push_back(std::shared_ptr<LevelLayer>(new LevelLayer));

    Layers[0]->BackgroundTexture.create(
      BGWidth * textureSize.x, BGHeight * textureSize.y
      );
    Layers[0]->BackgroundTexture.clear();


    sf::Texture *looptexture = nullptr;
    std::string RealTextureID{ "" };

    for (std::size_t OUTER = 0; OUTER < BGLayout.size(); ++OUTER) {
      
      for (std::size_t INNER = 0; INNER < BGLayout[OUTER].size(); ++INNER) {
        spr.setPosition(sf::Vector2f(INNER * textureSize.x, OUTER * textureSize.y));
        
        RealTextureID = MapToTextureID[BGLayout[OUTER][INNER]];

        auto loc = IDToTexture.find(RealTextureID);
        if (loc != IDToTexture.end()) {
          spr.setTexture(*loc->second);
          Layers[0]->BackgroundTexture.draw(spr);
        }
       
      }
    }
    
    Layers[0]->BackgroundTexture.display();
    Layers[0]->BGSprite->setTexture(
      Layers[0]->BackgroundTexture.getTexture()
    );

    Layers[0]->BGSprite->setTextureRect(
      sf::IntRect(0, 0, BGWidth * textureSize.x, BGHeight * textureSize.y)
    );

    sf::Vector2f scale;
    scale.x = (WindowSize.x) / (BGWidth * textureSize.x);
    scale.y = (WindowSize.y) / (BGHeight * textureSize.y);
    Layers[0]->BGSprite->setScale(scale);

    //For now, this is all we need to do to make the level ready to play
    

    CHECK_READY_MUTEX->lock();
    ReadyToPlay = true;
    CHECK_READY_MUTEX->unlock();
  }

  void Level::LoadLevel(const std::string &file)
  {
    //This needs to be done in a different thread

    LOADER = std::thread([this, file]() {
      std::ifstream IN(file);

      if (IN.fail()) {
        std::cerr << "Unable to load level: " << file << std::endl;
        IN.clear();
        return;
      }

      std::string str{ "" };
      while (IN >> str) {

        if (str == "ID:")
          this->ReadIDAndPath(IN.tellg(), IN);

        else if (str == "Layout:")
          this->ReadLayout(IN.tellg(), IN);

        else {
          std::cerr << "Unrecognized formatting in file. \"" << str << "\"" << std::endl;
          return;
        }
      }
      this->RequestTextures();
      IN.clear();
      IN.close();
    });
    LOADER.detach();

    DRAWER = std::thread([this]() {
      this->DrawToRenderTexture();
    });

    DRAWER.detach();

  }

  void Level::ReadLayout(std::streampos &pos, std::ifstream &IN)
  {
    std::string ID{ "" };
    std::string substring{ "" };
    std::size_t line{ 0 }, height{ 0 };

    std::stringstream ss;
    IN.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (std::getline(IN, ID)) {
      ss << ID;
      line = 0;
      std::vector<std::string> temp;
      BGWidth = 0;
      while (ss >> substring) {
        temp.push_back(substring);
        BGWidth++;
      }
      BGLayout.push_back(temp);
      BGHeight++;
      ss.clear();
    }

    std::cout << BGHeight << " by " << BGWidth << " background" << std::endl;
  }

  void Level::ReadIDAndPath(std::streampos &pos, std::ifstream &IN)
  {
    std::string ID{ "" };
    IN >> ID;

    std::string file;
    IN >> file;
    if (file != "Path:") {
      std::cerr << "Error reading file path for ID: \"" << ID << "\"" << std::endl;
      return;
    }
    IN >> file;

    MapToTextureID.emplace(
      std::piecewise_construct,
      std::make_tuple(ID),
      std::make_tuple(file)
    );

    //Push back the ID that'll be used by the resource manager, and
    //keep track of how many textures we know we are going to need
    KnownTextures.push_back(file);
  }

  bool Level::IsReady() const
  {
    bool b = false;
    CHECK_READY_MUTEX->lock();
    b = ReadyToPlay;
    CHECK_READY_MUTEX->unlock();
    return b;
  }

}
