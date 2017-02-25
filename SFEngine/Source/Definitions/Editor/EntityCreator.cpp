#include "../../Headers/Editor/EntityCreator.h"
#include "../../Headers/Engine/Editor.h"

namespace Engine
{



  EntityCreator::EntityCreator(tgui::Theme::Ptr Theme)
  {
    /*    tgui::ChildWindow::Ptr CreatorWindow;
    tgui::Label::Ptr LevelLabel;
    tgui::Label::Ptr MousePosLabel;
    tgui::Label::Ptr GridCellLabel;
    tgui::ComboBox::Ptr ModeSelect;
    tgui::CheckBox::Ptr ShowGridCheck;
    tgui::CheckBox::Ptr SnapToGridCheck;*/
    UITheme = Theme;
    CreatorWindow = Theme->load("ChildWindow");
    CreatorWindow->setSize({ 400, 600 });
    CreatorWindow->setPosition({ WindowSize.x - 500.f, 100 });
    CreatorWindow->setTitle("Entity Creator");
    CreatorWindow->connect("closed", [this]() {this->Close(); });

    LevelLabel = Theme->load("Label");
    LevelLabel->setText("Level: <in testing>");
    LevelLabel->setTextSize(12);
    LevelLabel->setPosition({ 10, 10 });
    LevelLabel->setSize({ 380, 20 });
    CreatorWindow->add(LevelLabel);

    PlaceTilesButton = Theme->load("Button");
    PlaceTilesButton->setPosition({ 280, 230 });
    PlaceTilesButton->setText("Place tiles");
    PlaceTilesButton->setSize({ 100, 20 });
    CreatorWindow->add(PlaceTilesButton);

    DoneButton = Theme->load("Button");
    DoneButton->setPosition({ 280, 260 });
    DoneButton->setText("Done");
    DoneButton->setSize({ 100, 20 });
    CreatorWindow->add(DoneButton);

    MousePosLabel = Theme->load("Label");
    MousePosLabel->setText("Mouse Position:");
    MousePosLabel->setTextSize(12);
    MousePosLabel->setPosition({ 10, 40 });
    MousePosLabel->setSize({ 380, 20 });
    CreatorWindow->add(MousePosLabel);

    GridCellLabel = Theme->load("Label");
    GridCellLabel->setText("Grid Cell:");
    GridCellLabel->setTextSize(12);
    GridCellLabel->setPosition({ 10, 70 });
    GridCellLabel->setSize({ 380, 20 });
    CreatorWindow->add(GridCellLabel);

    ModeSelect = Theme->load("ComboBox");
    ModeSelect->setSize({ 180, 20 });
    ModeSelect->addItem("Tile Edit");
    ModeSelect->addItem("Object Edit");
    ModeSelect->setPosition({ 10, 100 });
    ModeSelect->setSelectedItem("Tile Edit");
    CreatorWindow->add(ModeSelect);

    ShowGridCheck = Theme->load("CheckBox");
    ShowGridCheck->check();
    ShowGridCheck->setText("Show grid");
    ShowGridCheck->setPosition({ 10, 130 });
    CreatorWindow->add(ShowGridCheck);

    SnapToGridCheck = Theme->load("CheckBox");
    SnapToGridCheck->check();
    SnapToGridCheck->setText("Snap to grid");
    SnapToGridCheck->setPosition({ 10, 160 });
    CreatorWindow->add(SnapToGridCheck);

    TilesList = Theme->load("ComboBox");
    TilesList->setPosition({ 10, 200 });
    TilesList->setSize({ 380, 20 });
    TilesList->setItemsToDisplay(10);
    tgui::Scrollbar::Ptr scrollbar = Theme->load("ScrollBar");
    scrollbar->setSize({ 15, 100 });
    scrollbar->setPosition({ 365, 0 });
    TilesList->setScrollbar(scrollbar);
    CreatorWindow->add(TilesList);
    TilesList->connect("ItemSelected", [this](std::string str) {this->TileSelected(str); });
    
    TileCanvas = std::make_shared<tgui::Canvas>();
    TileCanvas->setSize({ 200, 200 });
    TileCanvas->setPosition({ 100, 230 });
    CreatorWindow->add(TileCanvas);
    rect.setSize({ 200, 200 });
    TileCanvas->clear(sf::Color::Transparent);
    TileCanvas->draw(rect);

    GUI->add(CreatorWindow);
    CreatorWindow->hide();
  }

  EntityCreator::~EntityCreator()
  {
    
  }

  bool EntityCreator::IsPlacingObject() const
  {
    return (PlacingObject.get());
  }

  void EntityCreator::SetEditorPtr(Editor * editor)
  {
    CurrentEditor = editor;
  }

  void EntityCreator::TickUpdate(const double & delta)
  {
    if (PlacingObject)
      PlacingObject->SetPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*currentRenderWindow)));
  }

  void EntityCreator::Render(std::shared_ptr<sf::RenderTexture> Target)
  {
  }

  void EntityCreator::Open()
  {
    open = true;
    CreatorWindow->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
  }

  void EntityCreator::Close()
  {
    open = false;
    CreatorWindow->hideWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
  }

  bool EntityCreator::IsOpen() const
  {
    return (CreatorWindow && CreatorWindow->isVisible());
  }

  bool EntityCreator::InPlacement() const
  {
    return InPlacementMode;
  }

  void EntityCreator::SetTileSheet(std::shared_ptr<Engine::TileSheet> Sheet)
  {
    TileSheet = Sheet;

    if (!TileSheet)
      return;

    TilesList->removeAllItems();
    TileCanvas->clear();
    auto Tiles = TileSheet->GetLevelTiles();
    auto numTiles = Tiles.size();

    for (auto & tile : Tiles) {
      TilesList->addItem(tile.first);
    }
  }

  void EntityCreator::SpawnEntity(std::shared_ptr<LevelObject> object)
  {
    std::cerr << "Spawning entity!" << std::endl;
  }

  void EntityCreator::SetLevel(std::shared_ptr<Level> lvl)
  {
    LevelPtr = lvl;
  }

  void EntityCreator::TileSelected(std::string name)
  {
    auto tile = TileSheet->GetLevelTiles()[name];
    TileCanvas->clear(sf::Color::Transparent);
    rect.setTexture(TileSheet->GetTexture().get());
    rect.setSize({
      static_cast<float>(CanvasViewSize),
      static_cast<float>(CanvasViewSize * (tile->TextureRect.height / tile->TextureRect.width))
    });
    rect.setTextureRect(tile->TextureRect);
    TileCanvas->draw(rect);
  }

  void EntityCreator::TileDoubleClicked(std::string name)
  {
    std::cerr << "TO FINISH : IMPLEMENT SPAWNING" << std::endl;
  }

  void EntityCreator::PlaceTilesButtonClicked()
  {
    InPlacementMode = true;
    CurrentEditor->HidePanels();
  }

  void EntityCreator::DoneButtonClicked()
  {
    InPlacementMode = false;
    CurrentEditor->ShowPanels();
  }

}
