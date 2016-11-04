#ifndef SKILLSET_H
#define SKILLSET_H

#include "Skill.h"
class SkillSet
{
public:
  SkillSet();
  ~SkillSet();
  void learnSkill[int index];
  bool knowSkill[int index];
private:
  bool skillArray[Skill::getSize()];

};


#endif