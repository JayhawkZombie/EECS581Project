#include "Actor\Actor.h"
#include "Physics\Collider.h"
#include "chaiscript\chaiscript.hpp"
#include "chaiscript\chaiscript_defines.hpp"
#include "chaiscript\chaiscript_stdlib.hpp"

#include <memory>

namespace Engine
{


  GenericActor::GenericActor(const std::string &texfile, const std::string &texID)
  {

  }

  void GenericActor::BuildAnimations(const std::string & filename, const std::string & texturefile, GenericActor * Actor)
  {
    std::string animname = "";
    std::size_t numframes = 0;

    std::shared_ptr<sf::Texture> AnimTexture = std::make_shared<sf::Texture>();
    if (!AnimTexture->loadFromFile(texturefile)) {
      std::cerr << "Unable to load animation file: " << texturefile << std::endl;
      return;
    }

    int left{ 0 }, top{ 0 }, width{ 0 }, height{ 0 };
    sf::IntRect Frame = { 0,0,0,0 };
    std::ifstream in(filename);
    std::size_t frametime = 0;
    while (in >> animname) {
      in >> numframes >> frametime;
      auto anim = std::make_shared<Animation>();

      for (std::size_t i = 0; i < numframes; ++i) {
        in >> left >> top >> width >> height;
        Frame.left = left; Frame.top = top; Frame.width = width; Frame.height = height;
        anim->AddFrame(Frame);
        anim->SetFrameTime(frametime);
        Actor->AddAnimation(animname, anim);
      }

    }
    in.close();
  }

  void GenericActor::BindScriptMethods(chaiscript::ModulePtr mptr)
  {
    //UGHSDJLGHSD LJHFSDLFHS DLFH SDF
    //It's SO UGLY!
    chaiscript::utility::add_class<Engine::GenericActor>(*mptr, "GenericActor",
    { chaiscript::constructor<Engine::GenericActor()>() },
    {
      { chaiscript::fun(static_cast<void(GenericActor::*)(const std::string &)>(&GenericActor::SetID)), "SetID" },
      { chaiscript::fun(static_cast<std::string(GenericActor::*)(void) const>(&GenericActor::GetID)), "GetID" },
      { chaiscript::fun(static_cast<const sf::Vector2f &(GenericActor::*)(void) const>(&GenericActor::GetActorPosition)), "GetPosition" },
      { chaiscript::fun(static_cast<void(GenericActor::*)(const sf::Vector2f &)>(&GenericActor::SetActorPosition)), "SetPosition" },
      { chaiscript::fun(static_cast<void(GenericActor::*)(float, float)>(&GenericActor::SetActorPosition)), "SetPosition" },
      { chaiscript::fun(static_cast<void(GenericActor::*)(const std::string &)>(&GenericActor::SetAnimation)), "SetAnimation" },
      { chaiscript::fun(static_cast<void(GenericActor::*)(const sf::Vector2f &)>(&GenericActor::SetActorAcceleration)), "SetAcceleration" },
      { chaiscript::fun(static_cast<void(GenericActor::*)(const sf::Vector2f &)>(&GenericActor::SetActorVelocity)), "SetVelocity" },
      { chaiscript::fun(static_cast<void(GenericActor::*)(const double &)>(&GenericActor::TickUpdate)), "TickUpdate" },
      { chaiscript::fun(static_cast<void(GenericActor::*)(const sf::Vector2f &)>(&GenericActor::MoveObject)), "MoveObject" }
    }
    );
  }

  GenericActor::GenericActor()
  {
    try
    {
      ItemID = std::to_string(GenerateID());
      ItemID = "Player" + ItemID;
    }
    catch (std::exception &err)
    {
      std::cerr << "Exception in GenericActor constructor" << std::endl;

      throw err;
    }
  }

  GenericActor::GenericActor(const GenericActor & Copy)
    : LevelObject()
  {
  }

  void GenericActor::AddAnimation(const std::string &ID, std::shared_ptr<Animation> info)
  {

  }

  void GenericActor::SetAnimation(const std::string & ID)
  {

  }

