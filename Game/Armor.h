#ifndef ARMOR_H
#define ARMOR_H

#include "Damage.h"
#include "RPGItem.h"
class Armor : public RPGItem
{
public:
  Armor();
  ~Armor();
  //getters
  Damage getDefense();
  int getType();

  //setters
  void setDefense(Damage defense);
  void setType(int type);

private:
  Damage m_defense;
  int m_type;
};

#endif