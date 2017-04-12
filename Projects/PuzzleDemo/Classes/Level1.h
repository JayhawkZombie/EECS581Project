#ifndef GAME_PUZZLE_LEVEL_1_H
#define GAME_PUZZLE_LEVEL_1_H

#include "../../../SFEngine/ProjectIncludes.h"
#include "../../../SFEngine/Source/Headers/Objects/ProjectileBase.h"

#include "../../../SFEngine/Source/Headers/Weather/WeatherSystem.h"
#include "../../../SFEngine/Source/Headers/Weather/Lightning.h"
#include "../../../SFEngine/Source/Headers/Time/TimedSequence.h"

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
  void OnEnd()   override;
  
protected:
  sf::Font font;
  std::shared_ptr<tgui::Gui> MainGUI;
  tgui::Theme::Ptr MenuTheme;
  tgui::Panel::Ptr MainPanel;
  tgui::Panel::Ptr OptionsPanel;
  tgui::Panel::Ptr LevelSelectPanel;

  tgui::Button::Ptr NewGameButton;
  tgui::Button::Ptr LevelSelectButon;
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

  sf::SoundBuffer m_BGMusicBuffer;
  sf::Sound m_BGMusic;

  //Pointers for levels
  std::shared_ptr<BasicLevel> OakTreeLevelPtr;
  std::shared_ptr<BasicLevel> BallPuzzleLevelPtr;
  tgui::Button::Ptr LevelSelectBack;

  bool m_Paused = false;

  void CreateNewGame();
  void LoadSaveGame();
  void EraseSaveGame();

  void ShowAboutScreen();

  void ShowLevelSelectScreen();
  void LevelSelectGoBack();
};

#endif
