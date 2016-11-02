#include "../../Headers/Events/EventSequence.h"

namespace Engine
{

  bool GenericEvent::TickUpdate(const double &delta)
  {
    CurrDuration += delta;
    UpdateEvent();

    return (CurrDuration >= TotalDuration);
  }

  void GenericEvent::Restart()
  {
    CurrDuration = 0;
  }

  void GenericEvent::UpdateEvent()
  {

  }

  /**
   *
   *
   *
   *
   *
   */

  EventSequence::EventSequence()
    : Paused(true), Halted(false), Finished(false)
  {
    
  }

  EventSequence::~EventSequence()
  {

  }

  void EventSequence::AddEvent(GenericEvent *Event)
  {
    EventList.AddSequence(*Event);
  }

  /**
   * Update the current event node
   *   if the event node has expired and it isn't supposed to repeat
   *   advance to the next event. If it is to repeat, restart the event node.
   * If there is no node to advance to, return false, as the event sequence is finished

   * @returns: false if the sequence is not finished, true otherwise
   */
  bool EventSequence::TickUpdate(const double &delta)
  {
    if (Halted)
      return true;

    CumulativeSequenceDuration += delta;
    Util::Node<GenericEvent> *Current = EventList.GetCurrent();

    if (Current) {
      //If the current node in the sequence isn't timed OR its time has expired
      //  invoke the trigger (callback) and advance the sequence
      //Returns true if there is a node to advance to, false if this was the last node
      //  that just expired
      if (Current->value.TickUpdate(delta)) {
        Current->value.Trigger();
        return EventList.AdvanceSequence();
      }
      else {
        return false;
      }
    }

    return true;
  }

  void EventSequence::AdvanceEvent()
  {
    
  }

  bool EventSequence::IsOver() const
  {
    return (EventList.GetEnd() == nullptr);
  }

  void EventSequence::BeginSequence()
  {
    Paused = false;
  }

  void EventSequence::PauseSequence()
  {
    Paused = true;
  }

  void EventSequence::HaltSequence()
  {
    Halted = false;
  }

  Util::Node<GenericEvent>* EventSequence::GetSequenceBeginning() const
  {
    return EventList.GetBeginning();
  }

  Util::Node<GenericEvent>* EventSequence::GetSequenceEnd() const
  {
    return EventList.GetEnd();
  }

  Util::Node<GenericEvent>* EventSequence::GetSequenceCurrent() const
  {
    return EventList.GetCurrent();
  }

}
