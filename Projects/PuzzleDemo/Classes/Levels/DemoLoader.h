#ifndef GAME_DEMO_LOADER_H
#define GAME_DEMO_LOADER_H

#include "../ProjectIncludes.h"
#include "SFEngine\ThirdParty\SelbaWard\Sprite3d.hpp"
#include "Time\TimedSequence.h"

#include "Projects/PuzzleDemo/Classes/Objects/LoadingRing.h"
#include "Projects/PuzzleDemo/Classes/Objects/Flippable.h"

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
  std::shared_ptr<Engine::BasicLevel> m_NextLevel;
  std::shared_ptr<sf::Texture> m_TestRingTexture;
  LoadingRing m_TestRing;
  Flippable   m_SFMLCard;
  STexture    m_SFMLCardFrontTexture;
  STexture    m_SFMLCardBackTexture;
};

#endif
