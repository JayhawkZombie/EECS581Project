#ifndef ListReader_H
#define ListReader_H

#include "MonsterType.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>

class ListReader{
	public:
		ListReader();
		~ListReader();
		//reads in the file and fills in a monsters array
		//returns the monster array
		MonsterType** readMonsters(std::string fileName);
		//return bestiary size
		const int getNumMonsters();
		const int getNumArmor();
		const int getNumWeapons();
		const int getNumUsables();
		
		
		

	private:
		int num_monsters;
		int num_armor;
		int num_usables;
		int num_weapons;

};
#endif
