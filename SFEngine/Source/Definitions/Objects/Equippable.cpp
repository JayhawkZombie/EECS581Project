#include "Objects\Equippable.h"

namespace Engine
{

  EquippableBase::EquippableBase()
    : BaseEngineInterface()
  {
  }

  EquippableBase::~EquippableBase()
  {
  }

  void EquippableBase::OnEquipped(LevelObject * EquippedOn)
  {
  }

  void EquippableBase::OnUnequipped(LevelObject * EquippedOff)
  {
  }

  std::string EquippableBase::GetEquipType() const
  {
    return m_EquipType;
  }

  void EquippableBase::SetEquipType(const std::string & Type)
  {
    m_EquipType = Type;
  }

}
