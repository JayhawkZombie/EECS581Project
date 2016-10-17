#include "Armor.h"



Armor::Armor()
{
  for (int i = 0; i < Damage::size; i++)
  {
    m_defense.content[i] = 0;
  }
  m_legs = false;
  m_torso = false;
  m_arms = false;
  m_head = false;
  m_ring = false;
}


Armor::~Armor()
{
}

Damage Armor::getDefense()
{
  return m_defense;
}

bool Armor::getLegs()
{
  return m_legs;
}

bool Armor::getTorso()
{
  return m_torso;
}

bool Armor::getArms()
{
  return m_arms;
}

bool Armor::getHead()
{
  return m_head;
}

bool Armor::getRing()
{
  return m_ring;
}
//setters
void Armor::setDefense(Damage defense)
{
  m_defense = defense;
}
void Armor::setLegs(bool legs)
{
  m_legs = legs;
}
void Armor::setTorso(bool torso)
{
  m_torso = torso;
}
void Armor::setArms(bool arms)
{
  m_arms = arms;
}
void Armor::setHead(bool head)
{
  m_head = head;
}
void Armor::setRing(bool ring)
{
  m_ring = ring;
}