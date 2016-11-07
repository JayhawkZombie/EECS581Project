#ifndef ListReader_H
#define ListReader_H

#include "MonsterType.h"
#include "Armor.h"
#include "Weapon.h"
#include "Useable.h"
#include "Skill.h"

#include <ctype.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <regex>

class ListReader{
	public:
		ListReader();
		~ListReader();
		//reads in the file and fills in an array
		//returns the array
		MonsterType** readMonsters(std::string &fileName);
		Armor** readArmor(std::string &fileName);
		Weapon** readWeapons(std::string &fileName);		
		Useable** readUseables(std::string &fileName);
		Skill** readSkills(std::string &fileName);
		//returns the number on top of the file
		const int getNumMonsters();
		const int getNumArmor();
		const int getNumWeapons();
		const int getNumUseables();
		const int getNumSkills();

	private:
		int num_monsters;
		int num_armor;
		int num_weapons;
		int num_useables;
		int num_skills;
};
#endif
