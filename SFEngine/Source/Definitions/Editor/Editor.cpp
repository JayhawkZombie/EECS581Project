#include "../../Headers/Engine/Editor.h"
#include "../../Headers/UI/Theme.h"
#include "../../Headers/UI/UICreationMacros.h"
#include "../../Headers/UI/UIIconSheet.h"
#include "../../Headers/Level/Level.h"

namespace Engine
{

  bool FlagForClose = false;

  Editor::Editor()
  {
    //Load the icon sheet
    UI::LoadIconSheet("./SFEngine/Source/CoreFiles/Textures/Icons/Icons.txt");
    IconSheet = std::make_shared<sf::Texture>();
    IconSheet->loadFromFile("./SFEngine/Source/CoreFiles/Textures/Icons/ui_icons_light.png");

    EditorFont.loadFromFile("./SFEngine/Source/CoreFiles/Fonts/Raleway-Regular.ttf");
    EditorModeText.setFont(EditorFont);
    EditorModeText.setCharacterSize(8);
    EditorModeText.setFillColor(sf::Color::White);
    EditorModeText.setPosition({ 400, 10 });
    EditorModeText.setString("Editor : Mode <No Selection>");

    MenuFont = std::make_shared<sf::Font>();
    MenuFont->loadFromFile("./SFEngine/Source/CoreFiles/Fonts/exo/Exo-Light.otf");

    TextFont = std::make_shared<sf::Font>();
    TextFont->loadFromFile("./SFEngine/Source/CoreFiles/Fonts/Raleway-Regular.ttf");

    PreviewGridInfoText.setFont(EditorFont);
    PreviewGridInfoText.setCharacterSize(6);
    PreviewGridInfoText.setFillColor(sf::Color::White);
    PreviewGridInfoText.setPosition({ 10, 820 });
    PreviewGridInfoText.setString("Grid Cell: 40 x 40");

    UITexture = std::shared_ptr<sf::RenderTexture>(new sf::RenderTexture);
    UITexture->create(WindowSize.x, WindowSize.y);

    EditorRenderState.blendMode = sf::BlendAdd;

    EditLevel = std::make_shared<Level>(sf::Vector2u({ 1920, 1080 }), sf::FloatRect(0, 0, 1920, 1080), true, sf::Vector2f({ 1920 / 16.f,1080 / 16.f }));

  }

  Editor::~Editor()
  {
    //TestMenu->Close();
  }

  void Editor::TickUpdate(const double &delta)
  {
    static float update_delta = 16.66667f;
    static float update_current = 0.f;

    update_current += delta;

    if (EnabledPhysics && (TestObjects.size() > 0 || Segments.size() > 0) && update_current >= update_delta) {
      UpdatePhysics(TestObjects, Segments, 2);
      update_current = 0.f;
    }

    UIHelper->TickUpdate(delta);

    if (IsUpdateLevelEnabled)
      EditLevel->TickUpdate(delta);
  }

  void Editor::Render(std::shared_ptr<sf::RenderTexture> Texture)
  {
    EditLevel->Render(Texture);

    UIHelper->Render(Texture);
    
    sf::VertexArray Varr = sf::VertexArray(sf::Lines, 2);

    for (auto & seg : Segments) {
      seg->draw(*currentRenderWindow);
    }

    sf::CircleShape circle;

    for (auto & obj : TestObjects) {
      obj->draw(*currentRenderWindow);
    }
  }

  void Editor::PreLoopSetup()
  {
    //set up the physics environment
    auto boundaries = WindowSize;
    std::cerr << "Editor::PreLoopSetup() : Boundaries {" << boundaries.x << ", " << boundaries.y << "}" << std::endl;
    AssignBoundaries(boundaries.y, boundaries.x);
    Gravity.x = 0.f;
    Gravity.y = 0.09f;
    SetGravity(&Gravity);
  }


}
