#include "../../Headers/Level/Level.h"
#include "..\..\Headers\Tiles\TMXMap.h"

namespace Engine
{

  Layer::Layer()
  {

  }

  Layer::~Layer()
  {

  }

  void Layer::TickUpdate(const double & delta)
  {
  }

  void Layer::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
    //Render the tiles first
    
  }

  void Layer::OnShutDown()
  {
  }

  void Layer::SerializeOut(std::ofstream & out)
  {
  }

  void Layer::SerializeIn(std::ifstream & in)
  {
  }

}
