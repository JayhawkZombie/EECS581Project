#include "../../Headers/Level/BasicLevel.h"

#include "../../Headers/Level/LevelObject.h"
#include "../../Headers/Physics/Collider.h"

namespace Engine
{

  BasicLevel::BasicLevel(const sf::Vector2u &LevelSize, const sf::FloatRect &DefaultView, bool showlines, const sf::Vector2f &GridSpacing)
    : LightTexture(std::make_shared<sf::RenderTexture>()),
    SceneBlendTexture(std::make_shared<sf::RenderTexture>()),
    ShowGridLines(showlines), Size(LevelSize), GridBlockSize(GridSpacing), CurrentView(DefaultView),
    Gravity(new ::vec2d)
  {

  }

  BasicLevel::~BasicLevel()
  {
    if (Gravity)
      delete Gravity;
  }

  void BasicLevel::TickUpdate(const double & delta)
  {
    static double cumulative = 0.f;
    cumulative += delta;

    static hres_time_point FrameStart = hres_clock::now();

    double Tick = delta;

    for (auto & obj : Objects) {
      Tick += std::chrono::duration<double, std::milli>(hres_clock::now() - FrameStart).count();
      obj->TickUpdate(Tick);
    }

    if (cumulative > updateInterval) {

      if (DoUpdatePhysics && (LevelObjects.size() > 0 || Segments.size() > 0)) {
        UpdateObjectPhysics();

        for (auto & obj : LevelObjects) {
          obj.second->PhysicsUpdate();
        }
      }

      cumulative = 0.f;
    }

  }

  void BasicLevel::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
    //This function shouldn't ever be called
  }

  void BasicLevel::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
  {
    SceneBlendTexture->clear(sf::Color::Transparent);

    if (ShowGridLines) {
      for (auto & arr : GridLines)
        Texture->draw(arr);
    }

    for (auto & obj : LevelObjects)
      Texture->draw(obj.second->Sprite);

    //If we are using the editor, draw the meshes too
    //Make this configurable later
#ifdef WITH_EDITOR
    for (auto & MeshCollection : LevelObjectMeshes)
      for (auto & Mesh : MeshCollection.second)
        if (Mesh->GetMesh().lock())
          Mesh->GetMesh().lock()->draw(*Texture);

    for (auto & seg : Segments)
      seg->draw(*Texture);
#endif
  }

  void BasicLevel::OnShutDown()
  {
  }

  void BasicLevel::SerializeOut(std::ofstream & out)
  {
  }

  void BasicLevel::SerializeIn(std::ifstream & in)
  {
  }

  void BasicLevel::HandleInputEvent(const UserEvent & evnt)
  {
  }

  void BasicLevel::HandleKeyPress(const sf::Keyboard::Key & key)
  {
  }

  void BasicLevel::HandleKeyRelease(const sf::Keyboard::Key & key)
  {
  }

  void BasicLevel::HandleWindowResized()
  {
  }

  void BasicLevel::LoadLevel(const std::string & lvlfile)
  {
  }

  void BasicLevel::OnBegin()
  {
  }

  void BasicLevel::OnEnd()
  {
  }

  void BasicLevel::LoadFromFile(const std::string & file)
  {
  }

  void BasicLevel::LoadAssets(const Json::Value & value)
  {
  }

  void BasicLevel::LoadAudio(const Json::Value & value)
  {
  }

  void BasicLevel::LoadTextures(const Json::Value & value)
  {
  }

  void BasicLevel::LoadTileSheets(const Json::Value & value)
  {
  }

  void BasicLevel::LoadSheet(const Json::Value & value)
  {
  }

  void BasicLevel::LoadAnimations(const Json::Value & value)
  {
  }

  void BasicLevel::UpdateObjectPhysics()
  {
  }

}
