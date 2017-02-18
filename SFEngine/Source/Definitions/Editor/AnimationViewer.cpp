#include "../../Headers/Editor/AnimationViewer.h"

namespace Engine
{
  AnimationViewer::AnimationViewer(tgui::Theme::Ptr tPtr)
    : Anim(nullptr)
  {
    Theme = tPtr;
    Window = Theme->load("ChildWindow");
    Window->setSize({ 400, 400 });

    float xDiff = WindowSize.x - 400.f;
    float yDiff = WindowSize.y - 400.f;
    Window->setPosition({ xDiff / 2.f, yDiff / 2.f });

    NameEdit = Theme->load("EditBox");
    NameEdit->setSize({ 100, 20 });
    NameEdit->setPosition({ 290, 10 });
    Window->add(NameEdit);

    Canvas = std::make_shared<tgui::Canvas>();
    Canvas->setSize({ 250, 250 });
    Canvas->setPosition({ 10, 10 });
    Window->add(Canvas);

    PlayPauseButton = Theme->load("Button");
    PlayPauseButton->setSize({ 40, 20 });
    PlayPauseButton->setText("Play");
    
    xDiff = PlayPauseButton->getSize().x;
    PlayPauseButton->setPosition({ 10 + xDiff / 2.f, 370 });
    Window->add(PlayPauseButton);

    FPSSpinner = Theme->load("SpinButton");
    FPSSpinner->setMinimum(10);
    FPSSpinner->setMaximum(100);
    FPSSpinner->setValue(40);
    FPSSpinner->setPosition({ 270, 50 });
    FPSSpinner->setSize({ 50, 50 });
    FPSSpinner->connect("valuechanged", [this](int value) {this->SpinnerClicked(value); });
    Window->add(FPSSpinner);

    FPSCurrent = Theme->load("Label");
    FPSCurrent->setText(std::to_string(FPSSpinner->getValue()));
    FPSCurrent->setSize({ 100, 20 });
    FPSCurrent->setPosition({ 270, 110 });
    Window->add(FPSCurrent);

    AnimRect.setSize({ 250, 250 });
    Texture = std::make_shared<sf::RenderTexture>();
    Texture->create(250, 250);
    AnimRect.setTexture(&(Texture->getTexture()));
    AnimRect.setTextureRect({ 0, 0, 250, 250 });
    AnimRect.setOutlineColor(sf::Color::White);
    AnimRect.setOutlineThickness(-1);
    Window->hide();
  }

  AnimationViewer::~AnimationViewer()
  {

  }

  void AnimationViewer::Open(std::shared_ptr<Animation> Animation)
  {
    Texture.reset();
    Texture = std::make_shared<sf::RenderTexture>();
    Texture->create(250, 250);
    GUI->add(Window, "AnimationViewerWindow");
    Window->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
    Anim = Animation.get();
    Anim->Play();
    Anim->SetSize({ 250, 250 });
  }

  void AnimationViewer::Close()
  {
    Window->hideWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
    GUI->remove(Window);
    Anim = nullptr;
  }

  bool AnimationViewer::IsOpen()
  {
    return Window->isVisible();
  }

  void AnimationViewer::TickUpdate(const double &delta)
  {
    if (Anim) {
      Anim->TickUpdate(delta);
    }
  }

  void AnimationViewer::Render()
  {
    if (Anim) {
      Texture->clear(sf::Color::Black);
      Anim->Render(Texture);
      AnimRect.setTexture(&(Texture->getTexture()));
      Texture->display();
      Canvas->draw(AnimRect);
    }
  }

  void AnimationViewer::SpinnerClicked(int value)
  {
    if (Anim) {
      Anim->SetFrameTime(static_cast<double>(value));
      FPSCurrent->setText(std::to_string(value));
    }
  }

  void AnimationViewer::PlayPauseClicked()
  {
    if (Playing && Anim) {
      Anim->Pause();
      PlayPauseButton->setText("Play");
    }
    else {
      Anim->Play();
      PlayPauseButton->setText("Pause");
    }
  }

}
