#include "Objects/TriggerVolume.h"

namespace Engine
{
  TriggerVolume::TriggerVolume(TriggerMethod Method)
  {
  }
  TriggerVolume::TriggerVolume(std::function<void(void)> TriggerCB, std::function<bool(std::shared_ptr<LevelObject>)> TriggerCheckCB, bool DoTriggerCheck)
  {
  }
  TriggerVolume::~TriggerVolume()
  {
  }
  TriggerVolume::TriggerVolume(const TriggerVolume &)
  {
  }
  std::shared_ptr<TriggerVolume> TriggerVolume::Clone() const
  {
    return std::shared_ptr<TriggerVolume>();
  }
  void TriggerVolume::TickUpdate(const double & TickDelta)
  {
  }
  void TriggerVolume::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
  }
  void TriggerVolume::DoTriggerChecks(std::map<std::string, std::shared_ptr<LevelObject>>& Objects)
  {
  }
  void TriggerVolume::Cleanup()
  {
  }
  void TriggerVolume::Sleep(bool MakeDefault)
  {
  }
  void TriggerVolume::Wake()
  {
  }
  void TriggerVolume::SleepFor(double Ms)
  {
  }
  void TriggerVolume::Enable(bool MakeDefault)
  {
  }
  void TriggerVolume::Disable(bool MakeDefault)
  {
  }
  void TriggerVolume::Reset()
  {
  }
  void TriggerVolume::SetCollider(std::shared_ptr<Collider2D> Collider)
  {
  }
  void TriggerVolume::SetTriggerMethod(TriggerMethod Method, bool MakeDefault)
  {
  }
}
