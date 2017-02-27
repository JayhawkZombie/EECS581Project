#ifndef SFENGINE_EDITOR_H
#define SFENGINE_EDITOR_H

#include "../BasicIncludes.h"
#include "../Actor/Player.h"
#include "../../../ThirdParty/PhysicsEngine.h"
#include "../UI/Events/Events.h"
#include "../Editor/EditorProject.h"
#include "../UI/UIIconSheet.h"
#include "../Editor/CreateNewProject.h"
#include "../Editor/EntityCreator.h"

namespace Engine
{

  enum class EditingMode : std::uint32_t
  {
    Tile,
    Actor,
    Light,
    Object,
    Animation,
    Particle,
    None
  };

  enum class CurrentMode : std::uint32_t
  {
    None,
    AddingObject,
    EditingObject,
    MovingObject
  };

  struct TileInfo {
    sf::Texture TileSheet;
    std::vector<sf::IntRect> TileSheetFrames;

    std::size_t SheetIndex = 0;

    sf::Sprite TileSheetSprite;
    sf::Sprite TileSheetPreviewSprite;
    sf::Sprite TilePlacingSprite;

    sf::Vector2f Position;
    sf::Vector2f Size;
    sf::Vector2f Scale;

    sf::RectangleShape TileSheetOutline;
    std::vector<sf::VertexArray> TileFrameOutlines;
    sf::Text TileText;
  };

  static sf::Vector2f EditorPreviewPosition = sf::Vector2f(0, 40);
  static sf::Vector2u EditorPreviewSize = sf::Vector2u(800, 600);
  static sf::Vector2i TileSheetPreviewSize = sf::Vector2i(400, 400);
  static sf::Vector2f TileSheetPreviewPosition = sf::Vector2f(810, 40);

  static std::vector<sf::IntRect> TileFrames = {
    { 0, 756, 86, 87 },
    { 0, 240, 128, 128 },
    { 0, 369, 128, 128 },
    { 129, 240, 128, 128 },
    { 287, 166, 128, 128 },
    { 287, 0, 182, 90 },
    { 258, 475, 100, 64 },
    { 129, 498, 106, 106 },
    { 287, 91, 132, 74 },
    { 129, 605, 91, 93 },
    { 258, 424, 102, 50 },
    { 129, 369, 128, 128 },
    { 258, 295, 128, 128 },
    { 470, 0, 128, 128 },
    { 416, 166, 128, 128 },
    { 599, 0, 128, 128 },
    { 387, 295, 128, 128 },
    { 545, 129, 128, 128 },
    { 728, 0, 128, 128 },
    { 545, 258, 128, 128 },
    { 674, 129, 128, 128 },
    { 857, 0, 128, 128 },
    { 674, 258, 128, 128 },
    { 803, 129, 128, 128 },
    { 803, 258, 128, 128 },
    { 0, 498, 128, 128 },
    { 0, 627, 128, 128 },
    { 361, 424, 54, 55 },
    { 236, 540, 53, 76 },
    { 0, 0, 286, 239 }
  };

  class AnimationViewer;
  class ObjectViewer;
  class TileSheetEditor;

  class Editor
  {
  public:
    Editor();
    ~Editor();

    void TickUpdate(const double &delta);
    void Render(std::shared_ptr<sf::RenderTexture> Texture);

    void PreLoopSetup();

    void HandleMousePressed(const InputEvent &Event);
    void HandleMouseReleased(const InputEvent &Event);
    void HandleMouseMoved(const InputEvent &Event);
    void HandleMouseScrolled(const InputEvent &Event);
    void HandleKeyPressed(const InputEvent &Event);
    void HandleKeyReleased(const InputEvent &Event);
    void HandleTextEntered(const InputEvent &Event);

    void CreateMenus();
    void CreateGUIMenus();

    void LoadProject(const std::string &ProjectPath);
    void HidePanels();
    void ShowPanels();

