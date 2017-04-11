#include "../../Headers/Weather/WeatherSystem.h"

namespace Engine
{



  WeatherEvent::WeatherEvent()
  {
  }

  WeatherEvent::~WeatherEvent()
  {
  }

  float WeatherEvent::GetTotalDuration()
  {
    return m_TotalDuration;
  }

  float WeatherEvent::GetCurrentDuration()
  {
    return m_CurrentDuration;
  }

  bool WeatherEvent::IsDone()
  {
    return m_Done;
  }

  void WeatherEvent::SetDoneCallback(std::function<void(void)> Callback)
  {
    m_DoneCallback = Callback;
  }

  WeatherSystem::WeatherSystem()
  {
  }

  WeatherSystem::~WeatherSystem()
  {
  }

  void WeatherSystem::SpawnEvent(std::shared_ptr<WeatherEvent> Event, std::function<void(void)> Completed)
  {
    Event->SetDoneCallback(Completed);
    Event->Start();
    m_Events.push_back(Event);
  }

  void WeatherSystem::TickUpdate(const double & delta)
  {
    for (auto & event : m_Events) {
      if (!event->IsDone())
        event->TickUpdate(delta);
    }
  }

  void WeatherSystem::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
    for (auto & event : m_Events) {
      if (!event->IsDone())
        event->Render(Target);
    }
  }

}
