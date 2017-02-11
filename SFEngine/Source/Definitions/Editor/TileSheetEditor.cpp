#include "..\..\Headers\Editor\TileSheetEditor.h"
#undef _WINUSER_

namespace Engine
{
  TileSheetEditor::TileSheetEditor(std::shared_ptr<tgui::Gui> Gui, tgui::Theme::Ptr ThemePtr)
  {
    GUI = Gui;
    Theme = ThemePtr;
    //Width is 600
    EditorWindow = ThemePtr->load("ChildWindow");
    float xDiff = WindowSize.x - 600.f;
    float yDiff = WindowSize.y - 800.f;

    EditorWindow->setPosition({ xDiff / 2.f, yDiff / 2.f });
    EditorWindow->setSize({ 600, 800 });

    NewTileSheetButton = Theme->load("Button");
    NewTileSheetButton->setText("new tile sheet");
    NewTileSheetButton->setSize({ 100, 20 });
    NewTileSheetButton->setPosition({ 470, 20 });
    NewTileSheetButton->connect("clicked", [this]() { this->BrowseForNewSheetTexture(); });
    EditorWindow->add(NewTileSheetButton);

    SelectedTileSheet = "";
    TileSheetCombo = ThemePtr->load("ComboBox");
    TileSheetCombo->setPosition({ 150, 20 });
    TileSheetCombo->setSize({ 300, 20 });
    TileSheetCombo->setTextSize(14);
    TileSheetCombo->connect("ItemSelected", [this](std::string item) {this->ChangeSelectedTileSheet(item); });
    tgui::Label::Ptr tscmb = ThemePtr->load("ToolTip");
    tscmb->setText("select from loaded tile sheets...");
    tscmb->setTextSize(8);

    tgui::Label::Ptr label = ThemePtr->load("Label");
    label->setText("tile sheet");
    label->setPosition({ 15, 15 });
    EditorWindow->add(label);
    EditorWindow->add(TileSheetCombo);

    TilesTab = ThemePtr->load("Tab");
    TilesTab->setSize({ 60, 60 });
    TilesTab->setPosition({ 0, 200 });
    TilesTab->add("tiles");
    TilesTab->add("physics");
    TilesTab->add("layers");
    TilesTab->add("etc");

    //Build the tiles tab
    TilesPanel = ThemePtr->load("Panel");
    TilesPanel->setPosition({ 0, 240 });
    TilesPanel->setSize({ 600, 540 });
    TilesPanel->setFont(Gui->getFont());

    TilesCanvas = std::make_shared<tgui::Canvas>();
    TilesCanvas->setPosition({ 10, 10 });
    TilesCanvas->setSize({ 300, 300 });
    TilesPanel->add(TilesCanvas);

    SelectedtileCanvas = std::make_shared<tgui::Canvas>();
    SelectedtileCanvas->setPosition({ 360, 300 });
    SelectedtileCanvas->setSize({ 100, 100 });
    TilesPanel->add(SelectedtileCanvas);

    TilesList = ThemePtr->load("ListBox");
    TilesList->setPosition({ 360, 90 });
    TilesList->setSize({ 150, 200 });
    TilesList->connect("ItemSelected", [this](std::string str)->void {this->TilesListItemSelected(str); });
    TilesPanel->add(TilesList);

    AddTileButton = ThemePtr->load("Button");
    AddTileButton->setText("add tile");
    AddTileButton->setPosition({ 10, 320 });
    AddTileButton->setSize({ 80, 20 });
    TilesPanel->add(AddTileButton);
    AddTileButton->connect("clicked", [this]() {this->AddTileButtonPressed(); });

    EditTileButton = ThemePtr->load("Button");
    EditTileButton->setText("edit tile");
    EditTileButton->setPosition({ 100, 320 });
    EditTileButton->setSize({ 80, 20 });
    TilesPanel->add(EditTileButton);
    EditTileButton->connect("clicked", [this]() {this->EditTileButtonPressed(); });

    DeleteTimeButton = ThemePtr->load("Button");
    DeleteTimeButton->setText("delete tile");
    DeleteTimeButton->setPosition({ 200, 320 });
    DeleteTimeButton->setSize({ 80, 20 });
    TilesPanel->add(DeleteTimeButton);
    DeleteTimeButton->connect("clicked", [this]() {this->DeleteTileButtonPressed(); });

    FrameLeftEdit = ThemePtr->load("EditBox");
    FrameLeftEdit->setDefaultText("left");
    FrameLeftEdit->setInputValidator(tgui::EditBox::Validator::Int);
    FrameLeftEdit->setMaximumCharacters(10);
    FrameLeftEdit->setTextSize(12);
    FrameLeftEdit->setPosition({ 10, 360 });
    FrameLeftEdit->setSize({ 100, 20 });
    FrameLeftEdit->disable();
    TilesPanel->add(FrameLeftEdit);

    tgui::Label::Ptr frledittooltip = ThemePtr->load("ToolTip");
    frledittooltip->setText("edit left of tile");
    FrameLeftEdit->setToolTip(frledittooltip);

    FrameTopEdit = ThemePtr->load("EditBox");
    FrameTopEdit->setDefaultText("top");
    FrameTopEdit->setInputValidator(tgui::EditBox::Validator::Int);
    FrameTopEdit->setMaximumCharacters(10);
    FrameTopEdit->setTextSize(12);
    FrameTopEdit->setPosition({ 120, 360 });
    FrameTopEdit->setSize({ 100, 20 });
    FrameTopEdit->disable();
    TilesPanel->add(FrameTopEdit);

    tgui::Label::Ptr frtedittooltip = ThemePtr->load("ToolTip");
    frtedittooltip->setText("edit top of tile");
    FrameTopEdit->setToolTip(frtedittooltip);

    FrameWidthEdit = ThemePtr->load("EditBox");
    FrameWidthEdit->setDefaultText("width");
    FrameWidthEdit->setInputValidator(tgui::EditBox::Validator::Int);
    FrameWidthEdit->setMaximumCharacters(10);
    FrameWidthEdit->setTextSize(12);
    FrameWidthEdit->setPosition({ 10, 390 });
    FrameWidthEdit->setSize({ 100, 20 });
    FrameWidthEdit->disable();
    TilesPanel->add(FrameWidthEdit);

    tgui::Label::Ptr frwedittooltip = ThemePtr->load("ToolTip");
    frwedittooltip->setText("edit top of tile");
    FrameWidthEdit->setToolTip(frwedittooltip);

    FrameHeightEdit = ThemePtr->load("EditBox");
    FrameHeightEdit->setDefaultText("height");
    FrameHeightEdit->setInputValidator(tgui::EditBox::Validator::Int);
    FrameHeightEdit->setMaximumCharacters(10);
    FrameHeightEdit->setTextSize(12);
    FrameHeightEdit->setPosition({ 120, 390 });
    FrameHeightEdit->setSize({ 100, 20 });
    FrameHeightEdit->disable();
    TilesPanel->add(FrameHeightEdit);

    FrameNameEdit = Theme->load("EditBox");
    FrameNameEdit->setDefaultText("name");
    FrameNameEdit->setPosition({ 10, 430 });
    FrameNameEdit->setSize({ 300, 20 });
    FrameNameEdit->disable();
    TilesPanel->add(FrameNameEdit);

    SaveTileButton = ThemePtr->load("Button");
    SaveTileButton->setText("save");
    SaveTileButton->setPosition({ 330, 430 });
    SaveTileButton->setSize({ 100, 20 });
    SaveTileButton->disable();
    TilesPanel->add(SaveTileButton);
    SaveTileButton->connect("clicked", [this]() {this->SaveTileButtonPressed(); });

    tgui::Label::Ptr frhedittooltip = ThemePtr->load("ToolTip");
    frhedittooltip->setText("edit top of tile");
    FrameWidthEdit->setToolTip(frhedittooltip);

    TilesPanel->add(TilesCanvas);

    EditorWindow->add(TilesPanel);
    TilesPanel->show();
    //PhysicsPanel->hide();
    //LayersPanel->hide();
    //EtcPanel->hide();

    EditorWindow->add(TilesTab);
    EditorWindow->connect("closed", [this]() {this->Close(); }); 
  }

