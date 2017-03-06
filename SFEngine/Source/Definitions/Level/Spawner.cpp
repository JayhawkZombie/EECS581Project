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
    static float drag = 0.5f;

    ballTex.setActive(true);
    polyTex.setActive(true);
    ballTex.clear(sf::Color::Transparent);
    polyTex.clear(sf::Color::Transparent);

    static std::shared_ptr<PhysicsEngineBaseMeshType> Mesh;

    if (ImGui::DragFloat("UpdateInterval", &updateInterval, 1.f, 10.f, 33.f)) {

    }

    if (ImGui::CollapsingHeader("Meshes <testing>")) {
      //mesh spawner logic
      ImGui::Separator();
      ImGui::Indent();

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
        for (auto & item : Segments) {
          auto ptr = dynamic_cast<waveSeg*>(item.get());
          if (ptr) {
            ptr->grav_N = gravity.y;
          }
        }
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

        if (ImGui::SliderFloat("Rotation", &rotation, 0, 2 * ____PI)) {
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

      ImGui::Unindent();
    }

    if (ImGui::CollapsingHeader("Waves")) {
      if (ImGui::InputFloat("Segment Drag", &drag, 0.05, 0.1)) {
        mvHit::drag = drag;
      }

      ImGui::Indent();

      static sf::Vector2i leftCorner{ 0, 0 }, rightCorner{ 0, 0 };
      static float waveRad = 5;
      static float ampL{ 0 }, ampR{ 0 }, wvR{ 0 }, wvL{ 0 }, frL{ 0 }, frR{ 0 };
      static float elev{ 0 }, airDen{ 0 }, fluidDen{ 0 }, depth{ 0 };

      ImGui::Separator();
      ImGui::Text("Position and Size");
      if (ImGui::InputInt("Left PosX", &leftCorner.x, 5, 15)) {
        if (Pos.x < 0) Pos.x = 0;
      }
      if (ImGui::InputInt("Left PoxY", &leftCorner.y, 5, 15)) {
        if (Pos.y < 0) Pos.y = 0;
      }
      if (ImGui::InputInt("Right PosX", &rightCorner.x, 5, 15)) {
        if (Pos.x < 0) Pos.x = 0;
      }
      if (ImGui::InputInt("Right PoxY", &rightCorner.y, 5, 15)) {
        if (Pos.y < 0) Pos.y = 0;
      }
      if (ImGui::InputFloat("Radius", &waveRad, 10.f, 20.f)) {
        if (waveRad < 5.f)
          waveRad = 5.f;
      }
      ImGui::Separator();

      ImGui::Text("Amplitude, Wavelen & Frequency");

      ImGui::Columns(2);
      ImGui::NewLine();
      ImGui::DragFloat("Amp", &ampL, 5.f, 0.f, 50.f);
      ImGui::DragFloat("Wavelen", &wvL, 5.f, 100.f, 1000.f);
      ImGui::DragFloat("Frequency", &frL, 0.0005, 0.f, 0.05f);
      ImGui::NextColumn();
      ImGui::DragFloat("Amp", &ampR, 5.f, 0.f, 50.f);
      ImGui::DragFloat("Wavelen", &wvR, 5.f, 100.f, 1000.f);
      ImGui::DragFloat("Frequency", &frR, 0.0005, 0.f, 0.05f);

      ImGui::Columns(1);
      ImGui::Separator();

      ImGui::Text("Elevation and Density");

      ImGui::InputFloat("Elevation", &elev, 5.f, 15.f);
      ImGui::InputFloat("Depth", &depth, 5.f, 15.f);
      ImGui::InputFloat("Air Density", &airDen, 0.00005, 0.0001);
      ImGui::InputFloat("Fluid Density", &fluidDen, 0.005, 0.001);

      if (ImGui::Button("Spawn")) {
        SpawnWave('W', leftCorner, rightCorner, radius, false, 300, ampR, wvR, frR, ampL, wvL, frL, elev, airDen, depth, fluidDen);
      }

      ImGui::Unindent();
    }

    if (ImGui::Selectable("Particles <empty>")) {
      //particle spawner logic
    }

    if (ImGui::CollapsingHeader("Entities")) {

		static sf::Vector2f Position = { 0, 0 };

		ImGui::Indent();
		if (ImGui::CollapsingHeader("Actors")) {
			//entity spawner logic
			ImGui::Separator();
			ImGui::Indent();

			ImGui::Text("Position and Size");
			if (ImGui::InputFloat("PosX", &Position.x, 5.f, 15.f)) {
				if (Position.x < 0) Position.x = 0;
			}
			if (ImGui::InputFloat("PoxY", &Position.y, 5.f, 15.f)) {
				if (Position.y < 0) Position.y = 0;
			}
			if (ImGui::InputInt("Radius", &radius, 1, 5)) {
				if (radius < 0) radius = 0;
			}
			ImGui::Separator();

			ImGui::Text("Velocity");
			ImGui::InputFloat("x", &Vel.x, 1.f, 5.f);
			ImGui::InputFloat("y", &Vel.y, 1.f, 5.f);
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
			if (ImGui::Button("Spawn")) {
				ImGui::SameLine();
				auto actor = std::make_shared<GenericActor>();
				actor->GenerateActorMesh("Polygon", Position);
				actor->SpriteTexture = Textures["ActorGuy"];
				actor->Sprite.setTexture(*actor->SpriteTexture);
				actor->Sprite.setScale(100 / 16.f, 100 / 16.f);
				actor->SetPosition(Position);

				SpawnActor(actor, Position);
			}

			ImGui::Unindent();
		}

		ImGui::Unindent();
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
