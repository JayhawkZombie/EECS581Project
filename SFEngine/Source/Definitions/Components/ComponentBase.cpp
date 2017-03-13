#include "../../Headers/Components/ComponentBase.h"

namespace Engine
{

  ComponentBase::ComponentBase()
  {
  }

  ComponentBase::~ComponentBase()
  {
  }

  std::uint32_t ComponentBase::GetID() const
  {
    return ComponentID;
  }

}
