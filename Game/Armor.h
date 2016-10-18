#ifndef ARMOR_H
#define ARMOR_H

#include "Damage.h"
class Armor
{
public:
  Armor();
  ~Armor();
  //getters
  Damage getDefense();
  bool getLegs();
  bool getTorso();
  bool getArms();
  bool getHead();
  bool getRing();

  //setters
  void setDefense(Damage defense);
  void setLegs(bool legs);
  void setTorso(bool torso);
  void setArms(bool arms);
  void setHead(bool head);
  void setRing(bool ring);

private:
  Damage m_defense;
  bool m_legs;
  bool m_torso;
  bool m_arms;
  bool m_head;
  bool m_ring;
};

#endif