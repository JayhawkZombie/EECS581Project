#ifndef SFENGINE_EDITOR_ENTITY_CREATOR_H
#define SFENGINE_EDITOR_ENTITY_CREATOR_H

#include "../Level/Level.h"

namespace Engine
{

  class EntityCreator
  {
  public:
    EntityCreator(tgui::Theme::Ptr Theme);
    ~EntityCreator();

    bool IsPlacingObject() const;

    void TickUpdate(const double &delta);
    void Render(std::shared_ptr<sf::RenderTexture> Target);
    void Open();
    void Close();
    bool IsOpen() const;
    void SetTileSheet(std::shared_ptr<TileSheet> Sheet);
    void SpawnEntity(std::shared_ptr<LevelObject> object);
  protected:
    void TileSelected(std::string name);
    void TileDoubleClicked(std::string name);
    sf::RectangleShape rect;
    bool open = false;
    float CanvasViewSize = 64.f;
    tgui::ComboBox::Ptr TilesList;
    tgui::Canvas::Ptr TileCanvas;

    std::shared_ptr<LevelObject> PlacingObject = nullptr;
    tgui::Theme::Ptr UITheme;
    tgui::Panel::Ptr TilesPanel;
    std::shared_ptr<TileSheet> TileSheet; //For now, only allow editing with one sheet
    tgui::ChildWindow::Ptr CreatorWindow;
    tgui::Label::Ptr LevelLabel;
    tgui::Label::Ptr MousePosLabel;
    tgui::Label::Ptr GridCellLabel;
    tgui::ComboBox::Ptr ModeSelect;
    tgui::CheckBox::Ptr ShowGridCheck;
    tgui::CheckBox::Ptr SnapToGridCheck;
    //TODO: Add stuff for LevelObject spawning
  };

}

#endif
