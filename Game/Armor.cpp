#include "Armor.h"



Armor::Armor()
{
  for (int i = 0; i < Damage::size; i++)
  {
    m_defense.content[i] = 0;
  }
  m_type = -1;
}


Armor::~Armor()
{
}

Damage Armor::getDefense()
{
  return m_defense;
}
int Armor::getType()
{
	return m_type;
}


//setters
void Armor::setDefense(Damage defense)
{
  m_defense = defense;
}
void Armor::setType(int type)
{
	m_type = type;
}
