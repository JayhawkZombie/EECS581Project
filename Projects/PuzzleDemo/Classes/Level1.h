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
  void MakeCreditsPanel();


  sf::Font font;
  std::shared_ptr<tgui::Gui> m_MainGUI;
  tgui::Theme::Ptr m_MenuTheme;
  tgui::Panel::Ptr m_MainPanel;
  tgui::Panel::Ptr m_OptionsPanel;
  tgui::Panel::Ptr m_LevelSelectPanel;

  tgui::Button::Ptr m_NewGameButton;
  tgui::Button::Ptr m_LevelSelectButon;
  tgui::Button::Ptr m_LoadGameButton;
  tgui::Button::Ptr m_OptionsButton;
  tgui::Button::Ptr m_AboutButton;
  tgui::Button::Ptr m_CloseButton;
  tgui::Button::Ptr m_CreditsButton;

  tgui::Button::Ptr    m_ToMainMenuButton;
  tgui::Label::Ptr     m_CreditsLabel;
  tgui::Scrollbar::Ptr m_CreditsScrollBar;
  tgui::Panel::Ptr     m_CreditsPanel;

  tgui::Label::Ptr     m_ProgrammingSectionLabel;
  tgui::Label::Ptr     m_DesignSectionLabel;
  tgui::Label::Ptr     m_MusicSectionLabel;

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
