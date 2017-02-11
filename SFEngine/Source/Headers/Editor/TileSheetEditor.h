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

    void Open();
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

    std::shared_ptr<FileBrowser> Browser;

#ifdef MessageBox //Seriiously, Windows? Is it really necessary to #define away MessageBox? USE A FUCKING NAMESPACE AND TYPEDEF!
#undef MessageBox
#endif
    tgui::ChildWindow::Ptr TileSheetNamePopup;
    tgui::EditBox::Ptr TileSheetNameEdit;
    tgui::Button::Ptr TileSheetOKButton;
    void TileSheetOKClicked();
    void CreateNewTileSheet(const std::string &ID, const std::string &texturepath);

    tgui::Button::Ptr NewTileSheetButton;
    //Child window to use
    tgui::ChildWindow::Ptr EditorWindow;
    tgui::Theme::Ptr Theme;
    //Data, followed by the UI element holding that data
    std::string SelectedTileSheet;
    tgui::ComboBox::Ptr TileSheetCombo;
    
    sf::RectangleShape TileSheetRect;
    sf::RectangleShape SelectedTileRect;

    std::shared_ptr<tgui::Gui> GUI;

    void SwitchTabs(tgui::Gui& gui, std::string selectedTab);
    //tabs
    tgui::Tab::Ptr TilesTab; tgui::Panel::Ptr TilesPanel;
    tgui::Tab::Ptr PhysicsTab; tgui::Panel::Ptr PhysicsPanel;
    tgui::Tab::Ptr LayersTab; tgui::Panel::Ptr LayersPanel;
    tgui::Tab::Ptr EtcTab; tgui::Panel::Ptr EtcPanel;

    //Tiles tab
    tgui::Canvas::Ptr TilesCanvas;
    tgui::Canvas::Ptr SelectedtileCanvas;
    tgui::ListBox::Ptr TilesList;
    tgui::Button::Ptr AddTileButton;
    tgui::Button::Ptr EditTileButton;
    tgui::Button::Ptr DeleteTimeButton;
    tgui::EditBox::Ptr FrameLeftEdit;
    tgui::EditBox::Ptr FrameTopEdit;
    tgui::EditBox::Ptr FrameWidthEdit;
    tgui::EditBox::Ptr FrameHeightEdit;
    tgui::EditBox::Ptr FrameNameEdit;
    tgui::Button::Ptr SaveTileButton;

    std::map<std::string, std::shared_ptr<TileSheet>> TileSheets;
  };

} 

#endif
