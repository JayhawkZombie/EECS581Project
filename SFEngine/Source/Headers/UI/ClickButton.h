#ifndef SFENGINE_UI_CLICK_BUTTON_H
#define SFENGINE_UI_CLICK_BUTTON_H

#include "BaseUIElement.h"

namespace Engine
{
  namespace UI
  {
    class ClickButton : public BaseUIElement
    {
    public:
      std::shared_ptr<ClickButton> Create();

      ClickButton();
      ClickButton(const ClickButton &) = delete;
      ~ClickButton();
      
      virtual void TickUpdate(const double &delta) = 0;
      virtual void Render();
      virtual void OnShutDown() = 0;


    private:
    };
  }
}




#endif
