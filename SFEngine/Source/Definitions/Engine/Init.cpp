#include "Engine\Engine.h"
#include "Messaging\CoreMessager.h"

namespace Engine
{
  UINT32 SFEngine::Init(int argc, char **argv)
  {
    //Initialize the messager
    Messager::Init();
    ASyncLevelStreamThread::Launch();
    LevelsLock = std::make_shared<std::mutex>();

    Messager::PostLogMessage(0, SystemMessage(SystemMessageType::ActivityLog, 0, 0, "EngineStartup"), MessageLogLevel::Normal);

    std::vector<std::string> Commands;

    for (int i = 0; i < argc; i++) {
      Commands.emplace_back(std::string(argv[i]));
    }

    currentRenderWindow = new sf::RenderWindow(sf::VideoMode(400, 400), "splash screen", sf::Style::None);
    sf::Font loadfont;
    loadfont.loadFromFile("./SFEngine/Source/CoreFiles/Fonts/Marvel-Regular.ttf");
    sf::Text loadingtext;
    loadingtext.setString("Please Wait... \nLoading...");

    auto rect = loadingtext.getGlobalBounds();

    loadingtext.setPosition({ rect.width / 2.f, rect.height / 2.f });
    currentRenderWindow->draw(loadingtext);
    currentRenderWindow->display();

    return Startup();
  }
}
