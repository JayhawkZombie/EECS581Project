#include "../../Headers/Engine/Engine.h"

namespace Engine
{
  UINT32 SFEngine::Init(int argc, char **argv)
  {
    std::cerr << "[Command Line Arguments]\n";
    for (int i = 0; i < argc; i++) {
      std::cout << "\t" << i << ": " << argv[i] << std::endl;
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
    
    ResourceManager = std::shared_ptr<Resource::ResourceManager>(new Resource::ResourceManager); 
    ResourceManager->Start();
    DefaultTexture = std::shared_ptr<sf::Texture>(new sf::Texture);
    DefaultTexture->loadFromFile("./SFEngine/Samples/Textures/DefaultTexture.png");

    return Startup();
  }
}