    void HandleWindowResized(const sf::Vector2u &NewWindowSize);
    void BindEditorMethods(chaiscript::ModulePtr mptr);
  protected:
    void MenuBarItemSelected(std::vector<sf::String> vec);
    void ShutDownEditor();
    void OpenTilesheetViewer();
    void OpenProjectCreator();

    void SelectLevelTab();
    void ExpandLevelPanel();
    void ShrinkLevelPanel();

    void SelectTilesTab();
    void ExpandTilesPanel();
    void ShrinkTilesPanel();

    void SelectAnimationTab();
    void ExpandAnimationPanel();
    void ShrinkAnimationPanel();

    void SelectGUITab();
    void ExpandGUIPanel();
    void ShrinkGUIPanel();
    
    void SelectActorsTab();
    void ExpandActorsPanel();
    void ShrinkActorsPanel();

    void SelectMusicTab();
    void ExpandMusicPanel();
    void ShrinkMusicPanel();

    void HideSideTabPanel();

    std::shared_ptr<chaiscript::ChaiScript> EditorScriptEngine;

    Json::Value ProjectJson;
    std::string PROJECT_PATH = { "" };
    void LoadAssets();
    void LoadSheets();
    void LoadAnimations();
    void LoadAnimation(const Json::Value &anim);
    void LoadSheet(const Json::Value &sheet);
    void LoadObjects();
    void LoadScripts(chaiscript::ModulePtr ptr);
    void PopulateGUI();

    std::map<std::string, std::shared_ptr<sf::Texture>> Textures;
    std::map<std::string, std::shared_ptr<TileSheet>> TIleSheets;
    std::map<std::string, std::shared_ptr<Animation>> Animations;

    tgui::MenuBar::Ptr MenuBar;

    std::function<void(float)> FtnPtr;

    tgui::ProgressBar::Ptr CreationProgress;
    bool Done = false;
    bool GUIPopulated = false;

    std::shared_ptr<EntityCreator> Creator;

    //TGUI elements
    tgui::Font TestTGUIFont;
    tgui::Theme::Ptr UIThemePtr;
    tgui::Panel::Ptr SideTabPanel;
    tgui::Button::Ptr LevelTab;
    tgui::Button::Ptr TilesTab;
    tgui::Button::Ptr AnimationTab;
    tgui::Button::Ptr GUITab;
    tgui::Button::Ptr ActorsTab;
    tgui::Button::Ptr MusicTab;
    tgui::Button::Ptr HideTabPanel;

    //wtf, TGUI
    tgui::Texture IconsTexture;
    //one texture for each icon? Whhhyyyyyyyyyyy?
    tgui::Texture BackArrowMediumTexture;
    tgui::Texture ForArrorMediumTexture;

    tgui::Panel::Ptr LevelPanel;
    tgui::Label::Ptr LevelPanelLabel;
    tgui::SpinButton::Ptr LevelPanelLayerSpinner;
    tgui::Button::Ptr LevelPanelTilesButton;
    tgui::Button::Ptr LevelPanelObjectsButton;
    tgui::Button::Ptr LevelPanelActorsButton;
    tgui::Button::Ptr LevelPanelMusicButton;
    tgui::Button::Ptr LevelPanelExpandButton;

    tgui::Panel::Ptr TilesPanel;
    tgui::Label::Ptr TilesPanelLabel;
    tgui::Button::Ptr TilesPanelExpandButton;
    tgui::Label::Ptr TilesPanelListLabel;
    tgui::ListBox::Ptr TilesPanelListBox;
    tgui::Button::Ptr TilesPanelAddButton;
    tgui::Button::Ptr TilesPanelEditButton;
    tgui::ListBox::Ptr TilesPanelTilesList;
    tgui::Label::Ptr TilesPanelTilesLabel;
    tgui::Button::Ptr TilesPanelClearButton;
    tgui::Canvas::Ptr TilesPanelTileCanvas;
    sf::RectangleShape TileSPanelTileCanvasRect;
    void TileSheetSelected(std::string sheet);
    void TileSelected(std::string tile);

