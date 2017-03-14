#ifndef SKILL_H
#define SKILL_H
#include <string>
#include <map>

#include "Damage.h" //for member variable m_effect


#include "MonsterType.h"//for writing generic monster skills

//the following two lines destroy everything if they are uncommented.
//#include "ListReader.h"//for writing generic monster skills
//#include "GameMain.h"//for subelement names when writing monster skills
#include <math.h> //to use ceil when making damages

#include <ctype.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
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
  ///static const int m_size;
  //setters
  void setName(std::string name);
  void setFilePath(std::string filePath);
  void setDescription(std::string description);
  void setIsPhysical(bool isPhysical);
  void setIsMagical(bool isMagical);
  void setCastOnSelf(bool castOnSelf);
  void setCastOnSingle(bool castOnSingle);
  void setCastOnEnemy(bool castOnEnemy);
  void setMpCost(int mpCost);
  void setDamage(Damage damage);
	//		static Skill** readSkills(std::string fileName);
	static void makeMonsterSkills();

	//static std::map<int, std::map<int, std::string>> skillPrefixes();
	static std::map<int, std::map<int, std::string>> AnimationFilePaths();
	static std::map<int, std::string> skillDefinitions();
	static std::map<int, std::string> specificSkillNames();
	static std::map<int, std::map<int, std::string>> SubElementNames2();

private:
  std::string m_name;
  std::string m_filePath;
  std::string m_description;
  bool m_isPhysical;
  bool m_isMagical;
  bool m_castOnSelf;
  bool m_castOnSingle;
  bool m_castOnEnemy;
  int m_mpCost;
  Damage m_effect;
};

#endif