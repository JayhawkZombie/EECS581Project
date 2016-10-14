#ifndef ListReader_H
#define ListReader_H

#include "monsterType.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>

class ListReader{
	public:
		ListReader();
		~ListReader();
		//reads in the file and fills in a monsters array
		//returns the monster array
		void readFile(std::string fileName);
		//travel through 
		//void travel();		
		//void printMenu(int menu);
		
		//
		//std::string getNames();
		
		

	private:
		int bestiarySize;
		//std::string selected;
		
		//std::string* monsterName[];
		//std::string* description[];
};
#endif
