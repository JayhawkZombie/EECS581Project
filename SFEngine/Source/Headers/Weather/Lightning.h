#ifndef SFENGINE_WEATHER_LIGHTNING_H
#define SFENGINE_WEATHER_LIGHTNING_H

#include "../Level/LevelObject.h"

namespace Engine
{

  class LightningBolt : public LevelObject
  {
  public:
    LightningBolt();
    ~LightningBolt();

    void TickUpdate(const double &delta) override;
    void Render(std::shared_ptr<sf::RenderTarget> Target) override;

    void Spark(const sf::Vector2f &StartPosition, const sf::Vector2f &EndPosition);
    bool IsAlive() const;
    void SetDoneCallback(std::function<void(void)> Callback);
    void SetStrikeCallback(std::function<void(sf::Vector2f)> Callback);
    void Reset();
  protected:
    std::function<void(sf::Vector2f)> m_StrikeCallback;
    std::function<void(void)> m_BoltDoneFunc;
    void UpdateBolt(const double &delta);
    void CreateBolt(const sf::Vector2f &StartPosition, const sf::Vector2f &EndPosition);
    bool   m_IsAlive         = false;
    float  m_SparkSpeed      = 1.f;
    double m_currentFadeTime = 0.0;
    double m_TotalFadeTime   = 900.0;
    unsigned char alpha      = 255;
    std::vector<sf::VertexArray> m_Points;
  };

  class CrawlingLightningBolt : public LevelObject
  {
  public:
    CrawlingLightningBolt();
    ~CrawlingLightningBolt();

    void TickUpdate(const double &delta) override;
    void Render(std::shared_ptr<sf::RenderTarget> Target) override;

    void Spark(const std::vector<sf::Vector2f> &Positions);
    bool IsAlive() const;
    void SetDoneCallback(std::function<void(void)> Callback);
    void SetStrikeCallback(std::function<void(sf::Vector2f)> Callback);
    void Reset();

    void SetCrawlSpeed(const float &BetweenSteps);
    void SetMaxBoltLength(const float &Length);

  protected:
    float m_TimeBetweenCrawlSteps = 16.f;
    float m_MaxBoltLength         = 3500.f;

    std::function<void(sf::Vector2f)> m_StrikeCallback;
    std::function<void(void)> m_BoltDoneFunc;

    static void GenerateBoltPoints(const sf::Vector2f &Start, const sf::Vector2f &End, std::vector<sf::VertexArray> &m_Points);

    void UpdateBolt(const double &delta);
    void CreateBolt(const sf::Vector2f &StartPosition, const sf::Vector2f &EndPosition);
    void StepBolt(int num_steps);

    sf::Vector2f m_CrawlDir;
    std::vector<float> m_Positions;
    float m_Sway = 40.f;
    float m_Jaggedness = 1.f / 90.f;
    float m_PrevDisplacement = 0.f;

    bool   m_IsAlive         = false;
    float  m_SparkSpeed      = 1.f;
    double m_currentFadeTime = 0.0;
    double m_TotalFadeTime   = 900.0;
    unsigned char alpha      = 255;
    std::vector<sf::VertexArray> m_Points;
    std::vector<sf::VertexArray> m_DisplayedPoints;
  };

}

#endif
