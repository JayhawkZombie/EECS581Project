#ifndef GAME_LEVEL_PHYSICS_DEMO_H
#define GAME_LEVEL_PHYSICS_DEMO_H

#include "../ProjectIncludes.h"
#include "Lights\LightingSystem.h"

#include "SFEngine\ThirdParty\SelbaWard\BitmapFont.hpp"
#include "SFEngine\ThirdParty\SelbaWard\BitmapText.hpp"
#include "SFEngine\ThirdParty\SelbaWard\ProgressBar.hpp"

#include <Thor/Particles.hpp>
#include <Thor/Animations.hpp>
#include <Thor/Vectors/PolarVector2.hpp>
#include <Thor/Math/Distributions.hpp>

class PhysicsDemoLevel : public Engine::BasicLevel
{
public:

  PhysicsDemoLevel();
  ~PhysicsDemoLevel() override final;

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
  Engine::LightSystem m_LightSystem;

  SPtrShared<Engine::PhysicsEngineWaveSegment> m_Wave;

  thor::ParticleSystem m_PSystem1;
  thor::UniversalEmitter m_PEmitter1;
  thor::ColorGradient m_PColorGradient1;
  thor::ColorAnimation m_PColorAnimation1;
  thor::FadeAnimation m_PFadeAnimation1;
  thor::TorqueAffector m_PTorqueAffector1;
  thor::ForceAffector m_PGravityAffector1;

};

#endif
