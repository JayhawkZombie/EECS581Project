#ifndef SFENGINE_EVENT_SEQUENCE_H
#define SFENGINE_EVENT_SEQUENCE_H

#include "../Engine/BaseEngineInterface.h"

#include "EventHandler.h"
#include "../Utils/ListTemplates.h"

namespace Engine
{

  struct GenericEvent {
    GenericEvent(const double &dur)
      : Duration(dur) {}
    GenericEvent()
      : Repeat(false), Duration(0), Trigger([]() {}) {}

    GenericEvent(const GenericEvent &t)
      : Repeat(t.Repeat), Duration(t.Duration), Trigger(t.Trigger) {}

    //Method called when the sequence node is hit
    std::function<void(void)> Trigger = []() {};

    bool Repeat = false;
    double Duration;
  };

  class EventSequence : public BaseEngineInterface
  {
  public:

    void TickUpdate(const double &delta);
    void Render();
    void OnShutDown();

    void AdvanceEvent();
    bool IsOver() const;

    void BeginSequence();
    void PauseSequence();
    void HaltSequence();


  private:
    Util::NodeSequence<GenericEvent> EventList;
    double CurrentEventDuration;
    double CumulativeSequenceDuration;

    double TotalSequenceDuration;

  };

}

#endif
