#include "../../Headers/UI/UIController.h"

namespace Engine
{
  namespace UI
  {
    UIController::UIController()
    {
      Callback_HandleKeyPress = std::bind(&UIController::HandleKeyPress, this, std::placeholders::_1);
      Handler.BindCallback(Events::KeyPressed, Callback_HandleKeyPress);

      Callback_HandleKeyRelease = std::bind(&UIController::HandleKeyRelease, this, std::placeholders::_1);
      Handler.BindCallback(Events::KeyReleased, Callback_HandleKeyRelease);

      Callback_HandleMouseMovement = std::bind(&UIController::HandleMouseMovement, this, std::placeholders::_1);
      Handler.BindCallback(Events::MouseMoved, Callback_HandleMouseMovement);
      
      Callback_HandleMousePress = std::bind(&UIController::HandleMousePress, this, std::placeholders::_1, std::placeholders::_2);
      Handler.BindCallback(Events::MouseDown, Callback_HandleMousePress);
      
      Callback_HandleMouseRelease = std::bind(&UIController::HandleMouseRelease, this, std::placeholders::_1, std::placeholders::_2);
      Handler.BindCallback(Events::MouseReleased, Callback_HandleMouseRelease);
    }

    UIController::~UIController()
    {

    }

    void UIController::TickUpdate(const double &delta)
    {

    }

    void UIController::Render()
    {

    }

    void UIController::OnShutDown()
    {

    }

    void UIController::AddElement(BaseUIElement *element)
    {
      Elements.push_back(std::shared_ptr<BaseUIElement>(std::move(element)));
    }
  }
}