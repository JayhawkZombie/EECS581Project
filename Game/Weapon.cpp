#include "Weapon.h"



Weapon::Weapon()
{
  for (int i = 0; i < Damage::size; i++)
  {
    m_addedDamage.content[i] = 0;
  }
  m_rightHand = true;
  m_leftHand = false;
}


Weapon::~Weapon()
{
}

Damage Weapon::getAddedDamage()
{
  return m_addedDamage;
}

bool Weapon::getRightHand()
{
  return m_rightHand;
}

bool Weapon::getLeftHand()
{
  return m_leftHand;
}

void Weapon::setAddedDamage(Damage addedDamage)
{
  m_addedDamage = addedDamage;
}

void Weapon::setRightHand(bool rightHand)
{
  m_rightHand = rightHand;
}

void Weapon::setLeftHand(bool leftHand)
{
  m_leftHand = leftHand;
}
