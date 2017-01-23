#include "../../Headers/Engine/Engine.h"

namespace Engine
{
  UINT32 SFEngine::Init(int argc, char **argv)
  {
    std::cerr << "[Command Line Arguments]\n";
    for (int i = 0; i < argc; i++) {
      std::cout << "\t" << i << ": " << argv[i] << std::endl;
    }
    
    ResourceManager = std::shared_ptr<Resource::ResourceManager>(new Resource::ResourceManager); 
    ResourceManager->Start();
    DefaultTexture = std::shared_ptr<sf::Texture>(new sf::Texture);
    DefaultTexture->loadFromFile("./SFEngine/Samples/Textures/DefaultTexture.png");

    int __width;

    for (int i = 0; i < 6; ++i) {

      LoadingAnimation[i].RequestSpriteSheet("./SFEngine/Samples/Animations/hyponosheet.png", "EngineLoadingWhite" + std::to_string(i));

      std::stringstream SS;
      std::ifstream _in("./SFEngine/Samples/Animations/hypnosheet.txt");
      std::string dump1, dump2, left, top, width, height;
      std::vector<sf::IntRect> Frames;
      if (_in) {
        while (_in >> dump1 && _in >> dump2) {
          
          _in >> left >> top >> width >> height;
          __width = std::stoi(width);
          LoadingAnimation[i].AddFrame({
            std::stoi(left), std::stoi(top), std::stoi(width), std::stoi(height)
          });

        }
      }
      LoadingAnimation[i].SetFrameTime(30);
      LoadingAnimation[i].SetPosition({ (float)__width * i, 400 });

    }



    return Startup();
  }
}
