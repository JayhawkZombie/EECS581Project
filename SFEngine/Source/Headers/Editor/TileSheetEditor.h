#ifndef SFENGINE_EDITOR_TILESHEET_EDITOR_H
#define SFENGINE_EDITOR_TILESHEET_EDITOR_H

#include <TGUI\TGUI.hpp>
#include "FileBrowser.h"
#include "../Level/Level.h"

namespace Engine
{

  class TileSheetEditor
  {

  public:
    TileSheetEditor(std::shared_ptr<tgui::Gui> Gui, tgui::Theme::Ptr ThemePtr);
    ~TileSheetEditor() = default;

    void Create();

    void Open();
    void Open(std::shared_ptr<TileSheet> Sheet);
    void Close();

    void LoadTileSheets(std::map<std::string, std::shared_ptr<TileSheet>> Sheets);
    void AddTileSheet(const std::string &ID, std::shared_ptr<TileSheet> Sheet);

    std::string GetSelectedTileSheet();
    std::string GetSelectedTile();

    std::shared_ptr<TileSheet> GetTileSheet();
    sf::IntRect GetTileRect();

  protected:
    void ChangeSelectedTileSheet(const std::string &ID);

    void AddTileButtonPressed();
    void EditTileButtonPressed();
    void DeleteTileButtonPressed();
    void CancelButtonPressed();
    void SaveTileButtonPressed();
    void TilesListItemSelected(std::string item);
    void AddTileFromInput();

    void FileSelected(const std::string &file);
    void BrowseForNewSheetTexture();

    tgui::Button::Ptr CloseButton;

    tgui::Theme::Ptr Theme;
    tgui::Panel::Ptr EditorPanel;
    tgui::Label::Ptr PanelLabel;

    tgui::ComboBox::Ptr TileSheetDropDown;
    tgui::Button::Ptr AddSheetButton;
    tgui::Button::Ptr RemoveSheetButton;

    tgui::Label::Ptr NameInputLabel;
    tgui::EditBox::Ptr NameInput;

    tgui::Canvas::Ptr SheetPreview;

    tgui::ComboBox::Ptr TilesDropDown;
    tgui::Label::Ptr TileNameEditLabel;
    tgui::EditBox TileNameEdit;
    tgui::SpinButton::Ptr TilePosXSpinner;
    tgui::SpinButton::Ptr TilePosYSpinner;
    tgui::SpinButton::Ptr TileSizeXSpinner;
    tgui::SpinButton::Ptr TileSizeYSpinner;

    tgui::Canvas::Ptr TilePreview;
    tgui::CheckBox::Ptr IsAnimated;
    tgui::CheckBox::Ptr HasCollision;

    tgui::ComboBox::Ptr TileScriptsDropDown;
  };

} 

#endif
