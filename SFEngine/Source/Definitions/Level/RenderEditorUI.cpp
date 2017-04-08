#include "../../Headers/Level/Level.h"
#include "../../Headers/Physics/Collider.h"

#ifdef WITH_EDITOR

namespace Engine
{

  void BasicLevel::RenderEditorUI(std::shared_ptr<sf::RenderTexture> Texture)
  {

    if (CurrentLevel) {
      for (auto & obj : CurrentLevel->LevelObjects)
        for (auto & collider : obj.second->GetColliders())
        {
          if (collider->GetMesh().lock())
            collider->GetMesh().lock()->draw(*Texture);
        }

      for (auto & seg : CurrentLevel->Segments)
        seg->draw(*Texture);
    }

  }

}

#endif
