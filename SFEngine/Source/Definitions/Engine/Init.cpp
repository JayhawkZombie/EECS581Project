#include "../../Headers/Engine/Engine.h"

namespace Engine
{
  UINT32 SFEngine::Init(int argc, char **argv)
  {
    std::cerr << "[Command Line Arguments]\n";
    for (int i = 0; i < argc; i++) {
      std::cout << "\t" << i << ": " << argv[i] << std::endl;
    }

    std::cerr << "Starting resource manager" << std::endl;
    ResourceManager = std::shared_ptr<Resource::ResourceManager>(new Resource::ResourceManager);
    ResourceManager->Start();

    LoadingAnimation[0].RequestSpriteSheet("./SFEngine/Samples/Animations/torchsheet.png", "EngineLoadingWhite");

    std::stringstream SS;
    std::ifstream _in("./SFEngine/Samples/Animations/torchsheet.txt");
    std::string dump1, dump2, left, top, width, height;
    std::vector<sf::IntRect> Frames;
    if (_in) {
      while (_in >> dump1 && _in >> dump2) {
        _in >> left >> top >> width >> height;

        LoadingAnimation[0].AddFrame({
          std::stoi(left), std::stoi(top), std::stoi(width), std::stoi(height)
        });

      }
    }
    LoadingAnimation[0].SetFrameTime(50); 
    LoadingAnimation[0].SetPosition({ 600,600 });



    return Startup();
  }
}
