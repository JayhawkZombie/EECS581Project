#include "../../Headers/Level/Level.h"

namespace Engine
{

  void ShowWaveOptions(waveSeg *wave)
  {
    ImGui::Text("Settings");
    ImGui::Separator();
    ImGui::DragFloat("Gravity", &wave->grav_N, 0.01f, 0.f, 10.f);
    ImGui::DragFloat("Amp left", &wave->Amp_wvLt, 5.f, 0.f, 50.f);
    ImGui::DragFloat("Amp right", &wave->Amp_wvRt, 5.f, 0.f, 50.f);

    ImGui::DragFloat("K left", &wave->K_wvLt, 0.01f, 0.f, 1.f);
    ImGui::DragFloat("K right", &wave->K_wvRt, 0.01f, 0.f, 1.f);

    ImGui::DragFloat("Freq left", &wave->rotFreqLt, 0.0005, 0.f, 0.05f);
    ImGui::DragFloat("Freq right", &wave->rotFreqRt, 0.0005, 0.f, 0.05f);

    ImGui::InputFloat("Elevation", &wave->Elev, 5.f, 15.f);
    ImGui::InputFloat("Depth", &wave->Depth, 5.f, 15.f);
    ImGui::InputFloat("Air Density", &wave->airDensity, 0.00005, 0.0001);
    ImGui::InputFloat("Fluid Density", &wave->fluidDensity, 0.005, 0.001);

    ImGui::Checkbox("IsHard", &wave->is_hard);
  }

  void Level::ShowSceneGraph()
  {

    if (!ImGui::Begin("SceneGraph")) {
      ImGui::End();
      return;
    }
    
    ImGui::Checkbox("Show Grid", &ShowGridLines);

    static std::string rootName = "Root" + GetID();
    if (ImGui::CollapsingHeader(rootName.c_str())) {
      ImGui::Indent();

      if (ImGui::CollapsingHeader("Segments")) {
        ImGui::Indent();

        if (ImGui::CollapsingHeader("Waves")) {
          ImGui::Indent();


          std::string _text{ "" };

          for (auto & wave : Waves) {

            _text = "Pos: (" + std::to_string(wave->pos.x) + ", " + std::to_string(wave->pos.y) + ")";

            if (ImGui::CollapsingHeader(_text.c_str())) {
              ImGui::Indent();
              ShowWaveOptions(wave.get());
              ImGui::Unindent();
            }

          }


          ImGui::Unindent();
        }

        std::string text = "";

        for (auto & item : Segments) {
          text = "pos: (" + std::to_string(item->pos.x) + ", " + std::to_string(item->pos.y) + ")";
          ImGui::Text(text.c_str());
        }

        ImGui::Unindent();
      }

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
