#include "../../Headers/Editor/TileSheetEditor.h"
#include "..\..\Headers\Editor\CreateNewProject.h"

#include <filesystem>

namespace Engine
{



  void NewProjectCreator::Open(tgui::Theme::Ptr ThemePtr)
  {
    Theme = ThemePtr;
    float xDiff = WindowSize.x - 700.f;
    float yDiff = WindowSize.y - 400.f;
    //create the window
    CreationWindow = Theme->load("ChildWindow");
    CreationWindow->setPosition({ xDiff / 2.f, yDiff / 4.f });
    CreationWindow->setSize({ 700, 400 });


    //create the edit fields to enter a project title
    ProjectNameInput = Theme->load("EditBox");
    ProjectNameInput->setDefaultText("project name");
    ProjectNameInput->setSize({ 550, 30 });
    ProjectNameInput->setPosition({ 10, 10 });

    BrowseFileButton = Theme->load("Button");
    BrowseFileButton->setText("browse");
    BrowseFileButton->setSize({ 100, 20 });
    BrowseFileButton->setPosition({ 570, 10 });
    BrowseFileButton->connect("clicked", [this]() {this->OpenFileBrowser(); });
    CreationWindow->add(BrowseFileButton);

    ProjectPathInput = Theme->load("EditBox");
    ProjectPathInput->setDefaultText("project path: " + std::experimental::filesystem::current_path().string());
    ProjectPathInput->setSize({ 550, 30 });
    ProjectPathInput->setPosition({ 10, 100 });

    CreateProjectButton = Theme->load("Button");
    CreateProjectButton->setText("create project");
    CreateProjectButton->setPosition({ 10, 160 });
    CreateProjectButton->connect("clicked", [this]() {this->CreateProject(); });

    CancelButton = Theme->load("Button");
    CancelButton->setText("cancel");
    CancelButton->setPosition({ 150, 160 });
    CancelButton->connect("clicked", [this]() {this->CancelCreation(); });

    ProjectInputDefaultAssetsCheck = Theme->load("CheckBox");
    ProjectInputDefaultAssetsCheck->setText("include default assets");
    ProjectInputDefaultAssetsCheck->setPosition({ 10, 60 });
    ProjectInputDefaultAssetsCheck->setSize({ 25, 25 });
    ProjectInputDefaultAssetsCheck->check();

    CreationWindow->add(ProjectNameInput);
    CreationWindow->add(ProjectPathInput);
    CreationWindow->add(CreateProjectButton);
    CreationWindow->add(CancelButton);
    CreationWindow->add(ProjectInputDefaultAssetsCheck);
    GUI->add(CreationWindow);
    GUI->focusWidget(CreationWindow);
    CreationWindow->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
  }

  void NewProjectCreator::Close()
  {
    CreationWindow->remove(CreationWindow);
    CreationWindow->destroy();
  }

  void NewProjectCreator::CreateProject()
  {
    std::ofstream out;
    std::string path = ProjectPathInput->getText();
    std::string name = ProjectNameInput->getText();
    if (path.back() != '/')
      path += '/';

    if (path.empty()) {
      MessageAlert("Project name must not be empty!");
      return;
    }
    else if (path == "project path") {
      MessageAlert("Project name must not be the default name");
      return;
    }

    path += name + ".sfproject";

    out.open(path);
    if (!out) {
      MessageAlert("Unable to create project file: \n" + path);
      out.clear();
      out.close();
      return;
    }

    ProjectFileTag Tag = ProjectFileTag::Beginning;
    //serialize the current time stamp
    SerializeUint64(Tag, out); //write the tag
    std::uint64_t timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    SerializeUint64(timestamp, out);

    //write out the file path for extra checking
    Tag = ProjectFileTag::PathCheck;
    SerializeUint64(Tag, out);
    SerializeString(path, out);

    //serialize the engine version
    Tag = ProjectFileTag::EngineVersion;
    SerializeUint64(Tag, out);
    SerializeString(EngineVersionString, out);

    Tag = ProjectFileTag::EOFMarker;
    SerializeUint64(Tag, out);

    //Serialize the EOF marker, mark the end of the project file
    SerializeUint32(EOFMarker, out);

    out.close();
    Close();

    MessageAlert("Project file created: \n" + path);
  }

  void NewProjectCreator::CancelCreation()
  {
    CreationWindow->remove(CreationWindow);
    CreationWindow->destroy();
  }

  void NewProjectCreator::OpenFileBrowser()
  {
    Browser.Open(std::experimental::filesystem::v1::current_path(), [](auto) {}, Theme);
  }

}
