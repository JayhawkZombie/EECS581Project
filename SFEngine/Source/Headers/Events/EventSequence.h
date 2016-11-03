#ifndef SFENGINE_EVENT_SEQUENCE_H
#define SFENGINE_EVENT_SEQUENCE_H

#include "../Engine/BaseEngineInterface.h"

#include "EventHandler.h"
#include "../Utils/ListTemplates.h"

namespace Engine
{

  struct GenericEvent {
    GenericEvent(Events t, const double &dur)
     : EventTrigger(t), TotalDuration(dur), CurrDuration(0) {}
    GenericEvent()
      : Repeat(false), TotalDuration(0), CurrDuration(0), Trigger([]() {}) {}

    GenericEvent(const GenericEvent &t)
     : Repeat(t.Repeat), TotalDuration(t.TotalDuration), CurrDuration(0), Trigger(t.Trigger) {}

    //Method called when the sequence node is hit
    std::function<void(void)> Trigger;
    Events EventTrigger;

    bool TickUpdate(const double &delta); 
    virtual void UpdateEvent();
    virtual void Restart();

    bool Repeat = false;
    double TotalDuration;
    double CurrDuration;
  };

  class EventSequence
  {
  public:
    EventSequence();
    ~EventSequence();

    bool TickUpdate(const double &delta);

    void AdvanceEvent();
    bool IsOver() const;

    void BeginSequence();
    void PauseSequence();
    void HaltSequence();

    bool Paused;
    bool Halted;
    bool Finished;

    Util::Node<GenericEvent>* GetSequenceBeginning() const;
    Util::Node<GenericEvent>* GetSequenceEnd() const;
    Util::Node<GenericEvent>* GetSequenceCurrent() const;

    void AddEvent(GenericEvent *Event);


  private:
    Util::NodeSequence<GenericEvent> EventList;
    double CurrentEventDuration;
    double CumulativeSequenceDuration;

    double TotalSequenceDuration;

  };

}

#endif
