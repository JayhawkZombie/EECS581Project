#include "../../Headers/Level/Level.h"

namespace Engine
{

  void Level::ShowSceneGraph()
  {

    if (!ImGui::Begin("SceneGraph")) {
      ImGui::End();
      return;
    }
    
    static std::string rootName = "Root" + GetID();
    if (ImGui::CollapsingHeader(rootName.c_str())) {
      ImGui::Indent();

      if (ImGui::CollapsingHeader("Physics Objects")) {
        ImGui::Indent();
        if (ImGui::Button("Clear")) {
          TestObjects.clear();
        }
        int i = 1000;
        std::string displaytext = "";

        for (auto & item : TestObjects) {
          displaytext = "pos: (" + std::to_string(item->pos.x) + ", " + std::to_string(item->pos.y) + ")";
          ImGui::Text(displaytext.c_str());
        }

        ImGui::Unindent();
      }

      if (ImGui::CollapsingHeader("Audio")) {
        //audio area

        ImGui::Indent();
        if (ImGui::CollapsingHeader("Scenic Audio")) {

          
        }

        if (ImGui::CollapsingHeader("Others")) {

          
        }

        ImGui::Unindent();
      }

      if (ImGui::CollapsingHeader("Starters")) {
        //starters/spawners area

        
      }

      if (ImGui::CollapsingHeader("Lights")) {
        //lights area

        
      }

      if (ImGui::CollapsingHeader("Static Objects")) {
        //static objects area

        
      }

      if (ImGui::CollapsingHeader("Volumes")) {
        ImGui::Indent();
        //volumes here
        if (ImGui::CollapsingHeader("Kill Volumes")) {

          
        }
        if (ImGui::CollapsingHeader("Spawn Volumes")) {

          
        }
        if (ImGui::CollapsingHeader("Transition Volumes")) {

          
        }
        if (ImGui::CollapsingHeader("Interaction Volumes")) {

          
        }
      
        ImGui::Unindent();
      } //volumes tree node

      if (ImGui::CollapsingHeader("Emitters")) {

        
      }

      if (ImGui::CollapsingHeader("Actors")) {

        
      }

      ImGui::Unindent();
    }

    ImGui::End();
  }

}
