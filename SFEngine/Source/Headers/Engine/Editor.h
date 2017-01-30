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

    void HandleMousePressed(const InputEvent &Event);
    void HandleMouseReleased(const InputEvent &Event);
    void HandleMouseMoved(const InputEvent &Event);
    void HandleMouseScrolled(const InputEvent &Event);
    void HandleKeyPressed(const InputEvent &Event);
    void HandleKeyReleased(const InputEvent &Event);
    void HandleTextEntered(const InputEvent &Event);

    void HandleWindowResized(const sf::Vector2u &NewWindowSize);

  protected:
    sf::RenderStates EditorRenderState;
    sf::RectangleShape EditorRect;

    //Used for sizing/spacing for different windows sizes
    float TopButtonHeight;
    float TopButtonWidth;

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

    //Data for the tile menu on the left
    std::shared_ptr<UI::ListWidget> TileList;
    std::shared_ptr<UI::ClickButtonBase> TileListOpenCloseButton;

    std::shared_ptr<UI::ListWidget> EditOptionsList;
    std::shared_ptr<UI::ClickButtonBase> EditOptionsOpenCloseButton;

    std::shared_ptr<UI::PopupObject> TestPopup;
    std::shared_ptr<UI::Alert> Alert;

    std::shared_ptr<UI::MenuWidget> TestMenu;
    std::shared_ptr<UI::MenuScreen> TestScreen;
    std::shared_ptr<UI::MenuScreen> TestScreen2;
    std::shared_ptr<UI::MenuScreen> TestScreen3;
    
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

    vec2d Gravity;
    std::vector<BaseMeshPtr> TestObjects;
    std::vector<SegmentPtr> Segments;

    BaseMeshPtr testball;
    SegmentPtr testsegment;
    /**
    *  _________________________________________________________________
    *  |                                                               |
    *  |                                                               |  <-- EditOptionsList
    *  |_______________________________________________________________|
    *  |                      |________________| <-- OpenCloseButton
    *  |
    *  |
    *  
    *  _________________________________________________________________
    *  |___________| <- TileSelect_OpenCloseButton
    *  |           |
    *  |           |
    *  |           |
    *  |           |
    *  |           |
    *  |           | <-- TileSelectList
    *  |           |
    *  |           |
    *  |           |
    *  |           |
    *  |___________|
    */

    //data for visualization
    sf::Font EditorFont;
    sf::Text EditorModeText;
    sf::Text PreviewGridInfoText;
    std::vector<sf::VertexArray> PreviewGridLines;

    //the lists needed for editing
    std::shared_ptr<UI::ListWidget> ObjectList;

    //Tiles for dragging into the level
    std::vector<std::shared_ptr<UI::DraggableTile>> DragTiles;
    std::shared_ptr<sf::Texture> TilesTexture;

    std::shared_ptr<UI::WidgetHelper> UIHelper;
    std::shared_ptr<UI::UILayer> UILayer;
    sf::Sprite UISprite;

    std::shared_ptr<sf::RenderTexture> UITexture;
    std::shared_ptr<UI::ClickButtonBase> TestButton;
    std::shared_ptr<UI::ClickButtonBase> TestButton2;


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
