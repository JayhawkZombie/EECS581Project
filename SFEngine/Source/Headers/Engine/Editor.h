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
#include "../UI/Input/NumericComboBox.h"
#include "../UI/Toggles/SimpleToggle.h"
#include "../UI/Input/TextInput.h"
#include "../UI/Input/Spinner.h"

#include "../UI/UICreationMacros.h"

#include "../UI/ObjectView.h"
#include "../Editor/EditorProject.h"
//includes for our custom menus
#include "../UI/Menu/EditAnimationMenu.h"
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

    EditorProject Project;

    std::map<std::string, std::shared_ptr<TileSheet>> TIleSheets;

    //TGUI elements
    tgui::Font TestTGUIFont;
    tgui::Theme::Ptr UIThemePtr;

    std::shared_ptr<TileSheetEditor> EditTilesWindow;
    std::shared_ptr<NewProjectCreator> ProjectCreator;

#ifdef MessageBox
#undef MessageBox //WTF seriously? WTF is defining MessageBoxW as MessageBox? That is stupid, GTFO
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

    //Close button
    std::shared_ptr<UI::ClickButtonBase> CloseButton;

    //Check options
    std::shared_ptr<UI::SimpleToggle> EnablePhysicsToggle;
    bool EnabledPhysics = true;
    std::shared_ptr<UI::NumericComboBox> PhysicsTicksBox;
    std::shared_ptr<UI::ClickButtonBase> EraseObjectsButton;
    std::shared_ptr<UI::TextInput> TestInput;
    std::shared_ptr<UI::IntSpinner> TestSpinner;

    //test list widget
    std::shared_ptr<UI::ListWidget> TestList;
    std::shared_ptr<UI::ClickButtonBase> TestListUpButton;
    std::shared_ptr<UI::ClickButtonBase> TestListDownButton;

    //Tile editing menu
    std::shared_ptr<UI::MenuWidget> AddTileMenu;
    std::shared_ptr<UI::MenuScreen> AddTileScreen;
    std::shared_ptr<UI::TextInput> AddTileTextureInput;
    std::shared_ptr<UI::TextInput> AddTileFrameLeftInput;
    std::shared_ptr<UI::TextInput> AddTileFrameTopInput;
    std::shared_ptr<UI::TextInput> AddTileFrameWidthInput;
    std::shared_ptr<UI::TextInput> AddTileFrameHeightInput;
    std::shared_ptr<UI::ClickButtonBase> AddTileSaveButton;
    std::shared_ptr<UI::ClickButtonBase> AddTileCancelButton;
    std::shared_ptr<UI::SimpleToggle> AddTileIsAnimatedToggle;
    std::shared_ptr<UI::ClickButtonBase> AddTileButton;

    //AddClass Menu
    std::shared_ptr<UI::MenuWidget> AddClassMenu;
    std::shared_ptr<UI::MenuScreen> AddClassSelectScreen;
    std::shared_ptr<UI::ClickButtonBase> AddClassAddActorButton;
    std::shared_ptr<UI::ClickButtonBase> AddClassAddObjectButton;
    std::shared_ptr<UI::ClickButtonBase> AddClassAddLightButton;
    std::shared_ptr<UI::ClickButtonBase> AddClassAddEffectButton;
    std::shared_ptr<UI::ClickButtonBase> AddClassAddCancelButton;

    std::shared_ptr<UI::ClickButtonBase> AddClassButton;

    std::shared_ptr<UI::MenuScreen> AddActorClassScreen;
    std::shared_ptr<UI::ClickButtonBase> AddActorClassCancelButton;

    std::shared_ptr<UI::MenuScreen> AddObjectClassScreen;
    std::shared_ptr<UI::ClickButtonBase> AddObjectClassCancelButton;

    std::shared_ptr<UI::MenuScreen> AddLightClassScreen;
    std::shared_ptr<UI::ClickButtonBase> AddLightClassCancelButton;

    std::shared_ptr<UI::MenuScreen> AddEffectClassScreen;
    std::shared_ptr<UI::ClickButtonBase> AddEffectClassCancelButton;

    //TestMenu
    UIMenu TestMenus;
    UIMenuScreen TestSelectScreen;
    UIButton OpenTestMenusButton; //for opening the menu from the main screen
    UIButton TestSelectEditAnimationButton;
    UIButton TestSelectCancelButton;


    UI::EditAnimationMenu AnimMenu;

    std::shared_ptr<UI::ObjectView> TestObjectView;
    std::shared_ptr<Animation> TestActorAnimation;
    std::shared_ptr<sf::Texture> TestAnimationTexture;



    sf::Color ButtonColorNormal = sf::Color(58, 0, 29);
    sf::Color ButtonColorHighlighted = sf::Color(86, 0, 43);
    sf::Color ButtonColorPressed = sf::Color(33, 0, 16);
    sf::Color ButtonOutlineNormal = sf::Color(0, 59, 127);
    sf::Color ButtonOutlineHighlighted = sf::Color(0, 40, 86);
    sf::Color ButtonOutlinePressed = sf::Color(0, 84, 181);

    std::shared_ptr<UI::ClickButtonBase> AllObjectButton;
    std::shared_ptr<UI::MenuWidget> ObjectSelectMenu;
    //Object types screen
    std::shared_ptr<UI::MenuScreen> ObjectSelectTypeScreen;
    std::shared_ptr<UI::ClickButtonBase> ObjectSelectType_PhysicsObjectButton;
    std::shared_ptr<UI::ClickButtonBase> ObjectSelectType_LightObjectButton;
    std::shared_ptr<UI::ClickButtonBase> ObjectSelectType_EffectObjectButton;
    std::shared_ptr<UI::ClickButtonBase> ObjectSelectType_CancelButton;

    std::shared_ptr<UI::MenuScreen> ObjectSelectPhysicsObjectScreen;
    std::shared_ptr<UI::ClickButtonBase> ObjectSelect_BackToSelectTypeButton;
    std::shared_ptr<UI::ClickButtonBase> ObjectSelect_BallButton;
    std::shared_ptr<UI::ClickButtonBase> ObjectSelect_SquareButton;
    std::shared_ptr<UI::ClickButtonBase> ObjectSelect_RectButton;
    std::shared_ptr<UI::ClickButtonBase> ObjectSelect_TriangleButton;
    std::shared_ptr<UI::ClickButtonBase> ObjectSelect_5PolyButton;

    std::shared_ptr<UI::MenuScreen> ObjectSelectLightObjectScreen;
    std::shared_ptr<UI::ClickButtonBase> LightSelect_CancelButton;

    std::shared_ptr<UI::MenuScreen> ObjectSelectEffectObjectScreen;
    std::shared_ptr<UI::ClickButtonBase> EffectSelect_CancelButton;

    std::shared_ptr<sf::Font> TextFont;
    std::shared_ptr<sf::Texture> ButtonOverlayTexture;

    //Data for the tile menu on the left
    std::shared_ptr<UI::ListWidget> TileList;
    std::shared_ptr<UI::ClickButtonBase> TileListOpenCloseButton;

    std::shared_ptr<UI::ListWidget> EditOptionsList;
    std::shared_ptr<UI::ClickButtonBase> EditOptionsOpenCloseButton;
    std::shared_ptr<sf::Font> MenuFont;

    //Test screen buttons
    std::shared_ptr<UI::ClickButtonBase> TestScreenButton1;
    std::shared_ptr<UI::ClickButtonBase> TestScreenButton2;
    std::shared_ptr<UI::ClickButtonBase> TestScreenButton3;
    std::shared_ptr<UI::ClickButtonBase> TestScreenButton4;
    std::shared_ptr<UI::ClickButtonBase> TestScreenButton5;
    std::shared_ptr<UI::ClickButtonBase> TestScreenButton6;

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
