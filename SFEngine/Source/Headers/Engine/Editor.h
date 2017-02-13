#ifndef SFENGINE_EDITOR_H
#define SFENGINE_EDITOR_H

#include <SFML/Graphics.hpp>

#include "../BasicIncludes.h"

#include "../Actor/Player.h"
#include "../Animation/Animation.h"
#include "../Render/Render.h"

#include "../UI/List/List.h"
#include "../UI/Text/TextLabel.h"
#include "../UI/WIdgetHelper.h"
#include "../UI/Buttons/ClickButtonBase.h"
#include "../UI/Draggables/DraggableTile.h"
#include "../UI/Alerts/PopupObject.h"

#include "../UI/Alerts/Alert.h"

#include "../UI/Menu/MenuWidget.h"
#include "../UI/Menu/MenuScreen.h"

#include "../../../ThirdParty/PhysicsEngine.h"
#include "../UI/ObjectView.h"
#include "../Editor/EditorProject.h"
#include "../UI/UIIconSheet.h"
#include <fstream>
#include <map>





//TGUI elements
#include "../Editor/TileSheetEditor.h"
#include "../Editor/CreateNewProject.h"
#include "../Editor/EditorProject.h"

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

    void HandleWindowResized(const sf::Vector2u &NewWindowSize);
    void BindEditorMethods(chaiscript::ModulePtr mptr);
  protected:
    void MenuBarItemSelected(std::vector<sf::String> vec);
    void ShutDownEditor();
    void OpenTilesheetViewer();
    void OpenProjectCreator();

    void SelectLevelTab();
    void ExpandLevelPanel();

    void SelectAnimationTab();
    void ExpandAnimationPanel();
    
    void SelectGUITab();
    void ExpandGUIPanel();
    
    void SelectActorsTab();
    void ExpandActorsPanel();
    
    void SelectMusicTab();
    void ExpandMusicPanel();
    
    void HideSideTabPanel();

    EditorProject Project;

    std::map<std::string, std::shared_ptr<TileSheet>> TIleSheets;

    tgui::MenuBar::Ptr MenuBar;

    //TGUI elements
    tgui::Font TestTGUIFont;
    tgui::Theme::Ptr UIThemePtr;
    tgui::Panel::Ptr SideTabPanel;
    tgui::Button::Ptr LevelTab;
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
    tgui::SpinButton::Ptr LevelPanelLayerSpinner;
    tgui::Button::Ptr LevelPanelTilesButton;
    tgui::Button::Ptr LevelPanelObjectsButton;
    tgui::Button::Ptr LevelPanelActorsButton;
    tgui::Button::Ptr LevelPanelMusicButton;
    tgui::Button::Ptr LevelPanelExpandButton;

    tgui::Panel::Ptr AnimationPanel;
    tgui::Button::Ptr AnimationPanelExpandButton;

    tgui::Panel::Ptr GUIPanel;
    tgui::Button::Ptr GUIPanelExpandButton;

    tgui::Panel::Ptr ActorsPanel;
    tgui::Button::Ptr ActorsPanelExpandButton;

    tgui::Panel::Ptr MusicPanel;
    tgui::Button::Ptr MusicPanelExpandButton;

    std::shared_ptr<TileSheetEditor> EditTilesWindow;
    std::shared_ptr<NewProjectCreator> ProjectCreator;

#ifdef MessageBox
#undef MessageBox //WTF seriously? WTF is defining MessageBoxW as MessageBox? That is stupid, GTFO -- WINDOWWWWWWWSSSSS, WWWWWHHHHHYYYYYYYYY???!!!!!!!!!
#endif

    tgui::MessageBox::Ptr QuitMessageBox;

    sf::RenderStates EditorRenderState;
    sf::RectangleShape EditorRect;

    chaiscript::ChaiScript *EditorScriptEngine;

    //Test actor, just for testing
    GenericActor TestActor;
    std::shared_ptr<sf::Texture> TestActorSpriteSheet;
    std::shared_ptr<Animation> TestAnimation;

    std::shared_ptr<Level> EditLevel;

    std::shared_ptr<UI::ListWidget> TestListWidget;

    //Used for sizing/spacing for different windows sizes
    float TopButtonHeight;
    float TopButtonWidth;

    bool IsUpdateLevelEnabled = true;

    std::shared_ptr<UI::LevelWidget> LevelView;

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

    std::shared_ptr<UI::WidgetHelper> UIHelper;
    std::shared_ptr<UI::UILayer> UILayer;
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
