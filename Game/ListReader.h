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
		const int bestiarySize();
		
		
		

	private:
		int bestiarySize;
		
};
#endif
