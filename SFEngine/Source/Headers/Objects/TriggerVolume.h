#ifndef SFENGINE_TRIGGER_VOLUME_H
#define SFENGINE_TRIGGER_VOLUME_H

#include "BasicIncludes.h"

namespace Engine
{
  class Collider2D;
  class LevelObject;

  enum class TriggerMethod
  {
    Touch_PhysicalResponse = 0,
    Touch_NoPhysicalResponse,
    MinimumOverlap_NoPhysicalResponse
  };


  class TriggerVolume
  {
  public:
    TriggerVolume(TriggerMethod Method);
    TriggerVolume(std::function<void(void)> TriggerCB,
                  std::function<bool(std::shared_ptr<LevelObject>)> TriggerCheckCB,
                  bool DoTriggerCheck = false);
    ~TriggerVolume();

    //Do we even want to be able to clone trigger objects?
    TriggerVolume(const TriggerVolume &);
    TriggerVolume(const TriggerVolume &&) = delete;
    TriggerVolume() = delete;

    virtual std::shared_ptr<TriggerVolume> Clone() const;

    void TickUpdate(const double & TickDelta);
    void Render(std::shared_ptr<sf::RenderTarget> Target);
    void DoTriggerChecks(std::map<std::string, std::shared_ptr<LevelObject>> &Objects);
    void Cleanup();

    void Sleep(bool MakeDefault = false);
    void Wake();
    void SleepFor(double Ms);

    void Enable(bool MakeDefault = true);
    void Disable(bool MakeDefault = true);
    void Reset();
    void SetCollider(std::shared_ptr<Collider2D> Collider);

    void SetTriggerMethod(TriggerMethod Method, bool MakeDefault = true);

  private:
    std::shared_ptr<Collider2D> m_Collider;
    TriggerMethod               m_TriggerMethod;
    bool                        m_Enabled = true;
    bool                        m_DoPhysicalResponse = false;
    bool                        m_Sleeping = false;
    bool                        m_DoTriggerCheck = false;
    double                      m_SleepingDuration = 0.0;
    double                      m_CurrentSleepingDuration = 0.0;

    //Stuff for default state
    TriggerMethod            m_DefaultTriggerMethod;
    bool                     m_DefaultEnabled;
    bool                     m_DefaultDoPhysicalResponse;
    bool                     m_DefaultSleeping;
    std::function<bool(std::shared_ptr<LevelObject>)>  m_DefaultTriggerCheckCallback;
    std::function<void(void)> m_DefaultTriggerCallback;
  };

}

#endif
