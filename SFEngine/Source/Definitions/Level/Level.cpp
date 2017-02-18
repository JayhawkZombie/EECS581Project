#include "../../Headers/Level/Level.h"
#include "../../Headers/Physics/PhysicsEngineInterface.h"
namespace
{

}

namespace Engine
{

  Level::Level(const sf::Vector2u &LevelSize, const sf::FloatRect &DefaultView, bool showlines, const sf::Vector2f &GridSpacing)
  {
    ShowGridLines = showlines;
    Size = LevelSize;
    GridBlockSize = GridSpacing;
    CurrentView = DefaultView;
    SceneTarget = std::make_shared<sf::RenderTexture>();
    SceneTarget->create(LevelSize.x, LevelSize.y);
    AssignBoundaries(static_cast<float>(LevelSize.x), static_cast<float>(LevelSize.y));

    auto seg = BuildSegmentMesh('L', { 0, 0 }, { 300, 500 });
    TestSegments.push_back(seg);

    Gravity.x = 0.f;
    Gravity.y = 0.09f;
    SetGravity(&Gravity);
    if (ShowGridLines) {
      GenerateGrid();
    }
  }

  Level::Level(const std::string &lvl)
  {
    Handler.BindCallback(Events::KeyPressed,

                         [this](const sf::Keyboard::Key &k) -> void
    {
      this->HandleKeyPress(k);
    }

    );
    Handler.BindCallback(Events::KeyReleased,

                         [this](const sf::Keyboard::Key &k) ->void
    {
      this->HandleKeyRelease(k);
    }
    );
  }

  Level::~Level()
  {

  }

  void Level::GenerateGrid()
  {
    float xpos = 0, ypos = 0;
    sf::VertexArray hline = sf::VertexArray(sf::Lines, 2);
    sf::VertexArray vline = sf::VertexArray(sf::Lines, 2);

    while (ypos < Size.y) {
      hline[0].position = { 0, ypos }; hline[0].color = sf::Color(0, 123, 137);
      hline[1].position = { static_cast<float>(Size.x), ypos }; hline[1].color = sf::Color(0, 123, 137);

      GridLines.push_back(hline);
      ypos += GridBlockSize.y;
    }

    while (xpos < Size.x) {
      vline[0].position = { xpos, 0 }; vline[0].color = sf::Color(0, 123, 137);
      vline[1].position = { xpos, static_cast<float>(Size.y) }; vline[1].color = sf::Color(0, 123, 137);

      GridLines.push_back(vline);
      xpos += GridBlockSize.y;
    }
  }

  void Level::LoadLevel(const std::string &lvlfile)
  {
    std::ifstream in(lvlfile);
    if (!in) {
      std::cerr << "Unable to open level file: " << lvlfile << std::endl;
      return;
    }

    
  }

  void Level::OnShutDown()
  {

  }

  void Level::HandleWindowResized()
  {

  }
}