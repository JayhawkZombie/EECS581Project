#ifndef GAME_LEVEL_STACK_H
#define GAME_LEVEL_STACK_H

#include "../../../../SFEngine/ProjectIncludes.h"
#include "../../../../SFEngine/Source/Headers/Weather/Lightning.h"
#include "../../../../SFEngine/Source/Headers/Time/TimedSequence.h"

#include "../Objects/PuzzleBall.h"

class BallStackLevel : public Engine::BasicLevel
{
public:
  BallStackLevel();
  ~BallStackLevel();

  void TickUpdate(const double &delta) override;
  void Render(std::shared_ptr<sf::RenderTarget> Target) override;
  void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture);

  void OnShutDown() override;
  void HandleInputEvent(const Engine::UserEvent &evnt) override;
  void EventUpdate(sf::Event event) override;
  void OnBegin() override;
  void OnEnd() override;
  void Reset() override;
  void UpdateObjectPhysics() override;

protected:
  void HandleUserClick(sf::Vector2i Pos);
  void CheckBallAndBolt(std::weak_ptr<Engine::Collider2D> Collider);
  void LaunchBall();
  void SpawnBall();
  void KillBall();
  
  std::shared_ptr<PuzzleBall> m_CurrentBall;
  sf::Color m_CurrentBallColor;
  sf::Color m_CurrentBoltColor;

  sf::Music m_BGMusic;
  sf::Sound m_TimeSlowDownSound; sf::SoundBuffer m_TimeSlowDownBuffer;
  sf::Sound m_TimeSpeedUpSound;  sf::SoundBuffer m_TimeSpeedUpBuffer;
  sf::Sound m_BallSpawnSound;    sf::SoundBuffer m_BallSpawnBuffer;

  std::shared_ptr<tgui::Gui> m_GameMenu;
  tgui::Button::Ptr m_DropBallButton;
  tgui::Panel::Ptr  m_PausePanel;
  tgui::Theme::Ptr  m_LevelTheme;
  sf::Font          m_MenuFont;

  Engine::TimedSequence m_GameSequencer;

  std::shared_ptr<Engine::PhysicsEngineSegmentType> m_PipeLeftWall;
  std::shared_ptr<Engine::PhysicsEngineSegmentType> m_PipeWallRight;
  std::shared_ptr<Engine::PhysicsEngineSegmentType> m_PipeDropBlock;

  std::shared_ptr<Engine::LightningBolt> m_BallKillerBolt;

  bool      m_Paused = false;
  void ShowMenu();
  void HideMenu();
  tgui::Button::Ptr m_QuitButton;
};

#endif