  void TileSheetEditor::Open()
  {
    GUI->add(EditorWindow, "TileSheetEditorWindow");
    EditorWindow->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(150));
  }

  void TileSheetEditor::Close()
  {
    GUI->remove(EditorWindow);
  }

  void TileSheetEditor::LoadTileSheets(std::map<std::string, std::shared_ptr<TileSheet>> Sheets)
  {
    TileSheets = Sheets;
  }

  void TileSheetEditor::AddTileSheet(const std::string & ID, std::shared_ptr<TileSheet> Sheet)
  {
    TileSheetCombo->addItem(ID);
    TileSheets[ID] = Sheet;
  }

  std::string TileSheetEditor::GetSelectedTileSheet()
  {
    return std::string();
  }

  std::string TileSheetEditor::GetSelectedTile()
  {
    return std::string();
  }

  std::shared_ptr<TileSheet> TileSheetEditor::GetTileSheet()
  {
    return std::shared_ptr<TileSheet>();
  }

  sf::IntRect TileSheetEditor::GetTileRect()
  {
    return sf::IntRect();
  }
  void TileSheetEditor::ChangeSelectedTileSheet(const std::string & ID)
  {
    //Get all of the frames from the sheet
    auto it = TileSheets.find(ID);
    if (it != TileSheets.end()) {
      TilesList->removeAllItems();
      TileSheetRect.setTexture(it->second->Sheet.get());
      TileSheetRect.setSize({ 300, 300 });

      TilesCanvas->draw(TileSheetRect);
      for (auto & id : it->second->Tiles) {
        TilesList->addItem(id.first);        
      }
      SelectedtileCanvas->clear();

      AddTileButton->enable();
      SelectedTileSheet = ID;
    }
    else {
      MessageAlert("Selected tile sheet \"" + ID + "\" does not exist");
    }
  }
  void TileSheetEditor::AddTileButtonPressed()
  {
    //Enable the inputs
    FrameLeftEdit->enable();
    FrameLeftEdit->setDefaultText("left");

    FrameTopEdit->enable();
    FrameTopEdit->setDefaultText("top");

    FrameWidthEdit->enable();
    FrameWidthEdit->setDefaultText("width");

    FrameHeightEdit->enable();
    FrameHeightEdit->setDefaultText("height");

    FrameNameEdit->enable();
    FrameNameEdit->setDefaultText("name");

    SaveTileButton->enable();

    //disable the other interactive items
  }

  void TileSheetEditor::EditTileButtonPressed()
  {
    //Enable the inputs
    FrameLeftEdit->enable();
    FrameLeftEdit->setDefaultText("left");

    FrameTopEdit->enable();
    FrameTopEdit->setDefaultText("top");

    FrameWidthEdit->enable();
    FrameWidthEdit->setDefaultText("width");

    FrameHeightEdit->enable();
    FrameHeightEdit->setDefaultText("height");

    //disable the other interactive items
    TilesList->disable();
    AddTileButton->disable();
    DeleteTimeButton->disable();
    EditTileButton->disable();

    SaveTileButton->enable();
    SaveTileButton->connect("clicked", [this]() {this->SaveTileButtonPressed(); });
  }
  void TileSheetEditor::DeleteTileButtonPressed()
  {
  }
  void TileSheetEditor::CancelButtonPressed()
  {
    FrameLeftEdit->setText("");
    FrameLeftEdit->disable();

    FrameTopEdit->setText("");
    FrameTopEdit->disable();

    FrameWidthEdit->setText("");
    FrameWidthEdit->disable();

    FrameHeightEdit->setText("");
    FrameHeightEdit->disable();

    TilesList->enable();
  }
  void TileSheetEditor::SaveTileButtonPressed()
  {
    int Left = std::stoi(FrameLeftEdit->getText().toAnsiString());
    int Top = std::stoi(FrameTopEdit->getText().toAnsiString());
    int Width = std::stoi(FrameWidthEdit->getText().toAnsiString());
    int Height = std::stoi(FrameHeightEdit->getText().toAnsiString());

    std::string tilename = FrameNameEdit->getText();

    sf::VertexArray varr = sf::VertexArray(sf::Quads, 4);
    varr[0].texCoords = { __TO_FLOAT__(Left), __TO_FLOAT__(Top) };
    varr[1].texCoords = { __TO_FLOAT__(Left) + __TO_FLOAT__(Width), __TO_FLOAT__(Top) };
    varr[2].texCoords = { __TO_FLOAT__(Left) + __TO_FLOAT__(Width), __TO_FLOAT__(Top) + __TO_FLOAT__(Height) };
    varr[3].texCoords = { __TO_FLOAT__(Left), __TO_FLOAT__(Top) + __TO_FLOAT__(Height) };

    TileSheets[SelectedTileSheet]->Tiles[tilename] = varr;
    TilesList->addItem(tilename);

    AddTileFromInput();
  }
  void TileSheetEditor::TilesListItemSelected(std::string item)
  {
    SelectedtileCanvas->clear();

    SelectedTileRect.setSize({ 100,100 });
    SelectedTileRect.setTexture(TileSheets[SelectedTileSheet]->Sheet.get());
    auto varr = TileSheets[SelectedTileSheet]->Tiles[item];
    SelectedTileRect.setTextureRect({ __INT_FROM_FLOAT__(varr[0].texCoords.x), 
                                    __INT_FROM_FLOAT__(varr[0].texCoords.y), 
                                    __INT_FROM_FLOAT__(varr[1].texCoords.x - varr[0].texCoords.x), 
                                    __INT_FROM_FLOAT__(varr[2].texCoords.y - varr[1].texCoords.y) });
    SelectedtileCanvas->draw(SelectedTileRect);
  }
  void TileSheetEditor::AddTileFromInput()
  {

  }
  void TileSheetEditor::FileSelected(const std::string & file)
  {
    Browser->Close();
    
    TileSheetNamePopup = Theme->load("ChildWindow");
    TileSheetNamePopup->setSize({ 500, 200 });
    tgui::Label::Ptr text = Theme->load("Label");
    text->setText("enter name for tile sheet");
    text->setTextSize(20);
    text->setPosition({ 10, 10 });
    TileSheetNamePopup->add(text);

    TileSheetNameEdit = Theme->load("EditBox");
    TileSheetNameEdit->setPosition({ 50, 150 });
    TileSheetNameEdit->setSize({ 200, 30 });
    TileSheetNameEdit->setDefaultText("tile sheet name");

    TileSheetOKButton = Theme->load("Button");
    TileSheetOKButton->setPosition({ 300, 150 });
    TileSheetOKButton->setSize({ 100, 20 });
    TileSheetOKButton->setText("create");

    TileSheetNamePopup->add(TileSheetNameEdit);
    TileSheetNamePopup->add(TileSheetOKButton);

    TileSheetOKButton->connect("clicked", 
                               [this, str = file]() -> void
                               {
                                 auto __str = this->TileSheetNameEdit->getText();
                                 this->TileSheetNamePopup->hide();
                                 this->CreateNewTileSheet(__str, str);
                                 GUI->remove(this->TileSheetNamePopup);
                               });
    GUI->add(TileSheetNamePopup);
    GUI->focusWidget(TileSheetNamePopup);
    TileSheetNamePopup->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
  }

  void TileSheetEditor::BrowseForNewSheetTexture()
  {
    Browser = std::make_shared<FileBrowser>();
    Browser->Open(std::experimental::filesystem::v1::current_path(), [this](const std::string &str) {this->FileSelected(str); }, Theme);
  }
  void TileSheetEditor::TileSheetOKClicked()
  {
  }
  void TileSheetEditor::CreateNewTileSheet(const std::string & ID, const std::string & texturepath)
  {
    std::shared_ptr<TileSheet> Sheet = std::make_shared<TileSheet>();
    Sheet->Sheet = std::make_shared<sf::Texture>();
    if (!Sheet->Sheet->loadFromFile(texturepath)) {
      MessageAlert("Failed to load texture to create tile sheet. Path given : " + texturepath);
    }
    else {
      AddTileSheet(ID, Sheet);
    }
  }
  void TileSheetEditor::SwitchTabs(tgui::Gui & gui, std::string selectedTab)
  {
  }
}
