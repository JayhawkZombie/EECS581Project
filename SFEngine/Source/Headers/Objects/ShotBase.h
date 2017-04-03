#include "ProjectileBase.h"

namespace Engine
{

  class ShotBase : public ProjectileBase
  {
  public:
    ShotBase();
    virtual ~ShotBase();

    virtual void TickUpdate(const double &delta) override;
    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(std::ofstream &out) override;
    virtual void SerializeIn(std::ifstream &in) override;
    virtual void SetPosition(const sf::Vector2f &pos);

    virtual void UpdateMesh();
    virtual void UpdateSegments();

  protected:

  };

}