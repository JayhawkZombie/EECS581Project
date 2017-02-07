#include "../../../Headers/UI/Menu/EditAnimationMenu.h"

namespace Engine
{

  namespace UI
  {

    void EditAnimationMenu::ConstructMenu(std::shared_ptr<MenuWidget> UpperMenu, std::shared_ptr<MenuScreen> PreviousScreen, const sf::Vector2f &_Size, const Theme &theme, std::shared_ptr<sf::Font> _Font, 
                                          const sf::Vector2f &UpperMenuScreenPosition, const sf::Vector2f &UpperMenuScreenSize, std::shared_ptr<ClickButtonBase> OpeningButton, std::shared_ptr<sf::Texture> IconSheet)
    {
      AnimationTarget = std::make_shared<sf::RenderTexture>();
      auto __size = currentRenderWindow->getSize();
      AnimationTarget->create(__size.x, __size.y);
      //create the editing stuff inside the edit animation menu
      MakeMenuScreen(EditAnimationScreen, UI::DefaultDarkTheme, UpperMenu);
      AddMenuScreen(UpperMenu, EditAnimationScreen);
        
      MakeMenuScreenButtonNormal(OpeningButton, PreviousScreen, UpperMenu, sf::Vector2f(UpperMenuScreenPosition.x + 10.f, UpperMenuScreenPosition.y + 10.f), UI::DefaultDarkTheme, "edit animation", _Font, nullptr);
      MakeMenuScreenTransition__Struct(OpeningButton, UpperMenu, EditAnimationScreen);

      ////create the actual editing menu
      MakeMenuScreenButtonNormal(EditAnimationSaveButton, EditAnimationScreen, TestMenus, sf::Vector2f(UpperMenuScreenPosition.x + 10.f, UpperMenuScreenPosition.y + UpperMenuScreenSize.y - 50.f), UI::DefaultDarkTheme, "save(and back)", _Font, nullptr);
      MakeMenuScreenButtonBack__Struct(EditAnimationSaveButton, PreviousScreen);

      EditAnimationFileInput = UI::TextInput::Create(EditAnimationScreen->ScreenLayer, EditAnimationScreen->ScreenHelper, { UpperMenuScreenPosition.x + 10.f, UpperMenuScreenPosition.y + 10.f }, { 200, 30 }, _Font, "texture path");
      MakeMenuScreenButtonNormal(EditAnimationFileLoadButton, EditAnimationScreen, TestMenus, sf::Vector2f(UpperMenuScreenPosition.x + 250.f, UpperMenuScreenPosition.y + 10.f), UI::DefaultDarkTheme, "load", _Font, nullptr);
      ////load texture
      AnimationTexture = std::make_shared<sf::Texture>();
      
      EditAnimationFileLoadButton->MouseReleaseCB =
        [this]()
      {
        std::string path = this->EditAnimationFileInput->GetString();
        if (!(this->TryToLoad(path))) {
          this->EditAnimationFileLoadButton->SetBGColor(sf::Color::Red);
        }
        else {
          this->EditAnimationFileLoadButton->SetBGColor(sf::Color::Green);
          this->GenAnimationFrames();
        }
      };
      PreviewAnimation = std::make_shared<Animation>();
      PreviewAnimation->SetFrameTime(30);
      PreviewAnimation->SetPosition({ UpperMenuScreenPosition.x + 10.f, UpperMenuScreenPosition.y + 150.f });
      PreviewAnimation->SetSize({ 100, 100 });
      AnimationViewer = UI::ObjectView::Create(EditAnimationScreen->ScreenLayer, EditAnimationScreen->ScreenHelper, { UpperMenuScreenPosition.x + 10.f, UpperMenuScreenPosition.y + 150.f }, { 100, 100 }, PreviewAnimation);

      EditAnimationPlayButton = UI::SimpleToggle::Create(EditAnimationScreen->ScreenLayer, EditAnimationScreen->ScreenHelper, { UpperMenuScreenPosition.x + 5, UpperMenuScreenPosition.y + 100 }, { 20, 20 }, { 15, 15 }, IconSheet, "pause_medium", "play_medium");
      EditAnimationPlayButton->CheckedCB = [this]() {this->PlayAnimation(); };
      EditAnimationPlayButton->UnCheckedCB = [this]() {this->PauseAnimation(); };

      MakeMenuScreenButtonNormal(ScaleAnimationPreviewButton, EditAnimationScreen, UpperMenu, sf::Vector2f(UpperMenuScreenPosition.x + 170.f, UpperMenuScreenPosition.y + 150.f), UI::DefaultDarkTheme, "scale anim", _Font, nullptr);
      ScaleAnimationPreviewButton->MouseReleaseCB = [this]() { this->ScaleAnimation(); };
      //EditAnimationFrameCountSpinner = UI::IntSpinner::Create(EditAnimationScreen->ScreenLayer, EditAnimationScreen->ScreenHelper, { UpperMenuScreenPosition.x + 10.f, 450 }, { 60, 30 }, _Font, IconSheet, 1);

      EditAnimationNumColsSpinner = UI::IntSpinner::Create(EditAnimationScreen->ScreenLayer, EditAnimationScreen->ScreenHelper, { UpperMenuScreenPosition.x + 200.f, 440 }, { 60, 30 }, _Font, IconSheet, 1);
      
      EditAnimationNumColsSpinner->ValueChangedCB = [this]() { this->SetCols(this->EditAnimationNumColsSpinner->GetValue()); };

      auto _frame_size_x_label = UI::TextLabel::Create(EditAnimationNumColsSpinner,
                                                       EditAnimationNumColsSpinner->Helper,
                                                       UI::TextAlignment::CenterJustified, "cols",
                                                       UI::DefaultDarkTheme.TextColorNormal,
                                                       _Font, UI::DefaultDarkTheme.TextSizeNormal,
                                                       EditAnimationNumColsSpinner->GlobalWidgetBounds.GlobalBounds,
                                                       { -70, 0 });

      EditAnimationNumRowsSpinner = UI::IntSpinner::Create(EditAnimationScreen->ScreenLayer, EditAnimationScreen->ScreenHelper, { UpperMenuScreenPosition.x + 200.f, 480 }, { 60, 30 }, _Font, IconSheet, 1);

      EditAnimationNumRowsSpinner->ValueChangedCB = [this]() { this->SetRows(this->EditAnimationNumRowsSpinner->GetValue()); };

      auto _frame_size_y_label = UI::TextLabel::Create(EditAnimationNumRowsSpinner,
                                                       EditAnimationNumRowsSpinner->Helper,
                                                       UI::TextAlignment::CenterJustified, "rows",
                                                       UI::DefaultDarkTheme.TextColorNormal,
                                                       _Font, UI::DefaultDarkTheme.TextSizeNormal,
                                                       EditAnimationNumRowsSpinner->GlobalWidgetBounds.GlobalBounds,
                                                       { -70, 0 });

      EditAnimationFrameSpeedSpinner = UI::IntSpinner::Create(EditAnimationScreen->ScreenLayer, EditAnimationScreen->ScreenHelper, { UpperMenuScreenPosition.x + 200.f, 520 }, { 60, 30 }, _Font, IconSheet, 30);
      EditAnimationFrameSpeedSpinner->ValueChangedCB = [this]() { this->PreviewAnimation->SetFrameTime(static_cast<double>(this->EditAnimationFrameSpeedSpinner->GetValue())); };

      auto _frame_cnt_label = UI::TextLabel::Create(EditAnimationFrameSpeedSpinner,
                                                    EditAnimationFrameSpeedSpinner->Helper,
                                                    UI::TextAlignment::CenterJustified, "speed(fps)",
                                                    UI::DefaultDarkTheme.TextColorNormal,
                                                    _Font, UI::DefaultDarkTheme.TextSizeNormal,
                                                    EditAnimationFrameSpeedSpinner->GlobalWidgetBounds.GlobalBounds,
                                                    { -80, 0 });
    }

