#ifndef GAME_PUZZLE_LEVEL_1_H
#define GAME_PUZZLE_LEVEL_1_H

#include "../../../SFEngine/ProjectIncludes.h"
#include "../../../SFEngine/Source/Headers/Objects/ProjectileBase.h"

#include "../../../SFEngine/Source/Headers/Weather/WeatherSystem.h"
#include "../../../SFEngine/Source/Headers/Weather/Lightning.h"

class Level1 : public Engine::BasicLevel
{
public:
  Level1();
  ~Level1();

  void TickUpdate(const double &delta) override;

  void Render(std::shared_ptr<sf::RenderTarget> Target) override;
  void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture);

  void OnShutDown() override;

  void HandleInputEvent(const Engine::UserEvent &evnt) override;

  void EventUpdate(sf::Event event) override;

  void OnBegin() override;

protected:
  void TriggerCrawlingLightning();

  sf::Font font;
  std::shared_ptr<tgui::Gui> MainGUI;
  tgui::Theme::Ptr MenuTheme;
  tgui::Panel::Ptr MainPanel;
  tgui::Panel::Ptr OptionsPanel;

  tgui::Button::Ptr NewGameButton;
  tgui::Button::Ptr LoadGameButton;
  tgui::Button::Ptr OptionsButton;
  tgui::Button::Ptr AboutButton;
  tgui::Button::Ptr CloseButton;

  thor::UniversalEmitter emitter;
  thor::ParticleSystem system;
  thor::ColorGradient gradient;
  thor::ColorAnimation *colorizer;
  thor::FadeAnimation fader;
  sf::Texture texture;
  sf::Clock fClock;
  thor::PolarVector2f velocity;

  bool m_Paused = false;

  Engine::LightningBolt m_BoltTopLeft;
  Engine::LightningBolt m_BoltTopRight;
  Engine::LightningBolt m_BoltBottomLeft;
  Engine::LightningBolt m_BoltBottomRight;

  std::shared_ptr<Engine::LightningStorm> m_LightningStorm;
  Engine::CrawlingLightningBolt m_CrawlBolts[32];

  bool m_ExplosionPlay = false;
  bool m_drawflare = true;
  thor::AnimationMap<sf::Sprite, std::string> m_AnimMap;
  thor::FrameAnimation m_flare;
  thor::Animator<sf::Sprite, std::string> *m_animator;
  sf::Sprite m_flareSprite;
  sf::Texture flareTexture;

  void CreateNewGame();
  void LoadSaveGame();
  void EraseSaveGame();

  void ShowAboutScreen();

};

#endif
