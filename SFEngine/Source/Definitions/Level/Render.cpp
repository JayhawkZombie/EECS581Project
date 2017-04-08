#include "../../Headers/Level/Level.h"
#include "../../Headers/Engine/Console.h"
#include "../../Headers/Physics/Collider.h"

namespace Engine
{
  void Level::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
  {
    SceneBlendTexture->clear(sf::Color::Transparent);

    Texture->draw(TileMap);

    if (ShowGridLines) {
      for (auto & arr : GridLines)
        Texture->draw(arr);
    }

    for (auto & obj : LevelObjects)
      Texture->draw(obj.second->Sprite);

    //If we are using the editor, draw the meshes too
    //Make this configurable later
#ifdef WITH_EDITOR
    BasicLevel::RenderEditorUI(Texture);
#endif
  }

  void Level::Render(std::shared_ptr<sf::RenderTarget> Target)
  {

  }

  void Level::RenderRegular()
  {

  }

  void Level::RenderLoadingScreen()
  {

  }

}