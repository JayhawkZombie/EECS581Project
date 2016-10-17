#ifndef WEAPON_H
#define WEAPON_H
#include "RPGItem.h"
#include "Damage.h"
class Weapon : public RPGItem
{
public:
  Weapon();
  ~Weapon();
  
  //getters and setters
  Damage getAddedDamage();
  bool getRightHand();
  bool getLeftHand();
  void setAddedDamage(Damage addedDamage);
  void setRightHand(bool rightHand);
  void setLeftHand(bool leftHand);

private:
  Damage m_addedDamage;
  bool m_rightHand;
  bool m_leftHand;
};

#endif;