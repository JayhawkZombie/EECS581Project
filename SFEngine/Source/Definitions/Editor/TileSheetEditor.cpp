#include "../../Headers/Editor/TileSheetEditor.h"

namespace Engine
{

  TileSheetEditor::TileSheetEditor(std::shared_ptr<tgui::Gui> Gui, tgui::Theme::Ptr ThemePtr)
  {
    Theme = ThemePtr;
  }

  void TileSheetEditor::Create()
  {
    EditorPanel = Theme->load("Panel");
    EditorPanel->setSize({ WindowSize.x - 300.f, WindowSize.y - 15.f });
    EditorPanel->setPosition({ 300.f, 15.f });

    float SPercWidth = (WindowSize.x - 300.f) * 0.70f;
    float xDiff = 0.f, yDiff = 0.f;

    xDiff = SPercWidth / 2.f;
    TilesDropDown = Theme->load("ComboBox");
    TilesDropDown->setSize({ SPercWidth, 25 });
    TilesDropDown->setPosition({ xDiff, 10.f });
    EditorPanel->add(TilesDropDown);

    NameInputLabel = Theme->load("Label");
    NameInputLabel->setText("Name:");
    float LabelWidth = NameInputLabel->getSize().x;
    NameInputLabel->setPosition({ 10.f, 50.f });
    EditorPanel->add(NameInputLabel);

    NameInput = Theme->load("EditBox");
    NameInput->setSize({ (WindowSize.x - 300.f) * 0.40f, 50.f });
    EditorPanel->add(NameInput);

    CloseButton = Theme->load("Button");
    CloseButton->setText("Close");
    CloseButton->setPosition({ 10.f, 10.f });
    EditorPanel->add(CloseButton);

    CloseButton->connect("clicked", [this]() {this->Close(); });
  }

  void TileSheetEditor::Open()
  {
  }

  void TileSheetEditor::Close()
  {
  }

  void TileSheetEditor::LoadTileSheets(std::map<std::string, std::shared_ptr<TileSheet>> Sheets)
  {
  }

  void TileSheetEditor::AddTileSheet(const std::string & ID, std::shared_ptr<TileSheet> Sheet)
  {
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

}