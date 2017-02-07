#ifndef SFENGINE_EDIT_ANIMATION_MENU_H
#define SFENGINE_EDIT_ANIMATION_MENU_H

#include "MenuWidget.h"
#include "MenuScreen.h"
#include "../Buttons/ClickButtonBase.h"
#include "../Text/TextLabel.h"
#include "../Input/TextInput.h"
#include "../Input/Spinner.h"
#include "../Toggles/SimpleToggle.h"
#include "../UICreationMacros.h"
#include "../../Animation/Animation.h"
#include "../Theme.h"

#include "../ObjectView.h"

namespace Engine
{

  namespace UI
  {

    struct EditAnimationMenu
    {
      void ConstructMenu(std::shared_ptr<MenuWidget> UpperMenu, std::shared_ptr<MenuScreen> PreviousScreen, const sf::Vector2f &Size, const Theme &theme, std::shared_ptr<sf::Font> _Font,
                         const sf::Vector2f &UpperMenuScreenPosition, const sf::Vector2f &UpperMenuScreenSize, std::shared_ptr<ClickButtonBase> OpeningButton, std::shared_ptr<sf::Texture> IconSheet);

      //Edit animation menu
      UIMenu EditMenu;
      UIMenuScreen EditAnimationScreen;
      UITextInput EditAnimationFileInput;
      UIButton EditAnimationFileLoadButton;
      //UIIntSpinner EditAnimationFrameCountSpinner;
      UIIntSpinner EditAnimationNumColsSpinner;
      UIIntSpinner EditAnimationNumRowsSpinner;
      UIIntSpinner EditAnimationFrameSpeedSpinner;
      //UIIntSpinner EditAnimationEditFrameLeftSpinner;
      //UIIntSpinner EditAnimationEditFrameTopSpinner;
      //UIIntSpinner EditAnimationEditFrameWidthSpinner;
      //UIIntSpinner EditAnimationEditFrameHeightSpinner;

      UIButton EditAnimationPauseAnimationButton;
      UIButton ScaleAnimationPreviewButton;
      //UIButton EditAnimationStepForwardButton;
      //UIButton EditAnimationStepBackButton;

      UIButton EditAnimationTexturePreviewFillinButton;
      UIButton EditAnimationAnimationPreviewFillinButton;

      UIButton EditAnimationCancelButton;
      UIButton EditAnimationSaveButton;

      UIButton EditAnimationButton;

      UIToggle EditAnimationPlayButton;
      UIObjectView AnimationViewer;

      std::shared_ptr<Animation> PreviewAnimation;
      std::shared_ptr<sf::Texture> AnimationTexture;
      std::shared_ptr<sf::RenderTexture> AnimationTarget;
      std::uint32_t NumRows = 1;
      std::uint32_t NumCols = 1;
      sf::RectangleShape AnimationRect;
      sf::RectangleShape TextureRect;
    private:
      bool TryToLoad(const std::string &file);
      void SetFPS(std::uint32_t value);
      void SetCols(std::uint32_t value);
      void SetRows(std::uint32_t value);
      void GenAnimationFrames();
      void PlayAnimation();
      void PauseAnimation();
      void ScaleAnimation();
    };

  }

}

#endif
