#include "../../Headers/Level/LevelEnvironment.h"
#include "../../Headers/Actor/Player.h"


namespace Engine
{

  LevelEnvironment::LevelEnvironment()
    : TilesAssigned(0), LevelMovement({ 0.f, 0.f })
  {
    DiagnosticText.setPosition(sf::Vector2f(100, 700));
    DiagnosticText.setCharacterSize(12);
    DiagnosticText.setFillColor(sf::Color::White);
    DiagnosticText.setString("Sample Diagnostic String");
  }

  LevelEnvironment::~LevelEnvironment()
  {

  }

  void LevelEnvironment::AddGlobalLight(const std::string &ID, std::shared_ptr<GlobalLightSource> src)
  {

  }

  void LevelEnvironment::AddActor(const std::string &ID, std::shared_ptr<GenericActor> src)
  {

  }

  void LevelEnvironment::AddLight(const std::string &ID, std::shared_ptr<GenericLightSource> src)
  {

  }

  void LevelEnvironment::SetPlayer(std::shared_ptr<Player> player)
  {

  }
  
  GlobalLightSource* LevelEnvironment::GetGlobalLight(const std::string &ID)
  {
    return nullptr;
  }

  GenericActor* LevelEnvironment::GetActor(const std::string &ID)
  {
    return nullptr;
  }

  GenericLightSource* LevelEnvironment::GetLight(const std::string &ID)
  {
    return nullptr;
  }

  Player* LevelEnvironment::GetPlayer(const std::string &ID)
  {
    return nullptr;
  }

  void LevelEnvironment::UpdateGemoetry(const double &delta)
  {
    int CELL_LEFT = std::floor(CurrentView.left / TileSize);
    int CELL_TOP = std::floor(CurrentView.top / TileSize);
    int CELL_RIGHT = std::floor(CurrentView.width / TileSize);
    int CELL_BOTTOM = std::floor(CurrentView.height / TileSize);

    for (std::size_t X = CELL_LEFT; X <= CELL_RIGHT; ++X) {
      for (std::size_t Y = CELL_TOP; Y <= CELL_BOTTOM; ++Y) {
        EnvironmentGrid.Mat[Y][X].TickUpdate(delta);
      }
    }

    MoveView(LevelMovement);
  }

  void LevelEnvironment::UpdateView(const double &delta)
  {
    ComputeLevelScale();

    for (std::size_t Y = 0; Y < LevelSizeY; ++Y) {
      for (std::size_t X = 0; X < LevelSizeX; ++X) {
        sf::Vector2f WC;

        ComputeLevelToWindowTransformation(EnvironmentGrid.Mat[Y][X].LevelPosition, WC);

        EnvironmentGrid.Mat[Y][X].ScreenPosition = WC;
        EnvironmentGrid.Mat[Y][X].BGTile.TileSprite.setPosition(WC);
        EnvironmentGrid.Mat[Y][X].BGTile.TileSprite.setScale(LevelScale);

      }
    }

    DiagnosticText.setPosition(sf::Vector2f(100.f, 400.f));
    DiagnosticText.setCharacterSize(12);
    DiagnosticText.setFillColor(sf::Color::White);
    DiagnosticText.setString(
      "Current Level View: (" + std::to_string(CurrentView.left) + ", " + std::to_string(CurrentView.top)
      + ", " + std::to_string(CurrentView.width) + ", " + std::to_string(CurrentView.height)
    );
  }

  void LevelEnvironment::ComputeLevelScale()
  {
    LevelScale = sf::Vector2f(
      WindowSize.x / (CurrentView.width - CurrentView.left),
      WindowSize.y / (CurrentView.height - CurrentView.top)
    );

  }

  void LevelEnvironment::ComputeLevelToWindowTransformation(sf::Vector2f &LC, sf::Vector2f &WC)
  {
    //Compute the scaling from Level Coordinates to Window Coordinates
    /*
    X Mapping: CurrentView.left -> 0
    CurrentView.width -> WinSize.x
    Y Mapping: CurrentView.top -> 0
    CurrentView.height -> WinSize.y
    */
    WC = sf::Vector2f(
      LevelScale.x * (LC.x - CurrentView.left),
      LevelScale.y * (LC.y - CurrentView.top)
    );
  }

  void LevelEnvironment::TickUpdate(const double &delta)
  {
    UpdateGemoetry(delta);
    UpdateView(delta);
  }

  void LevelEnvironment::MoveView(const sf::Vector2f &Movement) 
  {
    float deltaLeft, deltaRight, deltaUp, deltaDown;

    deltaLeft = CurrentView.left + Movement.x;
    deltaRight = CurrentView.width + Movement.x;
    deltaUp = CurrentView.top + Movement.y;
    deltaDown = CurrentView.height + Movement.y;

    sf::FloatRect NewView = CurrentView;

    //Check to make sure we aren't trying to view outside the level
    
    if (!(deltaLeft < 0) && !(deltaRight >= LevelSizeX * TileSize)) {
      NewView.left += Movement.x;
      NewView.width += Movement.x;
    }

    if (!(deltaUp < 0) && !(deltaDown >= LevelSizeY * TileSize)) {
      NewView.top += Movement.y;
      NewView.height += Movement.y;
    }
    
    CurrentView = NewView;
  }

  void LevelEnvironment::Render()
  {
    int CELL_LEFT = std::floor(CurrentView.left / TileSize);
    int CELL_TOP = std::floor(CurrentView.top / TileSize);
    int CELL_RIGHT = std::floor(CurrentView.width / TileSize);
    int CELL_BOTTOM = std::floor(CurrentView.height / TileSize);

    for (int x = CELL_LEFT; x <= CELL_RIGHT; ++x) {
      for (int y = CELL_TOP; y <= CELL_BOTTOM; ++y) {
        Render::RenderSprite(
          &EnvironmentGrid.Mat[y][x].BGTile.TileSprite
        );
      }
    }

  }

  void LevelEnvironment::HandleKeyPress(const sf::Keyboard::Key &key)
  {
    switch (key)
    {
      case sf::Keyboard::Up:
        LevelMovement.y = -0.2f;
        break;
      case sf::Keyboard::Down:
        LevelMovement.y = 0.2f;
        break;
      case sf::Keyboard::Left:
        LevelMovement.x = -0.2f;
        break;
      case sf::Keyboard::Right:
        LevelMovement.x = 0.2f;
        break;
    }
  }

  void LevelEnvironment::HandleKeyRelease(const sf::Keyboard::Key &key)
  {
    switch (key)
    {
      case sf::Keyboard::Up:
        LevelMovement.y = 0;
        break;
      case sf::Keyboard::Down:
        LevelMovement.y = 0;
        break;
      case sf::Keyboard::Left:
        LevelMovement.x = 0;
        break;
      case sf::Keyboard::Right:
        LevelMovement.x = 0;
        break;
    }
  }

}
