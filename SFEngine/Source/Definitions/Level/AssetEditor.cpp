#include "../../Headers/Level/Level.h"

namespace Engine
{

  void BasicLevel::ShowAssetEditor()
  {
    //whether to show existing assets or make a new asset
    static bool ShowAssetMaker = false;
    static bool ExistingAssetMaker = true;
    static bool NewAssetMaker = false;

    ImGui::Begin("Asset Maker");

    ExistingAssetMaker = !NewAssetMaker && ImGui::Selectable("Existing Assets", &ExistingAssetMaker);
    ImGui::SameLine();
    NewAssetMaker = !ExistingAssetMaker && ImGui::Selectable("New Asset", &NewAssetMaker);

    if (ExistingAssetMaker) {
      ImGui::Indent();
      ShowExistingAssetEditor();
      ImGui::Unindent();
    }
    else if (NewAssetMaker) {
      ImGui::Indent();
      ShowNewAssetMaker();
      ImGui::Unindent();
    }

    ImGui::End();
  }

  void BasicLevel::ShowNewAssetMaker()
  {
    static char nameBuf[500] = { 0 };
    ImGui::InputText("Name:", nameBuf, 500, ImGuiInputTextFlags_CharsNoBlank);



  }

  void BasicLevel::ShowExistingAssetEditor()
  {
  }



}
