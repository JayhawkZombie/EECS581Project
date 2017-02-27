#include "../../Headers/Level/Level.h"

#ifdef WITH_EDITOR
namespace Engine
{

  void Level::ShowSpawner()
  {
    if (!ImGui::Begin("Spawner")) {
      ImGui::End();
      return;
    }

    ShowPhysicsSpawner();
    ImGui::End();
  }

  void Level::ShowPhysicsSpawner()
  {
    static sf::Vector2f Pos = { 0, 0 };
    static sf::Vector2f Vel = { 0, 0 };
    static int radius = 5;
    static vec2d gravity = vec2d(0, 0.01);
    static int numsides = 3;
    static float mass = 0.01;
    static float coeffRest = 0.1;
    static float rotation = 0.f;
    static sf::Color color = sf::Color::White;
    static sf::RenderTexture ballTex;
    static sf::RenderTexture polyTex;
    static bool created = false;
    static sf::Sprite bRect;
    static sf::Sprite pRect;
    if (!created) {
      ballTex.create(100, 100);
      polyTex.create(100, 100);
      bRect.setTexture(ballTex.getTexture());
      pRect.setTexture(ballTex.getTexture());
      bRect.setTextureRect({ 0, 0, 100, 100 });
      pRect.setTextureRect({ 0, 0, 100, 100 });
      created = true;
    }

    ballTex.setActive(true);
    polyTex.setActive(true);
    ballTex.clear(sf::Color::Transparent);
    polyTex.clear(sf::Color::Transparent);

    static std::shared_ptr<PhysicsEngineBaseMeshType> Mesh;

    if (ImGui::CollapsingHeader("Meshes <testing>")) {
      //mesh spawner logic
      ImGui::Separator();
      ImGui::Text("Position and Size");
      if (ImGui::InputFloat("PosX", &Pos.x, 5.f, 15.f)) {
        if (Pos.x < 0) Pos.x = 0;
      }
      if (ImGui::InputFloat("PoxY", &Pos.y, 5.f, 15.f)) {
        if (Pos.y < 0) Pos.y = 0;
      }
      if (ImGui::InputInt("Radius", &radius, 1, 5)) {
        if (radius < 0) radius = 0;
      }
      ImGui::Separator();

      ImGui::Text("Velocity");
      ImGui::InputFloat("x", &Vel.x, 1.f, 5.f);
      ImGui::InputFloat("y", &Vel.y, 1.f, 5.f);
      ImGui::Separator();

      ImGui::Text("Gravity and Fraction");
      if (ImGui::InputFloat("Mass", &mass, 0.01, 0.1)) {
        if (mass < 0.01) mass = 0.01;
      }
      if (ImGui::InputFloat("Coeff of rest", &coeffRest, 0.05, 0.1)) {
        if (coeffRest < 0.05) coeffRest = 0.05;
      }
      if (ImGui::InputFloat("Gravity X", &gravity.x, 0.01, 0.1)) {
        SetGravity(&gravity);
      }
      if (ImGui::InputFloat("Gravity Y", &gravity.y, 0.01, 0.1)) {
        SetGravity(&gravity);
      }
      ImGui::Separator();

      ImGui::Text("Color");
      static float R = 0, G = 0, B = 0, A = 0;
      if (ImGui::DragFloat("Red", &R, 0.01f, 0.f, 1.f)) {
        color.r = static_cast<sf::Uint8>(std::floor(R * 255));
      }
      if (ImGui::DragFloat("Green", &G, 0.01f, 0.f, 1.f)) {
        color.g = static_cast<sf::Uint8>(std::floor(G * 255));
      }
      if (ImGui::DragFloat("Blue", &B, 0.01f, 0.0f, 1.0f)) {
        color.b = static_cast<sf::Uint8>(std::floor(B * 255));
      }
      ImGui::Separator();

      if (ImGui::CollapsingHeader("Ball")) {
        Mesh = BuildBallMesh('B', { 50.f, 50.f }, { 0, 0 }, radius, mass, coeffRest, color);
        ballTex.clear();
        Mesh->draw(ballTex);
        ballTex.display();

        ImGui::Image(ballTex.getTexture(), ImVec2(100, 100), sf::FloatRect(0, 0, 100, 100));

        if (ImGui::Button("Spawn")) {
          ImGui::SameLine();
          SpawnBall('B', Pos, Vel, radius, mass, coeffRest, color);
        }
      }

      if (ImGui::CollapsingHeader("N-Poly")) {
        Mesh = BuildPolygonMesh(numsides, radius, rotation, { 50.f, 50.f }, { 0 ,0 }, mass, coeffRest, color);

        if (ImGui::SliderFloat("Rotation", &rotation, 0, 2 * PI)) {
          Mesh = BuildPolygonMesh(numsides, radius, rotation, { 50.f, 50.f }, { 0 ,0 }, mass, coeffRest, color);
        }
        if (ImGui::InputInt("Num Sides", &numsides, 1, 5)) {
          if (numsides < 3)
            numsides = 3;

          Mesh = BuildPolygonMesh(numsides, radius, rotation, { 50.f, 50.f }, { 0 ,0 }, mass, coeffRest, color);
        }
        polyTex.clear();
        Mesh->draw(polyTex);
        polyTex.display();

        ImGui::Image(polyTex.getTexture(), ImVec2(100, 100), sf::FloatRect(0, 0, 100, 100));
        if (ImGui::Button("Spawn")) {
          ImGui::SameLine();
          SpawnNPoly(numsides, radius, rotation, Pos, Vel, mass, coeffRest, color);
        }
      }
    }

    if (ImGui::Selectable("Particles <empty>")) {
      //particle spawner logic
    }

    if (ImGui::Selectable("Entities <none>")) {
      //entity spawner logic
    }

    //if (ImGui::InputFloat("x Coordinate", &Pos.x, 1.f, 5.f)) {
    // /* if (Pos.x < 0)
    //    Pos.x = 0;*/
    //}
    //if (ImGui::InputFloat("y Coordinate", &Pos.y, 1.f, 5.f)) {
    //  /*if (Pos.y < 0)
    //    Pos.y = 0;*/
    //}
    //if (ImGui::DragFloat("Velocity x", &Vel.x, 1.f, 0.f, 20.f)) {

    //}
    //if (ImGui::DragFloat("Velocity y", &Vel.y, 1.f, 0.f, 20.f)) {

    //}
    //if (ImGui::InputInt("Radius", &radius, 1, 5)) {
    //  if (radius < 0)
    //    radius = 0;
    //}
    //if (ImGui::DragFloat("Mass", &mass, 0.001, 0.001, 1.f)) {

    //}
    //if (ImGui::DragFloat("Gravity", &gravity.y, 0.01, 0.01f, 2.f)) {
    //  SetGravity(&gravity);
    //}
    //if (ImGui::InputFloat("Coeff of Rest", &coeffRest, 0.1f, 0.2f)) {
    //  if (coeffRest < 0)
    //    coeffRest = 0;
    //}
    //if (ImGui::Button("Clear All")) {
    //  for (auto & obj : TestObjects)
    //    obj.reset();
    //  TestObjects.clear();
    //}
    //ImGui::Text("Color");

    //static float R = 0, G = 0, B = 0, A = 0;
    //if (ImGui::DragFloat("Red", &R, 0.01f, 0.f, 1.f)) {
    //  color.r = static_cast<sf::Uint8>(std::floor(R * 255));
    //}
    //if (ImGui::DragFloat("Green", &G, 0.01f, 0.f, 1.f)) {
    //  color.g = static_cast<sf::Uint8>(std::floor(G * 255));
    //}
    //if (ImGui::DragFloat("Blue", &B, 0.01f, 0.0f, 1.0f)) {
    //  color.b = static_cast<sf::Uint8>(std::floor(B * 255));
    //}

    //ImGui::Separator();

    //if (ImGui::CollapsingHeader("Ball")) {
    //  Mesh = BuildBallMesh('B', { 50.f, 50.f }, { 0, 0 }, radius, mass, coeffRest, color);
    //  Mesh->draw(tex);
    //  tex.display();

    //  ImGui::Image(tex.getTexture(), ImVec2(100, 100));
    //  if (ImGui::Button("Spawn")) {
    //    ImGui::SameLine();
    //    SpawnBall('B', Pos, Vel, radius, mass, coeffRest, color);
    //  }
    //}

    //if (ImGui::CollapsingHeader("N-Poly")) {
    //  Mesh = BuildPolygonMesh(numsides, radius, rotation, { 50.f, 50.f }, { 0 ,0 }, mass, coeffRest, color);

    //  if (ImGui::SliderFloat("Rotation", &rotation, 0, 2 * PI)) {
    //    Mesh = BuildPolygonMesh(numsides, radius, rotation, { 50.f, 50.f }, { 0 ,0 }, mass, coeffRest, color);
    //  }
    //  if (ImGui::InputInt("Num Sides", &numsides, 1, 5)) {
    //    if (numsides < 3)
    //      numsides = 3;

    //    Mesh = BuildPolygonMesh(numsides, radius, rotation, { 50.f, 50.f }, { 0 ,0 }, mass, coeffRest, color);
    //  }

    //  Mesh->draw(tex);
    //  tex.display();
    //  ImGui::Image(tex.getTexture(), ImVec2(100, 100));
    //  if (ImGui::Button("Spawn")) {
    //    ImGui::SameLine();
    //    SpawnNPoly(numsides, radius, rotation, Pos, Vel, mass, coeffRest, color);
    //  }
    //}

  }

}
#endif
