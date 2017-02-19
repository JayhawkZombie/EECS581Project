#include "../../Headers/Engine/Editor.h"

namespace Engine
{

  void Editor::CreateMenus()
  {
  }

  void Editor::CreateGUIMenus()
  {
    try
    {
      MenuBar = UIThemePtr->load("MenuBar");
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

      float hToFill = (WindowSize.y - MenuBar->getSize().y) / 7.f;
      float buttonPos = 0.f;
      unsigned int textSize = 18;

      SideTabPanel = UIThemePtr->load("Panel");
      SideTabPanel->setPosition({ 0, MenuBar->getSize().y });
      SideTabPanel->setSize({ 200.f, WindowSize.y - MenuBar->getSize().y });

      LevelTab = UIThemePtr->load("Button");
      LevelTab->setText("Level");
      LevelTab->connect("clicked", [this]() { this->SelectLevelTab(); });
      LevelTab->setSize({ 200.f, hToFill });
      LevelTab->setTextSize(textSize);
      LevelTab->setPosition({ 0, buttonPos }); buttonPos += hToFill;
      SideTabPanel->add(LevelTab);

      TilesTab = UIThemePtr->load("Button");
      TilesTab->setText("Tiles");
      TilesTab->connect("clicked", [this]() { this->SelectTilesTab(); });
      TilesTab->setSize({ 200.f, hToFill });
      TilesTab->setTextSize(textSize);
      TilesTab->setPosition({ 0, buttonPos }); buttonPos += hToFill;
      SideTabPanel->add(TilesTab);

      AnimationTab = UIThemePtr->load("Button");
      AnimationTab->setText("Animation");
      AnimationTab->connect("clicked", [this]() { this->SelectAnimationTab(); });
      AnimationTab->setSize({ 200.f, hToFill });
      AnimationTab->setTextSize(textSize);
      AnimationTab->setPosition({ 0, buttonPos }); buttonPos += hToFill;
      SideTabPanel->add(AnimationTab);

      GUITab = UIThemePtr->load("Button");
      GUITab->setText("GUI");
      GUITab->connect("clicked", [this]() { this->SelectGUITab(); });
      GUITab->setSize({ 200.f, hToFill });
      GUITab->setTextSize(textSize);
      GUITab->setPosition({ 0, buttonPos }); buttonPos += hToFill;
      SideTabPanel->add(GUITab);

      ActorsTab = UIThemePtr->load("Button");
      ActorsTab->setText("Actors");
      ActorsTab->connect("clicked", [this]() { this->SelectActorsTab(); });
      ActorsTab->setSize({ 200.f, hToFill });
      ActorsTab->setTextSize(textSize);
      ActorsTab->setPosition({ 0, buttonPos }); buttonPos += hToFill;
      SideTabPanel->add(ActorsTab);

      MusicTab = UIThemePtr->load("Button");
      MusicTab->setText("Music");
      MusicTab->connect("clicked", [this]() { this->SelectMusicTab(); });
      MusicTab->setSize({ 200.f, hToFill });
      MusicTab->setTextSize(textSize);
      MusicTab->setPosition({ 0, buttonPos }); buttonPos += hToFill;
      SideTabPanel->add(MusicTab);

      HideTabPanel = UIThemePtr->load("Button");
      HideTabPanel->connect("clicked", [this]() {this->HideSideTabPanel(); });
      HideTabPanel->setSize({ 200.f, hToFill });
      HideTabPanel->setTextSize(textSize);
      HideTabPanel->setText("Hide");
      HideTabPanel->setPosition({ 0, buttonPos });
      SideTabPanel->add(HideTabPanel);

      GUI->add(SideTabPanel);

      MenuBar->moveToFront();

      float panelPosX = WindowSize.x - 300.f;
      float panelPosY = MenuBar->getSize().y;

      float panelSizeX = WindowSize.x - 300.f;
      float panelSizeY = WindowSize.y - MenuBar->getSize().y;

      LevelPanel = UIThemePtr->load("Panel");
      LevelPanel->setPosition({ panelPosX, panelPosY });
      LevelPanel->setSize({ panelSizeX, panelSizeY });
      LevelPanel->hide();
      LevelPanelExpandButton = UIThemePtr->load("Button");
      LevelPanelLabel = UIThemePtr->load("Label");
      LevelPanelLabel->setText("Level Panel");
      LevelPanelLabel->setTextSize(18);
      auto size = LevelPanelLabel->getSize();
      float xDiff = 300.f - size.x;
      LevelPanelLabel->setPosition({ xDiff / 2.f, 10.f });
      LevelPanel->add(LevelPanelLabel);
      LevelPanelExpandButton->connect("clicked", [this]() -> void { this->ExpandLevelPanel(); });
      LevelPanelExpandButton->setPosition({ 0, 0 });
      LevelPanelExpandButton->setSize({ 20, 20 });
      LevelPanel->add(LevelPanelExpandButton);
      GUI->add(LevelPanel);

      TilesPanel = UIThemePtr->load("Panel");
      TilesPanel->setPosition({ panelPosX, panelPosY });
      TilesPanel->setSize({ panelSizeX, panelSizeY });
      TilesPanel->hide();
      TilesPanelExpandButton = UIThemePtr->load("Button");
      TilesPanelLabel = UIThemePtr->load("Label");
      TilesPanelLabel->setText("Tiles Panel");
      TilesPanelLabel->setTextSize(18);
      size = TilesPanelLabel->getSize();
      xDiff = 300.f - size.x;
      TilesPanelLabel->setPosition({ xDiff / 2.f, 10.f });
      TilesPanel->add(TilesPanelLabel);
      TilesPanelExpandButton->connect("clicked", [this]() -> void { this->ExpandTilesPanel(); });
      TilesPanelExpandButton->setPosition({ 0, 0 });
      TilesPanelExpandButton->setSize({ 20, 20 });
      TilesPanel->add(TilesPanelExpandButton);

      TilesPanelListLabel = UIThemePtr->load("Label");
      TilesPanelListLabel->setText("Sheets:");
      xDiff = 300.f - TilesPanelListLabel->getSize().x;
      TilesPanelListLabel->setPosition({ xDiff / 2.f, 100.f });
      TilesPanelListBox = UIThemePtr->load("ListBox");
      TilesPanelListBox->setSize({ 200.f, 400.f });
      TilesPanelListBox->setPosition({ 50.f, 150.f });
      TilesPanelListBox->connect("doubleclicked", [this](std::string str) -> void { this->TileSheetSelected(str); });
      TilesPanelTilesLabel = UIThemePtr->load("Label");
      TilesPanelTilesLabel->setText("Tiles:");
      xDiff = 300.f - TilesPanelTilesLabel->getSize().x;
      TilesPanelTilesLabel->setPosition({ xDiff / 2.f, 650.f });
      TilesPanelTilesList = UIThemePtr->load("ListBox");
      TilesPanelTilesList->setSize({ 200.f, 200.f });
      TilesPanelTilesList->setPosition({ 50.f, 700.f });

      TilesPanel->add(TilesPanelListLabel);
      TilesPanel->add(TilesPanelListBox);
      TilesPanel->add(TilesPanelTilesList);
      TilesPanel->add(TilesPanelTilesList);
      GUI->add(TilesPanel);

      AnimationPanel = UIThemePtr->load("Panel");
      AnimationPanel->setPosition({ 0, 0 });
      AnimationPanel->setSize({ panelSizeX, panelSizeY });
      AnimationPanel->hide();
      AnimationPanelLabel = UIThemePtr->load("Label");
      AnimationPanelLabel->setText("Animation Panel");
      AnimationPanelLabel->setTextSize(18);
      size = AnimationPanelLabel->getSize();
      xDiff = 300.f - size.x;
      AnimationPanelLabel->setPosition({ xDiff / 2.f, 10.f });
      AnimationPanel->add(AnimationPanelLabel);
      AnimationPanelExpandButton = UIThemePtr->load("Button");
      AnimationPanelExpandButton->connect("clicked", [this]() -> void { this->ExpandAnimationPanel(); });
      //AnimationPanelExpandButton->getRenderer()->setNormalTexture(BackArrowMediumTexture);
      AnimationPanelExpandButton->setPosition({ 0, 0 });
      AnimationPanelExpandButton->setSize({ 20, 20 });
      AnimationPanel->add(AnimationPanelExpandButton);
      AnimationPanelAnimationList = UIThemePtr->load("ListBox");
      AnimationPanelAnimationList->setSize({ 200, 250 });
      AnimationPanelAnimationList->setPosition({ 50, 150 });
      for (auto & anim : Animations) {
        AnimationPanelAnimationList->addItem(anim.first);
      }
      AnimationPanelAnimationList->connect("doubleclicked",
                                           [this](std::string name) -> void
      {
        auto it = this->Animations.find(name);
        if (it != this->Animations.end())
          this->AnimationPanelAnimationViewer->Open(it->second);
      });
      AnimationPanel->add(AnimationPanelAnimationList);
      GUI->add(AnimationPanel);

      GUIPanel = UIThemePtr->load("Panel");
      GUIPanel->setPosition({ 0, 0 });
      GUIPanel->setSize({ panelSizeX, panelSizeY });
      GUIPanel->hide();
      GUIPanelLabel = UIThemePtr->load("Label");
      GUIPanelLabel->setText("GUI Panel");
      GUIPanelLabel->setTextSize(18);
      size = GUIPanelLabel->getSize();
      xDiff = 300.f - size.x;
      GUIPanelLabel->setPosition({ xDiff / 2.f, 10.f });
      GUIPanel->add(GUIPanelLabel);
      GUIPanelExpandButton = UIThemePtr->load("Button");
      GUIPanelExpandButton->connect("clicked", [this]() -> void { this->ExpandGUIPanel(); });
      //GUIPanelExpandButton->getRenderer()->setNormalTexture(BackArrowMediumTexture);
      GUIPanelExpandButton->setPosition({ 0, 0 });
      GUIPanelExpandButton->setSize({ 20, 20 });
      GUIPanel->add(GUIPanelExpandButton);
      GUI->add(GUIPanel);

      ActorsPanel = UIThemePtr->load("Panel");
      ActorsPanel->setPosition({ 0, 0 });
      ActorsPanel->setSize({ panelSizeX, panelSizeY });
      ActorsPanel->hide();
      ActorsPanelLabel = UIThemePtr->load("Label");
      ActorsPanelLabel->setText("Actors Panel");
      ActorsPanelLabel->setTextSize(18);
      size = ActorsPanelLabel->getSize();
      xDiff = 300.f - size.x;
      ActorsPanelLabel->setPosition({ xDiff / 2.f, 10.f });
      ActorsPanel->add(ActorsPanelLabel);
      ActorsPanelExpandButton = UIThemePtr->load("Button");
      ActorsPanelExpandButton->connect("clicked", [this]() -> void { this->ExpandActorsPanel(); });
      //ActorsPanelExpandButton->getRenderer()->setNormalTexture(BackArrowMediumTexture);
      ActorsPanelExpandButton->setPosition({ 0, 0 });
      ActorsPanelExpandButton->setSize({ 20, 20 });
      ActorsPanel->add(ActorsPanelExpandButton);
      GUI->add(ActorsPanel);

      MusicPanel = UIThemePtr->load("Panel");
      MusicPanel->setPosition({ 0, 0 });
      MusicPanel->setSize({ panelSizeX, panelSizeY });
      MusicPanel->hide();
      MusicPanelLabel = UIThemePtr->load("Label");
      MusicPanelLabel->setText("Music Panel");
      MusicPanelLabel->setTextSize(18);
      size = MusicPanelLabel->getSize();
      xDiff = 300.f - size.x;
      MusicPanelLabel->setPosition({ xDiff / 2.f, 10.f });
      MusicPanel->add(MusicPanelLabel);
      MusicPanelExpandButton = UIThemePtr->load("Button");
      MusicPanelExpandButton->connect("clicked", [this]() -> void { this->ExpandMusicPanel(); });
      //MusicPanelExpandButton->getRenderer()->setNormalTexture(BackArrowMediumTexture);
      MusicPanelExpandButton->setPosition({ 0, 0 });
      MusicPanelExpandButton->setSize({ 20, 20 });
      MusicPanel->add(MusicPanelExpandButton);
      GUI->add(MusicPanel);

      EditTilesWindow = std::make_shared<TileSheetEditor>(GUI, UIThemePtr);
      AnimationPanelAnimationViewer = std::make_shared<AnimationViewer>(UIThemePtr);
      Done = true;
    }
    catch (EngineRuntimeError &err)
    {
      std::cerr << "Exception caught while creating menus" << std::endl;
    }
  }

}