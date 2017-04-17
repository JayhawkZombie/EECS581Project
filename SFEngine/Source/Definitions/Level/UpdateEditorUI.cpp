#include "Level\BasicLevel.h"

#ifdef WITH_EDITOR
#include "Engine\Console.h"

namespace Engine
{

  void BasicLevel::UpdateEditorUI(const double &delta)
  {
    if (CurrentLevel) {
      CurrentLevel->ShowSceneGraph();
      CurrentLevel->ShowAssetGraph();
      CurrentLevel->ShowGraphicalSettings();
      CurrentLevel->ShowSpawner();
      CurrentLevel->ShowAssetEditor();

      if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
          if (ImGui::MenuItem("Exit")) {
            FlagForClose = true;
          }
          ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
          if (ImGui::MenuItem("Something")) {

          }
          ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
      }
      Console::ShowDebugConsole(NULL);

    }
  }
}

#endif