  void GenericActor::__HandleKeyPress(const sf::Keyboard::Key &key)
  {

  }

  void GenericActor::ReceiveSprite(const std::string &ID, std::shared_ptr<sf::Texture> tex)
  {

  }

  GenericActor::~GenericActor()
  {

  }

  void GenericActor::SerializeOut(std::ofstream &out)
  {

  }

  void GenericActor::SerializeIn(std::ifstream &in)
  {

  }

  void GenericActor::OnShutDown()
  {
	  
  }

  void GenericActor::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
    if (CurrentAnimation)
      CurrentAnimation->Render(Target);
  }

  std::shared_ptr<BaseEngineInterface> GenericActor::Clone() const
  {
    auto Actor = std::make_shared<GenericActor>(*this);

    return Actor;
  }

  void GenericActor::TickUpdate(const double &delta)
  {
    try
    {
      //ScriptEngine->eval(ItemID + ".Update()");
    }
    catch (chaiscript::exception::eval_error &everr)
    {
      std::cerr << "Script eval error: " << everr.what() << std::endl;
    }
  }

  void GenericActor::SetCollisionHandleCallback(std::function<void(LevelObject*)> Callback)
  {
    m_HandleCollisionWithObject = Callback;
  }

  void GenericActor::HandleCollisionWithCollider(SPtrShared<Collider2D> Collider)
  {
    auto Object = Collider->GetObjectPtr();
  }

  void GenericActor::HandleCollisionWithObject(LevelObject * Object)
  {
  }

  void GenericActor::HandleInputEvent(const UserEvent & evnt)
  {
  }

  bool GenericActor::WantsInputEvent(const Events &evnt) const
  {
    return false;
  }

  void GenericActor::SetActorPosition(const sf::Vector2f &pos)
  {
	  Sprite.setPosition(pos);

	  if (m_Colliders.size() > 0) {
		  auto mesh = m_Colliders.front()->GetMesh().lock();
		  if (mesh)
			  mesh->setPosition(::vec2d(pos.x, pos.y));
	  }
  }

  void GenericActor::SetActorPosition(float x, float y)
  {
    SetActorPosition({ x, y });
  }

  void GenericActor::SetActorSize(const sf::Vector2f &size)
  {
    Size = size;

  }

  void GenericActor::CenterAroundCollider(std::shared_ptr<Collider2D> Collider)
  {
    auto ptr = Collider->GetMesh().lock();
    if (ptr) {
      auto vec = ptr->pos;
      auto siz = ptr->siz;

      Sprite.setPosition({ vec.x, vec.y });
      //diff in size
      sf::Vector2f sizeDiff = Size - sf::Vector2f(siz.x, siz.y);
      sizeDiff /= 2.f;

      Sprite.move(sizeDiff);
    }
  }

  void GenericActor::SetActorVelocity(const sf::Vector2f &vel)
  {
    Velocity = vel;
  }

  void GenericActor::SetActorAcceleration(const sf::Vector2f &acc)
  {
    Acceleration = acc;
  }

  void GenericActor::GenerateActorMesh(const std::string & meshtype, const sf::Vector2f & pos, float mass, float coeffOfRest, unsigned int num_sides, float init_rot)
  {
	  m_Colliders.push_back(Collider2D::CreatePolygonMesh(num_sides, std::max(Size.x, Size.y) / 2.f, init_rot, pos, { 0.f, 0.f }, mass, coeffOfRest, sf::Color::White));
	  MeshRadius = std::max(Size.x, Size.y) / 2.f;
  }

  void GenericActor::MoveObject(const sf::Vector2f & delta)
  {
    Move(delta);
  }

  const sf::Vector2f& GenericActor::GetActorPosition() const
  {
    return Position;
  }

  const sf::Vector2f& GenericActor::GetActorSize() const
  {
    return Size;
  }

  const sf::Vector2f& GenericActor::GetActorVelocity() const
  {
    return Velocity;
  }

  const sf::Vector2f& GenericActor::GetActorAcceleration() const
  {
    return Acceleration;
  }
}
