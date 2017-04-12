#ifndef GAME_GEM_H
#define GAME_GEM_H

#include "../../../../SFEngine/ProjectIncludes.h"

class ShatterGem : public Engine::LevelObject
{
public:
  ShatterGem();
  ~ShatterGem();

  void Render(std::shared_ptr<sf::RenderTarget> Target) override;
  void TickUpdate(const double &delta) override;
  void PhysicsUpdate() override;
  void OnShutDown() override;

  void OnGameStart() override;
  void OnGameEnd()   override;
  void OnKilled()    override;
  void OnSpawn()     override;

  void Shatter();
  void Reassemble();
protected:

  void RenderShatteredFragments();
  void UpdateShatteredFragments();

  std::vector<sf::VertexArray> m_ShatteredFragmentArrays;
  std::vector<sf::Vector2f>    m_ShatteredFragmentVelocities;

  std::vector<sf::IntRect> m_ShatterPieces;
  sf::Texture m_ShatterTexture;

  thor::FrameAnimation m_NormalAnimation;
  thor::FrameAnimation m_DeathAnimation;
  thor::FrameAnimation m_SpawnAnimation;

  thor::AnimationMap<sf::CircleShape, std::string> m_AnimationMap;
  thor::Animator<sf::CircleShape, std::string>    *m_Animator;

  sf::Sound m_ShatterSound;        sf::SoundBuffer m_ShatterBuffer;
  sf::Sound m_ReverseShatterSound; sf::SoundBuffer m_ReverseShatterBuffer;
};

#endif
