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
      for (auto & element : Elements) {
        for (auto & tgt : element->RenderTargets) {
          tgt.second.Render();
        }
      }

    }

    void UIController::OnShutDown()
    {

    }

    void UIController::AddElement(std::shared_ptr<BaseUIElement> element)
    {
      Elements.push_back(std::shared_ptr<BaseUIElement>(element));
    }
  }
}
