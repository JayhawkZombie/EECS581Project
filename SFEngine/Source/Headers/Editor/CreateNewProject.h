#ifndef SFENGINE_EDITOR_NEW_PROJECT_H
#define SFENGINE_EDITOR_NEW_PROJECT_H

#include <TGUI\TGUI.hpp>
#include "../Level/Level.h"
#include "EditorProject.h"
#include "FileBrowser.h"

namespace Engine
{

  class NewProjectCreator
  {
  public:
    NewProjectCreator() = default;
    ~NewProjectCreator() = default;

    void Open(tgui::Theme::Ptr Theme);
    void Close();

  protected:
    void CreateProject();
    void CancelCreation();
    void OpenFileBrowser();

    FileBrowser Browser;

    tgui::Theme::Ptr Theme;
    tgui::ChildWindow::Ptr CreationWindow;
    tgui::EditBox::Ptr ProjectNameInput;
    tgui::EditBox::Ptr ProjectPathInput;
    tgui::CheckBox::Ptr ProjectInputDefaultAssetsCheck;

    tgui::ComboBox::Ptr ProjectTypeCombo;
    tgui::Button::Ptr CreateProjectButton;
    tgui::Button::Ptr BrowseFileButton;
    tgui::Button::Ptr CancelButton;
  };

}

#endif
