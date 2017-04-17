#include "Level\BasicLevel.h"
#include "Level\LevelObject.h"

#ifdef WITH_EDITOR

namespace Engine
{

  void BasicLevel::ShowScene(std::shared_ptr<sf::RenderTexture> Texture)
  {

    //if (ImGui::Begin("Scene Viewer", NULL, ImGuiWindowFlags_MenuBar)) {

    //  if (ImGui::BeginMenuBar()) {
    //    if (ImGui::BeginMenu("Spawn")) {
    //      if (ImGui::MenuItem("Show Spawner")) {
    //      }

    //      ImGui::EndMenu();
    //    }

    //    if (ImGui::BeginMenu("Properties")) {

    //      ImGui::Checkbox("Physics", &DoUpdatePhysics);

    //      ImGui::EndMenu();
    //    }

    //    ImGui::EndMenuBar();
    //  }

    //  ImGui::Separator();

    //  if (ImGui::Button("Clear Objects")) {
    //    for (auto & obj : TestObjects)
    //      obj.reset();
    //    TestObjects.clear();
    //  }

    //  ImGui::Image(Texture->getTexture(), ImVec2(800, 800), sf::FloatRect({ 0, Size.y - 700.f, 800.f, 800.f }));

    //  ImGui::End(); //end Scene Viewer
    
  }

}
#endif //WITH_EDITOR
