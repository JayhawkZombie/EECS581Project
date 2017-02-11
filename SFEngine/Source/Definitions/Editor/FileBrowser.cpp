#include "../../Headers/Editor/FileBrowser.h"

namespace Engine
{



  void FileBrowser::Open(std::experimental::filesystem::v1::path path, std::function<void(std::string)> func_to_call, tgui::Theme::Ptr ThemePtr)
  {
    func = func_to_call;
    Theme = ThemePtr;
    Browser = Theme->load("ChildWindow");
    Browser->setSize({ 800, 700 });
    Browser->setPosition({ (WindowSize.x - 800) / 2.f, 200 });

    DirectoryList = Theme->load("ListBox");
    DirectoryList->setSize({ 700, 500 });
    DirectoryList->setPosition({ 50, 100 });
    DirectoryList->setItemHeight(20);
    DirectoryList->connect("doubleclicked", [this](std::string str) {this->DoubleClicked(str); });

    FileInput = Theme->load("EditBox");
    FileInput->setPosition({ 10, 650 });
    FileInput->setSize({ 600, 30 });

    SelectButton = Theme->load("Button");
    SelectButton->setPosition({ 640, 650 });
    SelectButton->setText("select");
    SelectButton->disable();
    SelectButton->connect("clicked", [this]() {this->SelectButtonClicked(); });
    Browser->add(SelectButton);

    UPButton = Theme->load("Button");
    UPButton->setPosition({ 10, 10 });
    UPButton->setSize({ 20, 20 });
    UPButton->setText("../");
    UPButton->connect("clicked", [this]() {this->GoUp(); });
    Browser->add(UPButton);
    CurrentPath = path.parent_path();
    CurrentPathLabel = Theme->load("Label");
    CurrentPathLabel->setPosition({ 40, 10 });
    CurrentPathLabel->setText(CurrentPath.string() + "/");
    CurrentPathLabel->setTextSize(14);
    Browser->add(CurrentPathLabel);

    FillTableWithCurrentPath();

    Browser->add(DirectoryList);
    Browser->add(FileInput);
    GUI->add(Browser);
    GUI->focusWidget(Browser);
    Browser->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
  }

  void FileBrowser::Close()
  {
    Browser->hideWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
    Browser->connect("unfocused", [this]() {GUI->remove(this->Browser); });
  }

  bool FileBrowser::IsItemPath(std::string maybe)
  {
    if (std::experimental::filesystem::v1::exists(maybe)) {
      return true;
    }

    return false;
  }

  std::vector<std::string> FileBrowser::GetDirectoryEntries(std::experimental::filesystem::v1::directory_iterator & iter)
  {
    std::vector<std::string> paths;

    for (auto & path : iter) {
      paths.push_back(path.path().filename().string());
    }

    return paths;
  }

  void FileBrowser::FillTableWithCurrentPath()
  {
    auto dir_iter = std::experimental::filesystem::v1::directory_iterator(CurrentPath);

    DirectoryList->removeAllItems();

    auto v = GetDirectoryEntries(dir_iter);
    for (auto & item : v) {
      DirectoryList->addItem(item);
    }
    CurrentPathLabel->setText(CurrentPath.string() + "\\");
  }

  void FileBrowser::DoubleClicked(std::string filepath)
  {
    //If it is a path, then we will travel to it
    if (std::experimental::filesystem::v1::is_directory(CurrentPath / "\\" / filepath)) {
      CurrentPath /= ("\\" + filepath);
      FillTableWithCurrentPath();  
    }
    else {
      FileInput->setText(filepath);
      SelectButton->enable();
    }
  }

  void FileBrowser::ItemSelected(std::string fileorpath)
  {
    auto path = std::experimental::filesystem::v1::path(fileorpath);

    if (std::experimental::filesystem::v1::is_regular_file(path)) {
      std::string filename = path.filename().string();
      FileInput->setText(filename);
    }
  }

  void FileBrowser::GoUp()
  {
    if (std::experimental::filesystem::v1::exists(CurrentPath.parent_path())) {
      CurrentPath = CurrentPath.parent_path();
      FillTableWithCurrentPath();
    }
    else {
      MessageAlert("!! Path does not exist !!");
    }
  }

  void FileBrowser::SelectButtonClicked()
  {
    //get the string from the input area
    std::string str = FileInput->getText();

    //if (std::experimental::filesystem::v1::exists(std::experimental::filesystem::v1::path(CurrentPath.string() + str))) {
    //  ShowOverwriteFilePopup(str);
    //}
    //else
    FileSelected(str);
  }

  void FileBrowser::FileSelected(std::string file)
  {
    if (func)
      func(CurrentPath.string() + "/" + file);
  }

  void FileBrowser::ShowOverwriteFilePopup(const std::string & file)
  {
    CreateNewFilePopup = Theme->load("ChildWindow");
    CreateNewFilePopup->setPosition({ 400, 300 });
    CreateNewFilePopup->setSize({ 400, 400 });
    
    CreateNewFileConfirmButton = Theme->load("Button");
    CreateNewFileConfirmButton->setText("confirm");
    CreateNewFileConfirmButton->setSize({ 100, 20 });
    CreateNewFileConfirmButton->setPosition({ 50, 300 });
    CreateNewFilePopup->add(CreateNewFileConfirmButton);

    CreateNewFileConfirmButton->connect("clicked", [this, str = file]() {this->OverwritePopupConfirmed(); this->FileSelected(str); });

    CreateNewFileDenyButton = Theme->load("Button");
    CreateNewFileDenyButton->setText("deny");
    CreateNewFileDenyButton->setSize({ 100, 20 });
    CreateNewFileDenyButton->setPosition({ 200, 300 });
    CreateNewFileDenyButton->connect("clicked", [this]() {this->OverwritePopupDenied(); });

    CreateNewFilePopup->add(CreateNewFileDenyButton);

    GUI->add(CreateNewFilePopup);
    CreateNewFilePopup->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
  }

  void FileBrowser::OverwritePopupConfirmed()
  {
    GUI->remove(CreateNewFilePopup);
  }

  void FileBrowser::OverwritePopupDenied()
  {
    GUI->remove(CreateNewFilePopup);
  }

}
