#ifndef GAME_DEMO_LOADER_H
#define GAME_DEMO_LOADER_H

#include "../ProjectIncludes.h"
#include "SFEngine\ThirdParty\SelbaWard\Sprite3d.hpp"
#include "Time\TimedSequence.h"

#include "Projects/PuzzleDemo/Classes/Objects/LoadingRing.h"
#include "Projects/PuzzleDemo/Classes/Objects/Flippable.h"
#include "Projects/PuzzleDemo/Classes/Objects/LoadingBar.h"

#include "SFEngine\ThirdParty\SelbaWard\BitmapFont.hpp"
#include "SFEngine\ThirdParty\SelbaWard\BitmapText.hpp"
#include "SFEngine\ThirdParty\SelbaWard\ProgressBar.hpp"

class DemoLoadLevel : public Engine::BasicLevel
{
public:
  DemoLoadLevel();
  ~DemoLoadLevel() override final;

  void CleanUp() override final;
  void OnEnd() override final;
  void OnBegin() override final;
  void OnShutDown() override final;
  void EventUpdate(sf::Event event) override final;
  void TickUpdate(const double &delta) override final;
  void HandleInputEvent(const Engine::UserEvent &evnt) override final;
  void Render(std::shared_ptr<sf::RenderTarget> Target) override final;
  void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture) override final;
  void SetNextLevel(std::shared_ptr<Engine::BasicLevel> NextLevel);
  std::string GetClass() const override final;

protected:
  sw::BitmapFont  m_BitmapFont;
  sw::BitmapText  m_BitmapText;
  LoadingBar      m_ProgressBar;

  std::shared_ptr<Engine::BasicLevel> m_NextLevel;
  SPtrSharedMutex m_LevelMutex;
  std::shared_ptr<sf::Texture> m_TestRingTexture;
  bool   m_LoadingNextLevel = true;
  double m_LoadingWaitCount = 0;
  bool   m_CanSwitchLevel = false;
  bool   m_TimingWaitCount = false;
  LoadingRing m_TestRing;
  Flippable   m_SFMLCard;
  STexture    m_SFMLCardFrontTexture;
  STexture    m_SFMLCardBackTexture;
};

#endif
