#ifndef SFENGINE_EDITOR_FILE_BROWSER_H
#define SFENGINE_EDITOR_FILE_BROWSER_H

#include <TGUI\TGUI.hpp>
#include "../Globals/GlobalHooks.h"
#include <filesystem>
#include <vector>

namespace Engine
{

  class FileBrowser
  {
  public:
    FileBrowser() = default;
    ~FileBrowser() = default;

    void Open(std::experimental::filesystem::v1::path path, std::function<void(std::string)> func_to_call, tgui::Theme::Ptr ThemePtr);
    void Close();

  protected:
    bool IsItemPath(std::string maybe);
    std::vector<std::string> GetDirectoryEntries(std::experimental::filesystem::v1::directory_iterator &iter);
    void FillTableWithCurrentPath();
    void DoubleClicked(std::string filepath);
    void ItemSelected(std::string fileorpath);
    void GoUp();

    void SelectButtonClicked();
    void FileSelected(std::string file);

    void ShowOverwriteFilePopup(const std::string &file);
    void OverwritePopupConfirmed();
    void OverwritePopupDenied();
    
    tgui::ChildWindow::Ptr Browser;
    tgui::Label::Ptr CurrentPathLabel;
    tgui::ListBox::Ptr DirectoryList;
    tgui::EditBox::Ptr FileInput;
    tgui::Button::Ptr SelectButton;
    tgui::Theme::Ptr Theme;

    std::experimental::filesystem::v1::path CurrentPath;

    std::function<void(std::string)> func = [](std::string s) {};

    tgui::ChildWindow::Ptr CreateNewFilePopup;
    tgui::Button::Ptr CreateNewFileConfirmButton;
    tgui::Button::Ptr CreateNewFileDenyButton;
    tgui::Button::Ptr UPButton;
  };

}

#endif