    tgui::Panel::Ptr AnimationPanel;
    tgui::Label::Ptr AnimationPanelLabel;
    tgui::Button::Ptr AnimationPanelExpandButton;
    std::shared_ptr<AnimationViewer> AnimationPanelAnimationViewer;
    tgui::Button::Ptr ViewAnimationButton;
    tgui::ListBox::Ptr AnimationPanelAnimationList;

    tgui::Panel::Ptr GUIPanel;
    tgui::Label::Ptr GUIPanelLabel;
    tgui::Button::Ptr GUIPanelExpandButton;

    tgui::Panel::Ptr ActorsPanel;
    tgui::Label::Ptr ActorsPanelLabel;
    tgui::Button::Ptr ActorsPanelExpandButton;

    tgui::Panel::Ptr MusicPanel;
    tgui::Label::Ptr MusicPanelLabel;
    tgui::Button::Ptr MusicPanelExpandButton;

    std::shared_ptr<TileSheetEditor> EditTilesWindow;
    std::shared_ptr<NewProjectCreator> ProjectCreator;

#ifdef MessageBox //Ugh windows, why do you do this crap?
#undef MessageBox
#endif
    tgui::MessageBox::Ptr QuitMessageBox;

    sf::RenderStates EditorRenderState;
    sf::RectangleShape EditorRect;

    //Test actor, just for testing
    GenericActor TestActor;
    std::shared_ptr<sf::Texture> TestActorSpriteSheet;
    std::shared_ptr<Animation> TestAnimation;

    std::shared_ptr<Level> EditLevel;

    //Used for sizing/spacing for different windows sizes
    float TopButtonHeight;
    float TopButtonWidth;

    bool IsUpdateLevelEnabled = true;

    //Icon sheet
    std::shared_ptr<sf::Texture> IconSheet;

    bool EnabledPhysics = true;

    std::shared_ptr<sf::Font> TextFont;
    std::shared_ptr<sf::Font> MenuFont;

    std::shared_ptr<sf::Texture> MenuTexture;

    //Methods for spawning in new object
    void SpawnBall(const sf::Vector2f &Position);
    void SpawnSquare(const sf::Vector2f &Position);
    void SpawnRect(const sf::Vector2f &Position);
    void SpawnTriangle(const sf::Vector2f &Position);
    void Spawn5Poly(const sf::Vector2f &Position);

    vec2d Gravity;
    std::vector<BaseMeshPtr> TestObjects;
    std::vector<SegmentPtr> Segments;

    //data for visualization
    sf::Font EditorFont;
    sf::Text EditorModeText;
    sf::Text PreviewGridInfoText;
    sf::Sprite UISprite;

    std::shared_ptr<sf::RenderTexture> UITexture;


    //the preview will be drawn to a render texture a forced to render in this 
    //rectangular area
    sf::RenderTexture PreviewTexture;
    sf::RectangleShape PreviewShape;
    sf::Sprite PreviewSprite;

    //the area in the screen that the live preview can be seen
    sf::View PreviewView;

    //Data for monitoring the editing state
    EditingMode Mode;
    sf::Text ModeText;

    TileInfo TileEditInfo;

    //changeable callbacks, changed when edit mode changes
    std::function<void(const sf::Keyboard::Key &key)> KeyPressed;
    std::function<void(const sf::Keyboard::Key &key)> KeyReleased;
    std::function<void(const sf::Vector2f &mPos, const sf::Mouse::Button &button)> MousePressed;
    std::function<void(const sf::Vector2f &mPos, const sf::Mouse::Button &button)> MouseReleased;
    std::function<void(const sf::Vector2f &mPos)> MouseMoved;

    //some functions that never change (load/save/etc)
    void SaveToFile(const std::string &file);
    void LoadFromFile(const std::string &file);
  };


}


#endif
