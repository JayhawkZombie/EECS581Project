#include "../../Headers/Level/Level.h"

namespace Engine
{

  void BasicLevel::ShowGraphicalSettings()
  {
    static bool IsVertSyncEnabled;

    if (!ImGui::Begin("Render Settings")) {
      ImGui::End();
      return;
    }

    ImGui::DragFloat("Brightness", &EngineRenderSettings.Brightness, 1.0f, 0.3f, 1.0f);
    ImGui::DragFloat("Contrast", &EngineRenderSettings.Contrast, 1.0f, 0.3f, 1.0f);
    if (ImGui::Checkbox("VSync", &IsVertSyncEnabled)) {
      currentRenderWindow->setVerticalSyncEnabled(IsVertSyncEnabled);
    }
    ImGui::Text("Clear Color");
    
    static float R = 0, G = 0, B = 0, A = 0;
    if (ImGui::DragFloat("Red", &R, 0.01f, 0.f, 1.f)) {
      EngineRenderSettings.BGClearColor.r = static_cast<sf::Uint8>(std::floor(R * 255));
    }
    if (ImGui::DragFloat("Green", &G, 0.01f, 0.f, 1.f)) {
      EngineRenderSettings.BGClearColor.g = static_cast<sf::Uint8>(std::floor(G * 255));
    }
    if (ImGui::DragFloat("Blue", &B, 0.01f, 0.0f, 1.0f)) {
      EngineRenderSettings.BGClearColor.b = static_cast<sf::Uint8>(std::floor(B * 255));
    }

    ImGui::End();
  }

}
