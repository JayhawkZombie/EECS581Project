#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H
#include "HumanActor.h"
class MainCharacter : public HumanActor
{
public:
  MainCharacter();
  ~MainCharacter();
  void IncrementAffinity(int index, int value);
  int getAffinity(int index);
  void printAffinities();

private:
  int m_affinity[6];
};

#endif