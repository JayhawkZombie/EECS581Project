#include "../../Headers/Weather/WeatherSystem.h"
#include "../../Headers/Weather/Lightning.h"

namespace Engine
{

  LightningStorm::LightningStorm()
  {
    m_random_dist = std::uniform_real_distribution<float>(0, 100);
    rand_generator = std::mt19937(rd());
    m_Done = false;
    m_Intensity = 1;
  }

  LightningStorm::~LightningStorm()
  {
  }

  void LightningStorm::Start()
  {
    m_Started = true;
    m_CurrentDuration = 0.f;
  }

  void LightningStorm::End()
  {
    m_Done = true;
    m_CurrentDuration = 0.f;
  }

  void LightningStorm::TickUpdate(const double & delta)
  {
    for (std::size_t i = 0; i < m_Bolts.size(); ++i) {
      if (m_Bolts[i]->IsAlive()) {
        m_Bolts[i]->TickUpdate(delta);

        if (!m_Bolts[i]->IsAlive())
          FreeBolt(i);
      }
    }

    /*
      As the intensity gets higher and higher, there is a higher chance of
        spawning a bolt every frame
    */
    //We only want to check every 16ms, otherwise we'll fire too often
    static double _update_check = 0.0;
    _update_check += delta;

    if (_update_check < 66.667)
      return;
    
    _update_check = 0.0;

    int attempt = rand() % 100;

    //If the probability is less than or equal to the random number chosen (between 0 and 100), then we will spawn a bolt
    //  (if there are any free)
    m_CurrentDuration += (float)delta;
    if (m_CurrentDuration >= m_TotalDuration) {
      m_Done = true;
      return;
    }

    if (attempt <= m_Intensity) {
      
      if (m_FreeBolts.size() > 0) {
        //Grab the first free bolt and spawn it, removing it from the set of free bolts
        std::size_t free_idx = *m_FreeBolts.begin();

        SpawnBolt(free_idx);
      }

    }

  }

  void LightningStorm::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
    for (auto & bolt : m_Bolts) {
      if (bolt->IsAlive())
        bolt->Render(Target);
    }
  }

  void LightningStorm::SetTotalDuration(float Duration)
  {
    m_TotalDuration = Duration;
  }

  void LightningStorm::IncreaseIntensity(int delta)
  {
    m_Intensity += delta;
    m_Intensity = std::min(100, m_Intensity);
    std::cerr << "Lightning storm intensity: " << m_Intensity << std::endl;
  }

  void LightningStorm::DecreaseIntensity(int delta)
  {
    m_Intensity -= delta;
    m_Intensity = std::max(0, m_Intensity);
    std::cerr << "Lightning storm intensity: " << m_Intensity << std::endl;
  }

  void LightningStorm::AllocateBolts(std::size_t NumBolts)
  {
    m_Bolts.reserve(NumBolts);

    for (std::size_t i = 0; i < NumBolts; ++i) {
      m_Bolts.push_back(std::make_shared<LightningBolt>());
      m_Bolts.back()->SetDoneCallback(
        [_i = i, this]() { this->FreeBolt(_i); }
      );

      m_FreeBolts.insert(i);
    }
  }

  void LightningStorm::FreeBolt(std::size_t Index)
  {
    m_FreeBolts.insert(Index);
    m_Bolts[Index]->Reset();
  }

  void LightningStorm::SpawnBolt(std::size_t Index)
  {
    sf::Vector2f EndPosition;
    float _x = __TO_FLOAT__((rand() % 1700));

    EndPosition.x = _x + __TO_FLOAT__((rand() % 150) + 35);
    EndPosition.y = 700.f + + __TO_FLOAT__((rand() % 200) + 50);
    m_Bolts[Index]->Spark(sf::Vector2f(_x, 0.f), EndPosition);
    m_FreeBolts.erase(Index);
  }

}