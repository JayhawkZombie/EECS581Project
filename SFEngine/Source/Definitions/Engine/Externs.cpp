#include "../../Headers/Globals/GlobalHooks.h"
#include "../../Headers/Engine/Engine.h"

#include <vector>

namespace Engine
{
  sf::RenderWindow *currentRenderWindow = nullptr;
  std::shared_ptr<Resource::ResourceManager> ResourceManager;
  sf::Vector2f WindowSize;
  std::shared_ptr<sf::Texture> DefaultTexture;

  std::unordered_set<std::uint32_t> UsedIDs;

  void SetKeyRepeatEnabled(bool enabled)
  {
    if (currentRenderWindow)
      currentRenderWindow->setKeyRepeatEnabled(enabled);
  }

  void FreeID(const std::uint32_t &ID)
  {
    auto it = UsedIDs.find(ID);
    if (it != UsedIDs.end())
      UsedIDs.erase(it);
  }

  bool IsIDUsed(const std::uint32_t &ID)
  {
    return (UsedIDs.find(ID) != UsedIDs.end());
  }

  std::uint32_t GenerateID()
  {
    std::uint32_t ItemID = 0;

    std::uint32_t Tries = 0;
    std::default_random_engine generator;
    generator.seed(NULL);
    std::uniform_int_distribution<std::uint32_t> dist(1, std::numeric_limits<std::uint32_t>::max() - 1);

    //Try one time to generate an ID
    ItemID = dist(generator);

    //If we couldn't do so, we will try a set number of times to generate one
    while (IsIDUsed(ItemID))
    {
      if (Tries >= MaxIDGenerationAttempts) {
        throw IDException({ ExceptionCause::IDGenerationError }, EXCEPTION_MESSAGE("Could not generate an ID for item"));
      }
      Tries++;
      ItemID = dist(generator);
    }

    //We were able to succesfully create an ID
    UsedIDs.insert(ItemID);

    return ItemID;
  }

  //ENGINE API METHODS
  sf::Vector2u GetCurrentWindowSize()
  {
    if (CurrentEngine)
      return CurrentEngine->GetCurrentWindowsize();
    else
      return{ 0, 0 };
  }

  decltype(auto) GetCurrentOpenGLVersionMajor()
  {
    sf::ContextSettings settings;

    if (currentRenderWindow) {
      settings = currentRenderWindow->getSettings();

      return settings.majorVersion;
    }

    return decltype(settings.majorVersion)(0);
  }

  decltype(auto) GetCurrentOpenGLVersionMinor()
  {
    sf::ContextSettings settings;

    if (currentRenderWindow) {
      settings = currentRenderWindow->getSettings();

      return settings.minorVersion;
    }

    return decltype(settings.minorVersion)(0);
  }

  decltype(auto) GetCurrentAASetting()
  {
    sf::ContextSettings settings;

    if (currentRenderWindow) {
      settings = currentRenderWindow->getSettings();

      return settings.antialiasingLevel;
    }

    return decltype(settings.antialiasingLevel)(0);
  }

  decltype(auto) GetCurrentContextSettings()
  {
    sf::ContextSettings settings;
    
    if (currentRenderWindow) {
      settings = currentRenderWindow->getSettings();

      return settings;
    }

    settings.antialiasingLevel = 0;
    settings.attributeFlags = sf::ContextSettings::Attribute::Default;
    settings.depthBits = 0;
    settings.majorVersion = 0;
    settings.minorVersion = 0;

    return settings;
  }

  decltype(auto) GetCurrentContext()
  {
    return sf::Context::getActiveContext();
  }

  decltype(auto) GetCurrentTexturePoolSize()
  {
    return 0;
  }

  decltype(auto) GetCurrentShaderPoolSize()
  {
    return 0;
  }

  decltype(auto) GetCurrentFramerateSetting()
  {
    if (CurrentEngine)
      return CurrentEngine->GetCurrentFrameRate();
    else
      return 0U;
  }

  decltype(auto) GetIsGlobalShadingEnabled()
  {
    return true;
  }

  decltype(auto) GetIsStaticShadingEnabled()
  {
    return true;
  }

  decltype(auto) GetIsDynamicShadingEnabled()
  {
    return true;
  }

  decltype(auto) GetIsStaticShadowingEnabled()
  {
    return true;
  }

  decltype(auto) GetIsDynamicShadowingEnabled()
  {
    return true;
  }

  decltype(auto) GetIsMultiThreadedLightingEnabled()
  {
    return false;
  }

  decltype(auto) GetIsUsingPreComputedLightMaps()
  {
    return true;
  }

  decltype(auto) GetCanPhysicsApproxCollision()
  {
    return true;
  }

  //if the editor is being used, link to the current engine and allow access to the global UI handler
#ifdef WITH_EDITOR
  SFEngine *CurrentEngine = nullptr;

  void AddUI(std::shared_ptr<Engine::UI::BaseUIElement> element)
  {
    if (CurrentEngine)
      CurrentEngine->AddUIElement(element);
  }

#endif
}
