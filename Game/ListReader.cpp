#include "ListReader.h"
ListReader::ListReader() : num_monsters(0), num_armor(0), num_weapons(0), num_useables(0)//, monsters(NULL), armor(NULL), weapons(NULL), useables(NULL)
{}
ListReader::~ListReader()
{
	/*if (monsters != NULL)
	{
		for (int i = 0; i < num_monsters; i++)
		{
			delete monsters[i];
		}
		delete monsters;
		monsters = NULL;
	}
	//repeat for rest
		*/
}
//shared_ptr<MonsterType> ListReader::readMonsters(std::string &fileName)
//	shared_ptr<MonsterType*> monsters(new MonsterType*)[num_monsters];
MonsterType** ListReader::readMonsters(std::string &fileName)
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
	int intVal;

	//assumes completed monster descriptions.
	while (index < num_monsters)
	{
		newMonster = new MonsterType;
		std::getline(file,line);
		std::getline(file,line);
		std::getline(file,line);
		newMonster->setName(line);
		
		std::getline(file,line);
		newMonster->setDescription(line);
		
		file >> intVal;
		newMonster->setPrimary(intVal);

		file >> intVal;
		newMonster->setSecondary(intVal);

		file >> intVal;
		newMonster->setEvolutionStage(intVal);

		file >> intVal;
		newMonster->setEvolutionType(intVal);

		std::getline(file,line);
		std::getline(file,line);
		newMonster->setTexture(line);

		std::getline(file,line);
		//newMonster->setPhysicalEvolution(line);
		std::getline(file,line);
		//newMonster->setBalancedEvolution(line);
		std::getline(file,line);
		//newMonster->setMagicalEvolution(line);
		
		monsters[index] = newMonster;
		index++;
	}
	file.close();
	return monsters;
}
Armor** ListReader::readArmor(std::string &fileName)
{
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::cout << "No file\n";
		return NULL;
	}
	//assumes the file size is on top of the data
	file >> num_armor;
	
	Armor** armor = new Armor*[num_armor];
	Armor* newArmor;
	
	Damage* damage;
	int index = 0;
	std::string line;
	int intIndex;
	int intVal;
	
	//accounting for whitespace on the end of the line
	std::regex integers("[[:digit:]]+");
	std::regex truespace("(true)");

	std::getline(file,line);
	while (index < num_armor)
	{
		newArmor = new Armor;

		std::getline(file,line);
		newArmor->setName(line);

		file >> intVal;
		newArmor->setValue(intVal);

		std::getline(file,line);
		std::getline(file,line);
		newArmor->setDescription(line);

		std::getline(file,line);
		newArmor->setTexture(line);
		
		std::getline(file,line);
		damage = new Damage;
		while ( std::regex_search (line,integers) )
		{	
			intIndex = stoi (line);
			std::getline(file,line);
			intVal = stoi (line);
			damage->setValue(intIndex,intVal);

			std::getline(file,line);
		}
		newArmor->setDefense(*damage);

		if ( std::regex_search (line,truespace) )
		{
			newArmor->setLegs(true);
		}
		std::getline(file,line);
		if ( std::regex_search (line,truespace) )
		{
			newArmor->setTorso(true);
		}
		std::getline(file,line);
		if ( std::regex_search (line,truespace) )
		{
			newArmor->setArms(true);
		}
		std::getline(file,line);
		if ( std::regex_search (line,truespace) )
		{
			newArmor->setHead(true);
		}
		std::getline(file,line);
		if ( std::regex_search (line,truespace) )
		{
			newArmor->setRing(true);
		}
		armor[index] = newArmor;
		index++;
	}

	file.close();
	return armor;	
}
Weapon** ListReader::readWeapons(std::string &fileName)
{
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::cout << "No file\n";
		return NULL;
	}
	//assumes the file size is on top of the data
	file >> num_weapons;
	
	Weapon** weapons = new Weapon*[num_weapons];
	Weapon* newWeapon;
	Damage* damage;

	int index = 0;
	std::string line;
	int intVal;
	int intIndex;

	//accounting for whitespace on the end of the line
	std::regex integers("[[:digit:]]+");
	std::regex truespace("(true)");

	std::getline(file,line);
	while (index < num_weapons)
	{
		newWeapon = new Weapon;

		std::getline(file,line);
		newWeapon->setName(line);

		file >> intVal;
		newWeapon->setValue(intVal);

		std::getline(file,line);	
		std::getline(file,line);
		newWeapon->setDescription(line);	

		std::getline(file,line);
		newWeapon->setTexture(line);
		
		std::getline(file,line);
		damage = new Damage;
		while ( std::regex_search (line,integers) )
		{	
			intIndex = stoi (line);
			std::getline(file,line);
			intVal = stoi (line);
			damage->setValue(intIndex,intVal);

			std::getline(file,line);
		}
		newWeapon->setAddedDamage(*damage);

		if ( std::regex_search (line,truespace) )
		{
			newWeapon->setRightHand(true);
		}
		std::getline(file,line);
		if ( std::regex_search (line,truespace) )
		{
			newWeapon->setLeftHand(true);
		}
		
		
		weapons[index] = newWeapon;
		index++;
	}
	file.close();
	return weapons;	
}
Useable** ListReader::readUseables(std::string &fileName)
{
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::cout << "No file\n";
		return NULL;
	}
	//assumes the file size is on top of the data
	file >> num_useables;
	
	Useable** useables = new Useable*[num_useables];
	Useable* newUseable;
	Damage* damage;

	int index = 0;
	std::string line;
	int intVal;
	int intIndex;

	//accounting for whitespace on the end of the line
	std::regex integers("[[:digit:]]+");
	std::regex truespace("(true)");

	while (index < num_useables)
	{
		newUseable = new Useable;

		std::getline(file,line);
		newUseable->setName(line);

		file >> intVal;
		newUseable->setValue(intVal);

		std::getline(file,line);
		std::getline(file,line);
		newUseable->setDescription(line);

		std::getline(file,line);
		newUseable->setTexture(line);
		
		std::getline(file,line);

		damage = new Damage;
		while ( std::regex_search (line,integers) )
		{	
			intIndex = stoi (line);
			std::getline(file,line);
			intVal = stoi (line);
			damage->setValue(intIndex,intVal);

			std::getline(file,line);
		}
		newUseable->setDamage(*damage);

		useables[index] = newUseable;
		index++;
	}
	file.close();
	return useables;	
}
/*Conversation** readConversation(std::string &fileName)
{
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::cout << "No file\n";
		return NULL;
	}
	int index = 0;
	std::string line;
	int intVal;
	int intIndex;
}
*/
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
const int ListReader::getNumUseables()
{
	return num_useables;
}