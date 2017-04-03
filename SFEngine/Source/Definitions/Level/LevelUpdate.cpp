#include "../../Headers/Level/Level.h"
#include "../../Headers/Engine/Console.h"
#include "../../Headers/Physics/Collider.h"

namespace Engine
{
  void Level::TickUpdate(const double &delta)
  {
    static double cumulative = 0.f;
    cumulative += delta;

#ifdef WITH_EDITOR
    //Update editor related objects
    for (auto & anim : EditorGraphAnimations)
      anim.second->TickUpdate(delta);
#endif
    TileMap.update(lvlData, 20);
    //Only want to update the physics 60 times per second, since it does not time itself ((((UGH))))
    
    for (auto & obj : Objects)
      obj->TickUpdate(delta);

    if (cumulative > updateInterval) {

      if (DoUpdatePhysics && ( LevelObjects.size() > 0 || Segments.size() > 0) ) {
        UpdateObjectPhysics();

        for (auto & obj : LevelObjects) {
          obj.second->PhysicsUpdate();
        }
      }

      cumulative = 0.f;
    }



#ifdef WITH_EDITOR
    ShowSceneGraph();
    ShowAssetGraph();
    ShowGraphicalSettings();
    ShowSpawner();
    ShowAssetEditor();

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

  void Level::UpdateObjectPhysics()
  {
    static std::vector<PhysicsEngineBaseMeshType *> MeshVector;
    static std::vector<PhysicsEngineSegmentType *> SegVector;

    static std::vector<std::shared_ptr<Engine::Collider2D>> Colliders;
   

    MeshVector.clear();
    SegVector.clear();
    Colliders.clear();

    for (auto & obj : LevelObjects) {
      auto vec = obj.second->GetColliders();
      for (auto & mesh : vec) {
        Colliders.push_back(mesh);
      }
    }
    
    for (auto & seg : Segments)
      SegVector.push_back(seg.get());

    UpdatePhysics(Colliders, SegVector);
  }

}