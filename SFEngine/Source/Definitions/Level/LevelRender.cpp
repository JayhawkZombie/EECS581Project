#include "../../Headers/Level/Level.h"
#include "../../Headers/Engine/Console.h"

namespace Engine
{
  void Level::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
    SceneBlendTexture->clear(sf::Color::Transparent);

    if (ShowGridLines) {
      for (auto & arr : GridLines)
        Target->draw(arr);
    }

    for (auto & obj : TestObjects)
      obj->draw(*Target);

    for (auto & seg : TestSegments)
      seg->draw(*Target);

	for (auto & object : Objects) {
		Target->draw(object->Sprite);
	}

  Target->draw(TileMap);

#ifdef WITH_EDITOR
    ShowSceneGraph();
    ShowAssetGraph();
    ShowGraphicalSettings();
    ShowSpawner();

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
#endif
  }

  void Level::RenderRegular()
  {

  }

  void Level::RenderLoadingScreen()
  {

  }

}