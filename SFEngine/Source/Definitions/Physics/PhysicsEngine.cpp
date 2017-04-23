#include "Exceptions\Exceptions.h"
#include "Physics\Collider.h"
#include "PhysicsEngine.h"
#include "Level\LevelObject.h"

namespace
{
  vec2d gravity;
}

namespace Engine
{

  template<typename T>
  inline void InsertIntoStream(const T &Data, std::stringstream &data_stream, bool newline = false)
  {
    if (data_stream.fail())
      throw StreamException({ ExceptionCause::StreamFailure }, EXCEPTION_MESSAGE("StringStream is in a fail state"));

    static std::string str_data = " ";

    str_data = std::to_string(Data);

    data_stream << str_data;

    if (newline)
      data_stream << "\n";
    else
      data_stream << " ";
  }


  BaseMeshPtr BuildBallMesh(char BallType, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, unsigned int Radius, float Mass, float CoeffecientOfRest, const sf::Color & Color)
  {
    BaseMeshPtr Ball;

    std::stringstream data_stream;
    if (BallType != 'G' && BallType != 'B')
      throw PhysicsInterfaceException({ ExceptionCause::PhysicsInitInvalidData }, EXCEPTION_MESSAGE("BallType is invald"));

    try
    {
      //Get the formatted data and try to use it to create a ball
      data_stream = GetFormattedBallConstructionData(BallType, InitialPosition, InitialVelocity, Radius, Mass, CoeffecientOfRest, Color);

      if (BallType == 'G')
        return (std::make_shared<ball_go>(data_stream));
      else
        return (std::make_shared<ball>(data_stream));
    }
    catch (EngineRuntimeError &err)
    {
      err.AddCause({ ExceptionCause::PhysicsInitError });
      err.AddMessage(EXCEPTION_MESSAGE("Physics Error : Cannot construct ball"));

      throw;
    }
  }

