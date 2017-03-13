#ifndef SKILL_H
#define SKILL_H
#include <string>
#include "Damage.h" //for member variable m_effect
#include "MonsterType.h"//for writing generic monster skills
#include "ListReader.h"//for writing generic monster skills
#include "GameMain.h"//for subelement names when writing monster skills

//Libraries for reading/writing text files
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <regex>
#include <memory>//smart pointers

#include <map>//for auto generation of skills

class Skill
{
public:
  //constructors
  Skill();
  ~Skill();

  //getters
  std::string getName();
  std::string getFilePath();
  std::string getDescription();
  bool getIsPhysical();
  bool getIsMagical();
  bool getCastOnSelf();
  bool getCastOnSingle();
  bool getCastOnEnemy();
  int getMpCost();
  Damage getDamage();

  //static const int m_size;
  
  //setters
  void setName(std::string name);
  void setAnimationFilePath(std::string filePath);
  void setDescription(std::string description);
  void setIsPhysical(bool isPhysical);
  void setIsMagical(bool isMagical);
  void setCastOnSelf(bool castOnSelf);
  void setCastOnSingle(bool castOnSingle);
  void setCastOnEnemy(bool castOnEnemy);
  void setMpCost(int mpCost);
  void setDamage(Damage damage);

  static Skill** readSkills(std::string fileName);
  static void makeMonsterSkills();

	//static std::map<int, std::map<int, std::string>> skillPrefixes();
	static std::map<int, std::map<int, std::string>> AnimationFilePaths();
	static std::map<int, std::string> skillDefinitions();

private:
	int m_skillId;
  std::string m_name;
  std::string m_animationFilePath;
  std::string m_description;
  bool m_isPhysical;
  bool m_isMagical;
  bool m_castOnSelf;
  bool m_castOnSingle;
  bool m_castOnEnemy;
  int m_mpCost;
  Damage m_effect;

  static Skill** skills;



};

#endif