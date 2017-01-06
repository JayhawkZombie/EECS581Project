#include "../../Headers/Globals/GlobalHooks.h"

namespace Engine
{
  sf::RenderWindow *currentRenderWindow = nullptr;
  std::shared_ptr<Resource::ResourceManager> ResourceManager;
  sf::Vector2f WindowSize;
  std::shared_ptr<sf::Texture> DefaultTexture;

  void SetKeyRepeatEnabled(bool enabled)
  {
    if (currentRenderWindow)
      currentRenderWindow->setKeyRepeatEnabled(enabled);
  }
}