    bool EditAnimationMenu::TryToLoad(const std::string &file)
    {
      if (!AnimationTexture->loadFromFile(file))
        return false;

      PreviewAnimation->SetSpriteSheet(AnimationTexture, "whatever");
      
      return true;
    }

    void EditAnimationMenu::SetFPS(std::uint32_t value)
    {
      PreviewAnimation->SetFrameTime(static_cast<double>(1000.f / value));
    }

    void EditAnimationMenu::SetCols(std::uint32_t value)
    {
      NumCols = std::max(1U, value);
      std::cerr << "NumCols : " << NumCols << std::endl;
      GenAnimationFrames();
    }

    void EditAnimationMenu::SetRows(std::uint32_t value)
    {
      NumRows = std::max(1U, value);
      std::cerr << "NumRows : " << NumRows << std::endl;
      GenAnimationFrames();
    }

    void EditAnimationMenu::GenAnimationFrames()
    {
      auto size = AnimationTexture->getSize();
      int FrameWidth = std::round(size.x / (float)NumCols);
      int FrameHeight = std::round(size.y / (float)NumRows);
      PreviewAnimation->ResetFrames();

      for (int j = 0; j < NumRows; ++j) {
        for (int i = 0; i < NumCols; ++i) {
          sf::IntRect frame = {};
          frame.left = i * FrameWidth;
          frame.top = j * FrameHeight;
          frame.width = FrameWidth;
          frame.height = FrameHeight;

          PreviewAnimation->AddFrame(frame);
        }
      }

    }

    void EditAnimationMenu::PlayAnimation()
    {
      PreviewAnimation->Play();
    }

    void EditAnimationMenu::PauseAnimation()
    {
      PreviewAnimation->Pause();
    }

    void EditAnimationMenu::ScaleAnimation()
    {
      //get frame size
      float framewidth = static_cast<float>(AnimationTexture->getSize().x / (float)NumCols);
      AnimationViewer->SetSpriteScale(100.f, framewidth);
    }

  }

}