#include "../../Headers/Engine/Editor.h"

namespace Engine
{

  void Editor::CreateMenus()
  {
    try
    {
      UIHelper = UI::WidgetHelper::Create();
      UILayer = UI::UILayer::Create(UIHelper);
      UIHelper->AddUILayer(UILayer);      
    }
    catch (std::exception &err)
    {
      std::cerr << "Fuck: " << err.what() << std::endl;
    }
  }

  void Editor::CreateGUIMenus()
  {
    UIThemePtr = std::make_shared<tgui::Theme>("./SFEngine/Source/CoreFiles/UIThemes/UIDark.txt");
    tgui::MenuBar::Ptr MenuBar = UIThemePtr->load("MenuBar");
    MenuBar->addMenu("file");
    MenuBar->addMenuItem("file", "new project");
    MenuBar->addMenuItem("file", "load project");
    MenuBar->addMenuItem("file", "save project");
    MenuBar->addMenuItem("file", "exit");
    MenuBar->connect("MenuItemClicked ", [this](std::vector<sf::String> item) {this->MenuBarItemSelected(item); });
    MenuBar->addMenu("edit");
    MenuBar->addMenuItem("edit", "settings");
    MenuBar->addMenuItem("edit", "tiles");
    MenuBar->addMenu("add");
    MenuBar->addMenuItem("add", "object");
    MenuBar->addMenuItem("add", "light");
    MenuBar->addMenuItem("add", "actor");
    MenuBar->setPosition({ 0,0 });
    MenuBar->setSize({ WindowSize.x }, { 20 });
    GUI->add(MenuBar);

    QuitMessageBox = UIThemePtr->load("MessageBox");
    tgui::Button::Ptr bttn = UIThemePtr->load("Button");
    bttn->setText("OK");
    QuitMessageBox->setText("Shutting down editor...");
    QuitMessageBox->setPosition({ 600, 700 });
    bttn->setPosition({ 15, 50 });
    QuitMessageBox->add(bttn, "ShutDownOK");


    EditTilesWindow = std::make_shared<TileSheetEditor>(GUI, UIThemePtr);
  }

}