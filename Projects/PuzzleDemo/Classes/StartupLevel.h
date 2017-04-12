#ifndef GAME_STARTUP_LEVEL_H
#define GAME_STARTUP_LEVEL_H

#include "../../../SFEngine/ProjectIncludes.h"
#include "../../../SFEngine/Source/Headers/Objects/ProjectileBase.h"

#include "../../../SFEngine/Source/Headers/Weather/WeatherSystem.h"
#include "../../../SFEngine/Source/Headers/Weather/Lightning.h"
#include "../../../SFEngine/Source/Headers/Time/TimedSequence.h"

class StartupLevel : public Engine::BasicLevel
{
public:
  StartupLevel();
  ~StartupLevel();

  void TickUpdate(const double &delta) override;
  void Render(std::shared_ptr<sf::RenderTarget> Target) override;
  void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture);
  void OnShutDown() override;
  void HandleInputEvent(const Engine::UserEvent &evnt) override;
  void EventUpdate(sf::Event event) override;
  void OnBegin() override;

  void CleanUp() override;
  void SetNextLevel(std::shared_ptr<Engine::BasicLevel> NextLevel);

protected:

  void TriggerCrawlingLightning();
  bool m_SequenceDone = false;
  bool m_Paused       = false;

  Engine::TimedSequence m_LightningSequence;
  void LightningSequenceStarted();
  void LightningSequenceEnded();

  //Stuff for the loading spinner in the bottom-right corner of the screen
  thor::AnimationMap<sf::Sprite, std::string> m_AnimMap;
  thor::Animator<sf::Sprite, std::string>    *m_animator;
  thor::FrameAnimation m_spinnerFrames;
  sf::Sprite  m_SpinnerSprite;
  sf::Texture m_SpinnerTexture;

  bool m_LightningSequenceDone = false;
  void LightningSequenceCB(int Bolt1, int Bolt2, int Bolt3, int Bolt4);
  std::vector<std::vector<sf::Vector2f>> m_LightningTraces;
  std::vector<sf::Vector2f> m_BoltStrikePositions;


  //Stuff for shattering the textures after the initial lightning letters
  bool  m_DrawShatters        = false;
  float m_SFMLFadeDuration    = 2000.f;
  float m_CurrentFadeDuration = 0.f;

  //Stuff for animating the sprites during the shattering process
  thor::AnimationMap<sf::Sprite, std::string> m_SFMLLogoMap;
  thor::Animator<sf::Sprite, std::string>    *m_SFMLAnimator;
  thor::FrameAnimation m_SFMLLogoFrame;
  sf::Texture m_SFMLShatterTexture;
  sf::Sprite  m_SFMLBeforeShatter;

  int ShatterDivisionX = 20;
  int ShatterDivisionY = 20;

  Engine::LightningBolt m_BoltTopLeft;
  Engine::LightningBolt m_BoltTopRight;
  Engine::LightningBolt m_BoltBottomLeft;
  Engine::LightningBolt m_BoltBottomRight;

  std::shared_ptr<Engine::LightningStorm> m_LightningStorm;
  Engine::CrawlingLightningBolt m_CrawlBolts[32];

  std::shared_ptr<Engine::BasicLevel> m_NextLevel;
};

#endif
