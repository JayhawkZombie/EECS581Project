#include "SkillSet.h"



SkillSet::SkillSet()
{
  for (int i = 0; i < Skill::getSize(); i++)
  {
    skillArray[0] = false;
  }
}


SkillSet::~SkillSet()
{
}

void SkillSet::learnSkill(int index)
{
  if (index > Skill::getSize||index<0)
  {
    return;//ignore case-outside bounds
  }
  skillArray[index] = true;
}

bool SkillSet::knowSkill(int index)
{
  if (index > Skill::getSize || index<0)
  {
    return;//ignore case-outside bounds
  }
  return skillArray[index];
}