#include "ListReader.h"
ListReader::ListReader() : num_monsters(0), num_armor(0), num_usables(0), num_weapons(0)
{}
ListReader::~ListReader()
{}
MonsterType** ListReader::readMonsters(std::string fileName)
{
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::cout << "No file\n";
		return NULL;
	}
	//assumes the file size is on top of the data
	file >> num_monsters;
	
	MonsterType** monsters = new MonsterType*[num_monsters];
	MonsterType* newMonster;
	
	int index = 0;
	std::string line;
	int intLine;

	//assumes completed monster descriptions.
	while (index < num_monsters)
	{
		newMonster = new MonsterType;
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
	return monsters;
}
const int ListReader::getNumMonsters()
{
	return num_monsters;
}	
const int ListReader::getNumArmor()
{
	return num_armor;
}
const int ListReader::getNumWeapons()
{
	return num_weapons;
}
const int ListReader::getNumUsables()
{
	return num_usables;
}

