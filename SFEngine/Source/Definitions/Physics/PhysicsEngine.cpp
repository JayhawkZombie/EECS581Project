#include "../../../ThirdParty/PhysicsEngine.h"
#include "../../Headers/Exceptions/Exceptions.h"
namespace Engine
{
  template<typename T>
  void InsertIntoStream(const T &Data, std::stringstream &data_stream, bool newline = false)
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


  std::shared_ptr<PhysicsEngineBaseMeshType> BuildBallMesh(char BallType, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, unsigned int Radius, float Mass, float CoeffecientOfRest, const sf::Color & Color)
  {
    std::shared_ptr<PhysicsEngineBaseMeshType> Ball;

    std::stringstream data_stream;
    if (BallType != 'G' && BallType != 'B')
      throw PhysicsInterfaceException({ ExceptionCause::PhysicsInitInvalidData }, EXCEPTION_MESSAGE("BallType is invald"));

    try
    { 
      //Get the formatted data and try to use it to create a ball
      data_stream = GetFormattedBallConstructionData(BallType, InitialPosition, InitialVelocity, Radius, Mass, CoeffecientOfRest, Color);

      std::cerr << "--- Ball Mesh Data ---" << std::endl;
      std::cerr << data_stream.str() << std::endl;
      std::cerr << "----------------------" << std::endl;

      if (BallType == 'G')
        Ball = std::shared_ptr<PhysicsEngineBaseMeshType>(new ball_go(data_stream));
      else
        Ball = std::shared_ptr<PhysicsEngineBaseMeshType>(new ball(data_stream));

      return Ball;
    }
    catch (EngineRuntimeError &err)
    {
      err.AddCause({ ExceptionCause::PhysicsInitError });
      err.AddMessage(EXCEPTION_MESSAGE("Physics Error : Cannot construct ball"));

      throw;
    }
  }

  std::shared_ptr<PhysicsEngineBaseMeshType> BuildPolygonMesh(unsigned int num_sides, float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
  {
    std::shared_ptr<PhysicsEngineBaseMeshType> Poly;

    try
    {
      std::stringstream data = GetFormattedPolyConstructionData(num_sides, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);

      std::cerr << "--- Poly Mesh Data ---" << std::endl;
      std::cerr << data.str() << std::endl;
      std::cerr << "----------------------" << std::endl;

      Poly = std::shared_ptr<PhysicsEngineBaseMeshType>(new regPolygon(data));
      return Poly;
    }
    catch (EngineRuntimeError &err)
    {
      throw;
    }
  }

  std::shared_ptr<PhysicsEngineSegmentType> BuildSegmentMesh(char type, const sf::Vector2i & TopLeftCorner, const sf::Vector2i & BottomRightCorner, float radius)
  {
    std::shared_ptr<PhysicsEngineSegmentType> Segment;

    try
    {
      std::stringstream data = GetFormattedSegmentConstructionData(type, TopLeftCorner, BottomRightCorner, radius);
      Segment = std::shared_ptr<PhysicsEngineSegmentType>(new lineSeg(data));
      return Segment;
    }
    catch (EngineRuntimeError &err)
    {
      throw;
    }
  }

  std::stringstream GetFormattedBallConstructionData(char BallType, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, unsigned int Radius, float Mass, float CoeffecientOfRest, const sf::Color & Color)
  {
    std::stringstream data;

    try
    {
      //data << BallType << std::endl;
      //InsertIntoStream<char>(BallType, data, true);
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
      InsertIntoStream<char>(type, data);
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


  void UpdatePhysics(std::vector<std::shared_ptr<PhysicsEngineBaseMeshType>> &Meshes, std::vector<std::shared_ptr<PhysicsEngineSegmentType>> Segments, std::size_t Steps)
  {

    for (std::size_t _step = 0; _step < Steps; ++_step) {

      for (std::size_t i = 0; i < Meshes.size(); ++i) {
        Meshes[i]->update();
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

      for (std::size_t i = 0; i < Meshes.size() - 1; ++i) { 
        for (std::size_t j = i + 1; j < Meshes.size(); ++j) {
          Meshes[i]->hit(*Meshes[j]);
        }
      }


    } //for _step = 0; _step < Steps;...
  }

  void AssignBoundaries(float WindowHeight, float WindowWidth)
  {
    PhysicsEngineBaseMeshType::wdwH = WindowHeight;
    PhysicsEngineBaseMeshType::wdwW = WindowWidth;
    PhysicsEngineBaseMeshType::wdwCf = 0.f;
  }

  void SetGravity(vec2d *Gravity)
  {
    PhysicsEngineBaseMeshType::pGravity = Gravity;
  }

}