  BaseMeshPtr BuildPolygonMesh(unsigned int num_sides, float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
  {
    try
    {
      std::stringstream data = GetFormattedPolyConstructionData(num_sides, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
      return (std::make_shared<regPolygon>(data));
    }
    catch (EngineRuntimeError &err)
    {
      err.AddCause(ExceptionCause::PhysicsInitError);
      err.AddMessage(EXCEPTION_MESSAGE("Physics error : Cannot construct poly"));
      throw;
    }
  }

  SegmentPtr BuildSegmentMesh(char type, const sf::Vector2i & TopLeftCorner, const sf::Vector2i & BottomRightCorner, float radius)
  {
    try
    {
      std::stringstream data = GetFormattedSegmentConstructionData(type, TopLeftCorner, BottomRightCorner, radius);
      return (std::make_shared<lineSeg>(data));
    }
    catch (EngineRuntimeError &err)
    {
      err.AddCause(ExceptionCause::PhysicsInitError);
      err.AddMessage(EXCEPTION_MESSAGE("Physics error : Cannot construct segment"));
      throw;
    }
  }
  WaveSegmentPtr BuildWaveSegment(char type, const sf::Vector2i & TopLeftCorner, const sf::Vector2i & BottomRightCorner, float radius, bool IsHard, unsigned int NumWavePts, float ampRight, float waveLenRight, float rFreqRight, float ampLeft, float waveLenLeft, float rFreqLeft, float elev, float airDen, float depth, float fluidDen)
  {
    try
    {
      std::stringstream data = GetFormattedWaveSegmentConstructionData(type, TopLeftCorner, BottomRightCorner, radius, IsHard, NumWavePts, ampRight, waveLenRight, rFreqRight, ampLeft, waveLenLeft, rFreqLeft, elev, airDen, depth, fluidDen);
      return (std::make_shared<waveSeg>(data));
    }
    catch (EngineRuntimeError &err)
    {
      err.AddCause(ExceptionCause::PhysicsInitError);
      err.AddMessage(EXCEPTION_MESSAGE("Physics error : Cannot construct wave"));
      throw;
    }
  }
  std::stringstream GetFormattedWaveSegmentConstructionData(char type, const sf::Vector2i &TopLeftCorner, const sf::Vector2i &BottomRightCorner, float radius, bool IsHard,
                                                            unsigned int NumWavePts, float ampRight, float waveLenRight, float rFreqRight,
                                                            float ampLeft, float waveLenLeft, float rFreqLeft,
                                                            float elev, float airDen, float depth, float fluidDen)
  {
    std::stringstream data;

    try
    {
      std::cerr << "Wave construction data: " << std::endl;
      std::cerr << type << " " << (IsHard ? 1 : 0) << " " << TopLeftCorner.x << " " << TopLeftCorner.y << " " << BottomRightCorner.x << " " << BottomRightCorner.y << std::endl;
      std::cerr << NumWavePts << " " << ampRight << " " << waveLenRight << " " << rFreqRight << " " << ampLeft << " " << waveLenLeft << " " << rFreqLeft << " " << std::endl;
      std::cerr << elev << " " << airDen << " " << depth << " " << fluidDen << std::endl;

      InsertIntoStream<int>(TopLeftCorner.x, data);
      InsertIntoStream<int>(TopLeftCorner.y, data);
      InsertIntoStream<int>(BottomRightCorner.x, data);
      InsertIntoStream<int>(BottomRightCorner.y, data);
      InsertIntoStream<unsigned int>(NumWavePts, data);
      InsertIntoStream<float>(ampRight, data);
      InsertIntoStream<float>(waveLenRight, data);
      InsertIntoStream<float>(rFreqRight, data);
      InsertIntoStream<float>(ampLeft, data);
      InsertIntoStream<float>(waveLenLeft, data);
      InsertIntoStream<float>(rFreqLeft, data, true);
      InsertIntoStream<float>(elev, data);
      InsertIntoStream<float>(airDen, data);
      InsertIntoStream<float>(depth, data);
      InsertIntoStream<float>(fluidDen, data);

      std::cerr << "Formatted data: \n*********************************\n" << data.str() << "\n****************************************\n" << std::endl;
    }
    catch (StreamException &err)
    {
      std::cerr << "StreamExcetion: " << err.what() << std::endl;
    }
    catch (FormattingError &ferr)
    {
      std::cerr << "Formatting Error: " << ferr.what() << std::endl;
    }

    return data;
  }


  std::stringstream GetFormattedBallConstructionData(char BallType, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, unsigned int Radius, float Mass, float CoeffecientOfRest, const sf::Color & Color)
  {
    std::stringstream data;

    try
    {
      InsertIntoStream<int>((int)(std::floor(InitialPosition.x)), data);
      InsertIntoStream<int>((int)(std::floor(InitialPosition.y)), data);
      InsertIntoStream<int>((int)(std::floor(InitialVelocity.x)), data);
      InsertIntoStream<int>((int)(std::floor(InitialVelocity.y)), data, true);
      InsertIntoStream<unsigned int>(Radius, data, true);
      InsertIntoStream<float>(Mass, data);
      InsertIntoStream<float>(CoeffecientOfRest, data, true);
      InsertIntoStream<unsigned char>(Color.r, data);
      InsertIntoStream<unsigned char>(Color.g, data);
      InsertIntoStream<unsigned char>(Color.b, data, true);
    }
    catch (StreamException &err)
    {
      std::cerr << "StreamExcetion: " << err.what() << std::endl;
    }
    catch (FormattingError &ferr)
    {
      std::cerr << "Formatting Error: " << ferr.what() << std::endl;
    }

    return data;
  }

  std::stringstream GetFormattedPolyConstructionData(unsigned int num_sides, float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
  {
    std::stringstream data;

    try
    {
      InsertIntoStream<unsigned int>(num_sides, data);
      InsertIntoStream<float>(radius, data);
      InsertIntoStream<float>(init_rotation, data, true);
      InsertIntoStream<int>((int)(std::floor(InitialPosition.x)), data);
      InsertIntoStream<int>((int)(std::floor(InitialPosition.y)), data);
      InsertIntoStream<int>((int)(std::floor(InitialVelocity.x)), data);
      InsertIntoStream<int>((int)(std::floor(InitialVelocity.y)), data, true);
      InsertIntoStream<float>(mass, data);
      InsertIntoStream<float>(CoeffOfRest, data, true);
      InsertIntoStream<unsigned char>(Color.r, data);
      InsertIntoStream<unsigned char>(Color.g, data);
      InsertIntoStream<unsigned char>(Color.b, data, true);
    }
    catch (StreamException &serr)
    {
      std::cerr << "StreamExcetion: " << serr.what() << std::endl;
    }
    catch (FormattingError &ferr)
    {
      std::cerr << "Formatting Error: " << ferr.what() << std::endl;
    }

    return data;
  }

  std::stringstream GetFormattedSegmentConstructionData(char type, const sf::Vector2i & TopLeftCorner, const sf::Vector2i & BottomRightCorner, float radius)
  {
    std::stringstream data;

    try
    {
      InsertIntoStream<int>(TopLeftCorner.x, data);
      InsertIntoStream<int>(TopLeftCorner.y, data);
      InsertIntoStream<int>(BottomRightCorner.x, data);
      InsertIntoStream<int>(BottomRightCorner.y, data);
      if (type == 'A')
        InsertIntoStream<float>(radius, data, true);
      else
        InsertIntoStream<char>('\n', data);
    }
    catch (StreamException &serr)
    {
      std::cerr << "StreamExcetion: " << serr.what() << std::endl;
    }
    catch (FormattingError &ferr)
    {
      std::cerr << "Formatting Error: " << ferr.what() << std::endl;
    }

    return data;
  }


  void UpdatePhysics(std::vector<PhysicsEngineBaseMeshType *> &Meshes, std::vector<PhysicsEngineSegmentType *> Segments, std::size_t Steps)
  {

    for (std::size_t _step = 0; _step < Steps; ++_step) {

      for (std::size_t i = 0; i < Meshes.size(); ++i) {
        Meshes[i]->update(gravity);
      }

      //Update segments
      for (auto & segPtr : Segments) {
        segPtr->update();
      }

      //Do collision testing and response
      for (auto & segPtr : Segments) {
        for (auto & meshPtr : Meshes) {
          segPtr->hit(*meshPtr);
        }
      }

      for (std::size_t i = 0; i + 1 < Meshes.size(); ++i) {
        for (std::size_t j = i + 1; j < Meshes.size(); ++j) {
          Meshes[i]->hit(*Meshes[j]);
        }
      }


    } //for _step = 0; _step < Steps;...
  }

  inline bool IsColliderAndMeshGood(std::weak_ptr<PhysicsEngineBaseMeshType> Mesh, std::shared_ptr<Engine::Collider2D> Collider) {
    return (
      Mesh.lock() &&
      (Collider->IsActive()
      && Collider->IsAwake()
      && Collider->IsEnabled())
      );
  }

  inline bool IsColliderGood(std::shared_ptr<Engine::Collider2D> Collider) {
    return (Collider->IsActive()
            && Collider->IsAwake()
            && Collider->IsEnabled()
            );
  }

  inline void DoExtraSegmentChecks(std::shared_ptr<Collider2D> Collider, PhysicsEngineSegmentType *Segment) {
    sf::FloatRect Bounds = Collider->GetGlobalBounds();

    static sf::Vector2f Move{ 0, 0 };
    static float right = 0.f;
    static float left = 0.f;
    static float top = 0.f;
    static float bottom = 0.f;
    static ::vec2d SegPos{ 0.f, 0.f };

    right = Bounds.left + Bounds.width;
    left = Bounds.left;
    top = Bounds.top;
    bottom = Bounds.top + Bounds.height;
    SegPos = Segment->pos;
    Move = { 0, 0 };
    /*
     * Check to see if the segment is a little too much into the left of the collider
     **/
    if (left <= SegPos.x && right > SegPos.x)
      Move.x = (SegPos.x - left) + 0.1f;

    /*
    * Check to see if the segment is a little too much into the right of the collider
    **/
    else if (SegPos.x <= right && left < SegPos.x)
      Move.x = (SegPos.x - right) - 0.1f;

    /*
    * Check to see if the segment is a little too much into the top of the collider
    **/
    if (SegPos.y >= top && bottom > SegPos.y)
      Move.y = (SegPos.y - top) + 0.1f;

    /*
    * Check to see if the segment is a little too much into the bottom of the collider
    **/
    else if (bottom >= SegPos.y && top < SegPos.y)
      Move.y = (SegPos.y - bottom) - 0.1f;
      
    auto object = Collider->GetObjectPtr();

    if (object)
      object->MoveObject(Move);
  }

  void UpdatePhysics(std::vector<std::shared_ptr<Engine::Collider2D>> Colliders, std::vector<PhysicsEngineSegmentType *> Segments, std::size_t steps)
  {
    for (std::size_t _step = 0; _step < steps; ++_step) {

      for (auto & collider : Colliders) {
        collider->Update(gravity);
      }

      for (auto & seg : Segments)
        seg->update();

      for (auto & collider : Colliders) {

        auto mesh = collider->GetMesh();
        if (!IsColliderAndMeshGood(mesh, collider))
          continue;

        for (auto & seg : Segments) {
          if (seg->hit(*mesh.lock()))
            collider->HandleCollisionWithSegment(seg);
          
          /*
          * We will do some extra checks here because the physics engine has a significant flaw when colliders are
          * aligned with segments
          **/
          DoExtraSegmentChecks(collider, seg);
        }

      }

      //for (auto & seg : Segments) {
      //  for (auto & coll : Colliders) {
      //    auto mesh = coll->GetMesh();
      //    if (mesh.lock() && seg->hit(*mesh.lock())) {
      //      //Do something here
      //      coll->HandleCollisionWithSegment(seg);
      //      /*
      //       * We will do some extra checks here because the physics engine has a significant flaw when colliders are
      //       * aligned with segments
      //       **/

      //    }
      //  }
      //}

      for (std::size_t i = 0; i < Colliders.size(); ++i) {
        for (std::size_t j = 0; j < Colliders.size(); ++j) {
          auto m_1 = Colliders[i]->GetMesh().lock();
          auto m_2 = Colliders[j]->GetMesh().lock();

          if (Colliders[i]->IsAwake() && Colliders[j]->IsAwake()) {
            if (m_1 && m_2 && m_1->hit(*m_2)) {
                Colliders[i]->HandleCollision(Colliders[j]);
                Colliders[j]->HandleCollision(Colliders[i]);
              }
          }

        }
      }

    }
  }

  void AssignBoundaries(float WindowHeight, float WindowWidth)
  {
    PhysicsEngineBaseMeshType::wdwH = WindowHeight;
    PhysicsEngineBaseMeshType::wdwW = WindowWidth;
    PhysicsEngineBaseMeshType::wdwCf = 0.f;
  }

  void SetGravity(::vec2d *Gravity)
  {
    gravity = *Gravity;
  }

}