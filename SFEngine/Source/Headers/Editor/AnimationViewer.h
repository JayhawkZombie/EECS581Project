#ifndef SFENGINE_ANIMATION_VIEWER_H
#define SFENGINE_ANIMATION_VIEWER_H

#include "../BasicIncludes.h"
#include "../Animation/Animation.h"

namespace Engine
{

  class AnimationViewer
  {
  public:
    AnimationViewer(tgui::Theme::Ptr tPtr);
    ~AnimationViewer();

    void Open(std::shared_ptr<Animation> Animation);
    void Close();

    void TickUpdate(const double &delta);
    void Render();
    bool IsOpen();

  protected:
    void SpinnerClicked(int value);
    void PlayPauseClicked();

    tgui::ChildWindow::Ptr Window;
    tgui::Canvas::Ptr Canvas;
    tgui::SpinButton::Ptr FPSSpinner;
    tgui::Label::Ptr FPSCurrent;
    tgui::Button::Ptr PlayPauseButton;
    tgui::Theme::Ptr Theme;
    tgui::EditBox::Ptr NameEdit;

    Animation *Anim;
    bool Playing = true;
    sf::RectangleShape AnimRect;
    std::shared_ptr<sf::RenderTexture> Texture;
  };

}

#endif
