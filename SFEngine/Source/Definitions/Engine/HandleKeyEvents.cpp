#include "../../Headers/Engine/Engine.h"

namespace Engine
{

  void SFEngine::HandleKeyPress(const sf::Keyboard::Key &k)
  {
    if (k == sf::Keyboard::Escape)
      EngineUIController.ToggleShown();
    else
      EngineUIController.Handler.HandleKeyPress(k);

    for (auto & level : Levels) {
      level->Handler.HandleKeyPress(k);
    }
  }

  void SFEngine::HandleKeyRelease(const sf::Keyboard::Key &k)
  {
    EngineUIController.Handler.HandleKeyRelease(k);

    switch (k)
    {
      case sf::Keyboard::Num0:
        RenderSettings.PostProcess = 0;
        break;
      case sf::Keyboard::Num1:
        RenderSettings.PostProcess = 1;
        break;
      case sf::Keyboard::Num2:
        RenderSettings.PostProcess = 2;
        break;
      case sf::Keyboard::Num3:
        RenderSettings.PostProcess = 3;
        break;
    }

    Render::__Set__Render__Settings(RenderSettings);

    for (auto & level : Levels) {
      level->HandleKeyRelease(k);
    }
  }

}
