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

    return Startup();
  }
}
