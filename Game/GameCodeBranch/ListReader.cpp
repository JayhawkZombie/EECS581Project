#include "ListReader.h"
ListReader::ListReader() : bestiarySize(0)
{}
ListReader::~ListReader()
{}
void ListReader::readFile(std::string fileName)
{

	std::ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::cout << "No file\n";
		return;
	}
	//assumes the file size is on top of the data
	file >> bestiarySize;
	
	monsterType* monsters = new monsterType[bestiarySize];
	monsterType* newMonster;
	
	int index = 0;
	std::string line;
	int intLine;

	//assumes completed monster descriptions.
	while (index < bestiarySize)
	{
		newMonster = new monsterType;
		file >> intLine;
		newMonster->setPrimary(intLine);

		file >> intLine;
		newMonster->setSecondary(intLine);

		file >> intLine;
		newMonster->setEvolutionStage(intLine);

		file >> intLine;
		newMonster->setEvolutionType(intLine);

		std::getline(file,line);
		std::getline(file,line);
		newMonster->setName(line);

		std::getline(file,line);
		newMonster->setDescription(line);

		monsters[index] = newMonster;
		index++;
	}
	file.close();
}
		
	//std::cout << monsters[357]->getDescription();
	/*
		file >> intLine;
		//newMonster->setSecondary(std::stoi(line));
		//newMonster->setEvolutionStage(std::stoi(line));
		//newMonster->setEvolutionType(std::stoi(line));
		//newMonster->setName(line);
		//newMonster->setDescription(line);
		bestiary[index] = newMonster;
		index++;
		if (index > 0)
			break;
	}

	file.close();
	std::ofstream data;
	data.open("hello.txt");
	for (int i = 0; i < 4; i++)
	{
		data << bestiary[i]->getPrimary();
	}
	data.close();
	//
	*/

