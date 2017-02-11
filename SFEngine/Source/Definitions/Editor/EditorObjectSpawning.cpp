#include "../../Headers/Engine/Editor.h"

namespace Engine
{

  void Editor::SpawnBall(const sf::Vector2f &Position)
  {
    std::cerr << "Spawn object at: " << Position.x << ", " << Position.y << std::endl;


    auto Ball = BuildBallMesh('B', Position, { 0,0 }, 40, 1.f, 0.8f, sf::Color::Green);
    TestObjects.push_back(Ball);

    //std::cerr << "Ball pos: " << Ball->pos.x << ", " << Ball->pos.y << std::endl;
    //auto ptr = (ball_go *)(Ball.get());
    //ptr->r = 25;
    //std::cerr << "Ball rad: " << ptr->r << std::endl;
  }

  void Editor::SpawnRect(const sf::Vector2f &Position)
  {
    auto poly = BuildPolygonMesh(4, 15.f, 0.f, { 400, 0 }, { 0,0 }, 1.f, 0.5f, sf::Color::Blue);
    TestObjects.push_back(poly);
  }

  void Editor::SpawnTriangle(const sf::Vector2f & Position)
  {
    auto tri = BuildPolygonMesh(3, 15.f, 0.f, { 400, 0 }, { 0,0 }, 1.f, 0.5f, sf::Color::White);
    TestObjects.push_back(tri);
  }

  void Editor::Spawn5Poly(const sf::Vector2f & Position)
  {
    auto poly = BuildPolygonMesh(5, 15.f, 0.f, { 400, 0 }, { 0,0 }, 1.f, 0.5f, sf::Color(127, 0, 130));
    TestObjects.push_back(poly);
  }

  void Editor::SpawnSquare(const sf::Vector2f &Position)
  {
    auto poly = BuildPolygonMesh(4, 15.f, 0.f, { 400, 0 }, { 0,0 }, 1.f, 0.5f, sf::Color::White);
    TestObjects.push_back(poly);
  }

}