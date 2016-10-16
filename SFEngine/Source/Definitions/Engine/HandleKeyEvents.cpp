#include "../../Headers/Engine/Engine.h"

namespace Engine
{

  void SFEngine::HandleKeyPress(const sf::Keyboard::Key &k)
  {
    if (k == sf::Keyboard::Escape)
      EngineUIController.ToggleShown();
    else
      EngineUIController.Handler.HandleKeyPress(k);

    if (k == sf::Keyboard::Up) {
      RenderSettings.Brightness += 0.1;
    }
    else if (k == sf::Keyboard::Down) {
      RenderSettings.Brightness -= 0.1;
    }
    else if (k == sf::Keyboard::Left) {
      RenderSettings.Contrast += 0.1;
    }
    else if (k == sf::Keyboard::Right) {
      RenderSettings.Contrast -= 0.1;
    }

    if (k == sf::Keyboard::Z) {
      RenderSettings.Gamma += 0.1;
    }
    else if (k == sf::Keyboard::X) {
      RenderSettings.Gamma -= 0.1;
    }

    if (k == sf::Keyboard::P) {
      RenderSettings.PostProcess += 1;
    }
    else if (k == sf::Keyboard::L) {
      RenderSettings.PostProcess -= 1;
    }
    //std::cerr << "PostProcessEffect = " << RenderSettings.PostProcess << std::endl;
    Render::__Set__Render__Settings(RenderSettings);

    for (auto & level : Levels) {
      level->Handler.HandleKeyPress(k);
    }
  }

  void SFEngine::HandleKeyRelease(const sf::Keyboard::Key &k)
  {
    EngineUIController.Handler.HandleKeyRelease(k);
  }

}
