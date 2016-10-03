#include "../../Headers/UI/UIController.h"

namespace Engine
{
  namespace UI
  {
    UIController::UIController()
    {
      //Screw it, LAMBDAS
      //Ahhh, so much cleaner :D
      Handler.BindCallback(Events::KeyPressed, 
                           [this](const sf::Keyboard::Key &k) {this->HandleKeyPress(k); });

      Handler.BindCallback(Events::KeyReleased,
                           [this](const sf::Keyboard::Key &k) {this->HandleKeyRelease(k); });

      Handler.BindCallback(Events::MouseMoved,
                           [this](const sf::Vector2i &m) {this->HandleMouseMovement(m); });

      Handler.BindCallback(Events::MouseDown,
                           [this](const sf::Vector2i &m, const sf::Mouse::Button &b) {this->HandleMousePress(m, b); });

      Handler.BindCallback(Events::MouseReleased,
                           [this](const sf::Vector2i &m, const sf::Mouse::Button &b) {this->HandleMouseRelease(m, b); });

      FocusedElement = nullptr;
      Shown = false;
      DisplayBoundsRect = false;
      BoundsRect.setFillColor(sf::Color::Red);
    }

    UIController::~UIController()
    {
      std::cerr << "UIController destruction" << std::endl;
    }

    void UIController::TickUpdate(const double &delta)
    {

    }

    void UIController::Render()
    {
      if (!Shown)
        return;

      if (DisplayBoundsRect)
        Render::RenderShape(&BoundsRect);

      for (auto & element : Elements) {
        if (element->State.test(Active)) {
          for (auto & tgt : element->RenderTargets) {
            tgt.second.Render();
          }
        }
      }

    }

    void UIController::OnShutDown()
    {

    }

    void UIController::Show()
    {
      Shown = true;
    }

    void UIController::Hide()
    {
      Shown = false;
    }

    void UIController::ShowBoundsRect()
    {
      DisplayBoundsRect = true;
    }

    void UIController::HideBoundsRect()
    {
      DisplayBoundsRect = false;
    }

    sf::FloatRect UIController::GetBounds() const
    {
      return UIBounds;
    }
    
    bool UIController::IsShown() const
    {
      return Shown;
    }

    void UIController::ToggleShown()
    {
      Shown = !Shown;
    }

    void UIController::AddElement(std::shared_ptr<BaseUIElement> element)
    {
      Elements.push_back(std::shared_ptr<BaseUIElement>(element));
    }

    void UIController::SetBounds(const sf::FloatRect &bounds)
    {
      UIBounds =
        sf::FloatRect(
          bounds.left,
          bounds.top,
          bounds.left + bounds.width,
          bounds.top + bounds.height
        );
      BoundsRect.setPosition(sf::Vector2f(bounds.left, bounds.top));
      BoundsRect.setSize(sf::Vector2f(bounds.width, bounds.height));
    }
  }
}
