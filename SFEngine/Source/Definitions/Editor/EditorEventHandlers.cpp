#include "../../Headers/Engine/Editor.h"

namespace Engine
{


  void Editor::HandleMousePressed(const InputEvent &Event)
  {
    //DEBUG_ONLY std::cerr << "Editor::HandleMousePressed" << std::endl;

    UIHelper->ConsumeEvent(Event);
  }

  void Editor::HandleMouseReleased(const InputEvent &Event)
  {
    //DEBUG_ONLY std::cerr << "Editor::HandleMouseReleased" << std::endl;

    UIHelper->ConsumeEvent(Event);
  }

  void Editor::HandleMouseMoved(const InputEvent &Event)
  {
    //Let's see if the mouse is over any of our elements
    //DEBUG_ONLY std::cerr << "Editor::HandleMouseMoved" << std::endl;

    UIHelper->ConsumeEvent(Event);

  }

  void Editor::HandleMouseScrolled(const InputEvent &Event)
  {

  }

  void Editor::HandleKeyPressed(const InputEvent &Event)
  {

  }

  void Editor::HandleKeyReleased(const InputEvent &Event)
  {

  }

  void Editor::HandleTextEntered(const InputEvent &Event)
  {

  }


}
