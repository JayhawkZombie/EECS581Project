#include "../../Headers/Weather/Lightning.h"

namespace Engine
{

  LightningBolt::LightningBolt()
    : m_BoltDoneFunc([]() {}), m_StrikeCallback([](auto v) {})
  {
  }

  LightningBolt::~LightningBolt()
  {
  }

  void LightningBolt::TickUpdate(const double & delta)
  {
    UpdateBolt(delta);
  }

  void LightningBolt::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
    if (m_IsAlive) {
      for (auto & seg : m_Points)
        Target->draw(seg);
    }
  }


  void LightningBolt::Spark(const sf::Vector2f &StartPosition, const sf::Vector2f &EndPosition)
  {
    m_IsAlive = true;
    m_Points.clear();
    CreateBolt(StartPosition, EndPosition);
    alpha = 255;
  }

  bool LightningBolt::IsAlive() const
  {
    return m_IsAlive;
  }

  void LightningBolt::SetDoneCallback(std::function<void(void)> Callback)
  {
    m_BoltDoneFunc = Callback;
  }

  void LightningBolt::SetStrikeCallback(std::function<void(sf::Vector2f)> Callback)
  {
    m_StrikeCallback = Callback;
  }

  void LightningBolt::Reset()
  {
    m_currentFadeTime = 0.f;
    m_IsAlive = false;
  }

  void LightningBolt::UpdateBolt(const double &delta)
  {
    if (!m_IsAlive) {
      return;
    }

    m_currentFadeTime += delta;

    if (m_currentFadeTime >= m_TotalFadeTime) {
      m_IsAlive = false;
      m_currentFadeTime = 0.0;
      alpha = 0;
    }
    else {
      alpha = (unsigned char)(floor(255 * (1 - (m_currentFadeTime / m_TotalFadeTime))));
      for (auto & seg : m_Points) {
        seg[0].color.a = alpha;
        seg[1].color.a = alpha;
      }
    }
  }

  void LightningBolt::CreateBolt(const sf::Vector2f &StartPosition, const sf::Vector2f &EndPosition)
  {
    sf::Vector2f Tangent = EndPosition - StartPosition;
    sf::Vector2f Normal = sf::Vector2f(Tangent.y, -Tangent.x);

    float mag = std::sqrt((Tangent.x * Tangent.x) + (Tangent.y * Tangent.y));
    Normal /= mag;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    sf::Vector2f DistanceVec = StartPosition - EndPosition;
    float Distance = std::sqrt((DistanceVec.x * DistanceVec.x) + (DistanceVec.y * DistanceVec.y));

    std::vector<float> Positions;
    Positions.push_back(0);
    for (std::size_t i = 0; i < (int)(Distance / 8); ++i) {
      Positions.push_back(dis(gen));
    }

    std::sort(Positions.begin(), Positions.end());

    const float sway = 70;
    const float jaggedness = 1.f / sway;

    std::uniform_real_distribution<> _dis(-sway, sway);
    sf::Vector2f prevPoint = StartPosition;
    float prevDisplacement = 0.f;

    for (std::size_t i = 1; i < Positions.size(); ++i) {
      float pos = Positions[i];
      float scale = (Distance * jaggedness) * (pos - Positions[i - 1]);

      float envelope = pos > 0.95f ? 20 * (1 - pos) : 1;

      float displ = _dis(gen);
      displ -= (displ - prevDisplacement) * (1 - scale);
      displ *= envelope;

      sf::Vector2f postan = pos * Tangent;
      sf::Vector2f dispn = displ * Normal;

      sf::Vector2f point = StartPosition + postan + dispn;
      m_Points.push_back(sf::VertexArray(sf::Lines, 2));
      m_Points.back()[0].position = prevPoint; m_Points.back()[0].color = sf::Color(255, 229, 255);
      m_Points.back()[1].position = point;     m_Points.back()[1].color = sf::Color(255, 229, 255);

      prevPoint = point;
      prevDisplacement = displ;
    }

    m_Points.push_back(sf::VertexArray(sf::Lines, 2));
    m_Points.back()[0].position = prevPoint;   m_Points.back()[0].color = sf::Color(255, 229, 255);
    m_Points.back()[1].position = EndPosition; m_Points.back()[1].color = sf::Color(255, 229, 255);
  }


  /*
    Cawling lightning bolt
  */
  CrawlingLightningBolt::CrawlingLightningBolt()
    : m_BoltDoneFunc([]() {}), m_StrikeCallback([](auto v) {})
  {
    
  }

  CrawlingLightningBolt::~CrawlingLightningBolt()
  {
  }

  void CrawlingLightningBolt::GenerateBoltPoints(const sf::Vector2f & Start, const sf::Vector2f & End, std::vector<sf::VertexArray> &m_Points)
  {
    sf::Vector2f Tangent = End - Start;
    sf::Vector2f Normal = sf::Vector2f(Tangent.y, -Tangent.x);

    float mag = std::sqrt((Tangent.x * Tangent.x) + (Tangent.y * Tangent.y));
    Normal /= mag;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    sf::Vector2f DistanceVec = Start - End;
    float Distance = std::sqrt((DistanceVec.x * DistanceVec.x) + (DistanceVec.y * DistanceVec.y));

    std::vector<float> Positions;
    Positions.push_back(0);
    for (std::size_t i = 0; i < (int)(Distance / 8); ++i) {
      Positions.push_back(dis(gen));
    }

    std::sort(Positions.begin(), Positions.end());

    const float sway = 15;
    const float jaggedness = 1.f / 70.f;

    std::uniform_real_distribution<> _dis(-sway, sway);
    sf::Vector2f prevPoint = Start;
    float prevDisplacement = 0.f;

    for (std::size_t i = 1; i < Positions.size(); ++i) {
      float pos = Positions[i];
      float scale = (Distance * jaggedness) * (pos - Positions[i - 1]);

      float envelope = pos > 0.95f ? 20 * (1 - pos) : 1;

      float displ = _dis(gen);
      displ -= (displ - prevDisplacement) * (1 - scale);
      displ *= envelope;

      sf::Vector2f postan = pos * Tangent;
      sf::Vector2f dispn = displ * Normal;

      sf::Vector2f point = Start + postan + dispn;
      m_Points.push_back(sf::VertexArray(sf::Lines, 2));
      m_Points.back()[0].position = prevPoint; m_Points.back()[0].color = sf::Color(255, 229, 255);
      m_Points.back()[1].position = point;     m_Points.back()[1].color = sf::Color(255, 229, 255);

      prevPoint = point;
      prevDisplacement = displ;
    }

    m_Points.push_back(sf::VertexArray(sf::Lines, 2));
    m_Points.back()[0].position = prevPoint;   m_Points.back()[0].color = sf::Color(255, 229, 255);
    m_Points.back()[1].position = End;         m_Points.back()[1].color = sf::Color(255, 229, 255);
  }

  void CrawlingLightningBolt::UpdateBolt(const double & delta)
  {
    static float _delta_count = 0;
    _delta_count += (float)delta;

    if (_delta_count >= 1.4f * m_TimeBetweenCrawlSteps) {
      StepBolt(1);
      _delta_count = 0;
      if (m_DisplayedPoints.size() > m_MaxBoltLength)
        m_DisplayedPoints.erase(m_DisplayedPoints.begin() + 0);
    }
  }

  void CrawlingLightningBolt::CreateBolt(const sf::Vector2f & StartPosition, const sf::Vector2f & EndPosition)
  {
    m_CrawlDir = EndPosition - StartPosition;
  }

  void CrawlingLightningBolt::StepBolt(int num_steps)
  {
    if (m_Points.size() > 0) {
      int count = std::min(m_Points.size(), (std::size_t)num_steps);

      for (int i = 0; i < count; ++i) {
        m_DisplayedPoints.push_back(m_Points[0]);
        m_Points.erase(m_Points.begin() + 0);
      }
    }
    else if (m_DisplayedPoints.size() > 0) {
      //Now, then, I suppose we start erasing from the end of us here
      m_DisplayedPoints.erase(m_DisplayedPoints.begin() + 0);
    }
    else {
      m_IsAlive = false;
      m_DisplayedPoints.clear();
      m_Points.clear();
    }
  }

  void CrawlingLightningBolt::TickUpdate(const double & delta)
  {
    UpdateBolt(delta);
  }

  void CrawlingLightningBolt::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
    if (m_IsAlive) {
      for (auto & seg : m_DisplayedPoints)
        Target->draw(seg);
    }
  }

  void CrawlingLightningBolt::Spark(const std::vector<sf::Vector2f> &Positions)
  {
    for (std::size_t i = 1; i < Positions.size(); ++i) {
      GenerateBoltPoints(Positions[i - 1], Positions[i], m_Points);
    }
    m_IsAlive = true;
  }

  bool CrawlingLightningBolt::IsAlive() const
  {
    return m_IsAlive;
  }

  void CrawlingLightningBolt::SetDoneCallback(std::function<void(void)> Callback)
  {
    m_BoltDoneFunc = Callback;
  }

  void CrawlingLightningBolt::SetStrikeCallback(std::function<void(sf::Vector2f)> Callback)
  {
    m_StrikeCallback = Callback;
  }

  void CrawlingLightningBolt::Reset()
  {
    m_IsAlive = false;
    m_currentFadeTime = 0.f;
  }

  void CrawlingLightningBolt::SetCrawlSpeed(const float & BetweenSteps)
  {
    m_TimeBetweenCrawlSteps = BetweenSteps;
  }

  void CrawlingLightningBolt::SetMaxBoltLength(const float & Length)
  {
    m_MaxBoltLength = Length;
  }

}

