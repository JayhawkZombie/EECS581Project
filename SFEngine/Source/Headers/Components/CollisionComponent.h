#ifndef SFENGINE_COLLISION_COMPONENT_H
#define SFENGINE_COLLISION_COMPONENT_H

#include "ComponentBase.h"
#include "../../../ThirdParty/PhysicsEngine.h"

class mvHit;

namespace Engine
{

  class CollisionComponent : protected ComponentBase
  {
  public:
    CollisionComponent();
    ~CollisionComponent();
    void AttachedTo(ComponentManager *newManager) override;
    void AttachedTo(LevelObject *Object) override;
    void Detach() override;
    void Update() override;
    void Enable() override;
    void Disable() override;
    std::string GetComponentName() const override;

    void CreateMesh(std::shared_ptr<::mvHit> Mesh);
    std::shared_ptr<PhysicsEngineBaseMeshType> GetMesh();

  protected:
    std::shared_ptr<PhysicsEngineBaseMeshType> CollisionMesh;
    bool Enabled = true;
  };

}

#endif
