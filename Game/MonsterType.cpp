#include "MonsterType.h"

MonsterType::MonsterType() :
m_primary(-1), m_secondary(-1), m_evolutionStage(-1), m_evolutionType(-1),
m_name(""), m_description(""),
m_physicalEvolution(NULL), m_balancedEvolution(NULL), m_magicalEvolution(NULL),
m_numEvolutions(0), m_texture("")

{}
MonsterType::~MonsterType()
{}
void MonsterType::setPrimary(int primary)
{
	m_primary = primary;
}
void MonsterType::setSecondary(int secondary)
{
	m_secondary = secondary;
}
void MonsterType::setEvolutionStage(int evolutionStage)
{
	m_evolutionStage = evolutionStage;
}
void MonsterType::setEvolutionType(int evolutionType)
{
	m_evolutionType = evolutionType;
}
void MonsterType::setName(std::string name)
{
	m_name = name;
}
void MonsterType::setDescription(std::string description)
{
	m_description = description;
}
int MonsterType::getPrimary()
{
	return m_primary;
}
int MonsterType::getSecondary()
{
	return m_secondary;
}
int MonsterType::getEvolutionStage()
{
	return m_evolutionStage;
}
int MonsterType::getEvolutionType()
{
	return m_evolutionType;
}
int MonsterType::getConcatenation()
{
	std::string str_concat;
	str_concat.append( (std::to_string(m_primary)) );
	str_concat.append( (std::to_string(m_secondary)) );
	str_concat.append( (std::to_string(m_evolutionStage)) );
	str_concat.append( (std::to_string(m_evolutionType)) );
	m_concatenation = std::stoi(str_concat);
	
	return m_concatenation;
}
void MonsterType::setTexture(std::string texture)
{
	m_texture = texture;
}
std::string MonsterType::getTexture()
{
	return m_texture;
}
std::string MonsterType::getName()
{
	return m_name;
}
std::string MonsterType::getDescription()
{
	return m_description;
}
void MonsterType::setPhysicalEvolution(MonsterType* physicalEvolution)
{
	m_physicalEvolution = physicalEvolution;
}
void MonsterType::setBalancedEvolution(MonsterType* balancedEvolution)
{
	m_balancedEvolution = balancedEvolution;
}
void MonsterType::setMagicalEvolution(MonsterType* magicalEvolution)
{
	m_magicalEvolution = magicalEvolution;
}
std::map<int, std::map<int, std::map<int, std::map<int, int>>>> MonsterType::getMBPType()
{
	//the four inputs are 
	//1 primary Element
	//2 secondary Element
	//3 stage
	//4 Evolution Type
	//if the result is a
	//0- this is a physical evolution
	//1- this is a balanced evolution
	//2- this is a magical evolution
	std::map<int, std::map<int, int>> treeType1;
	std::map<int, std::map<int, int>> treeType2;
	std::map<int, std::map<int, int>> treeType3;
	std::map<int, std::map<int, int>> treeType4;
	std::map<int, std::map<int, int>> treeType5;


	treeType1[1][0] = 1;
	treeType1[2][0] = 1;
	treeType1[3][0] = 1;
	treeType1[4][0] = 1;

	treeType2[1][0] = 1;
	treeType2[2][0] = 0;
	treeType2[2][1] = 2;
	treeType2[3][0] = 0;
	treeType2[3][1] = 2;
	treeType2[4][0] = 0;
	treeType2[4][1] = 2;

	treeType3[1][0] = 1;
	treeType3[2][0] = 0;
	treeType3[2][1] = 1;
	treeType3[2][2] = 2;
	treeType3[3][0] = 0;
	treeType3[3][1] = 1;
	treeType3[3][2] = 2;
	treeType3[4][0] = 0;
	treeType3[4][1] = 1;
	treeType3[4][2] = 2;

	treeType4[1][0] = 1;
	treeType4[2] = treeType3[2];
	treeType4[3][0] = 0;
	treeType4[3][1] = 1;
	treeType4[3][2] = 1;
	treeType4[3][3] = 2;
	treeType4[4] = treeType4[3];

	treeType5[1][0] = 0;
	treeType5[1][1] = 1;
	treeType5[1][2] = 2;
	treeType5[2][0] = 0;
	treeType5[2][1] = 1;
	treeType5[2][2] = 2;
	treeType5[2][3] = 1;
	treeType5[3][0] = 0;
	treeType5[3][1] = 1;
	treeType5[3][2] = 1;
	treeType5[3][3] = 2;
	treeType5[3][4] = 1;
	treeType5[4][0] = 0;
	treeType5[4][1] = 0;
	treeType5[4][2] = 2;
	treeType5[4][3] = 1;
	treeType5[4][4] = 2;
	treeType5[4][5] = 1;

	std::map<int, std::map<int, std::map<int, std::map<int, int>>>> type;

	type[0][0] = treeType4;
	type[0][1] = treeType2;
	type[0][2] = treeType3;
	type[0][3] = treeType2;
	type[0][4] = treeType2;
	type[0][5] = treeType2;

	type[1][0] = treeType1;
	type[1][1] = treeType4;
	type[1][2] = treeType3;
	type[1][3] = treeType3;
	type[1][4] = treeType4;
	type[1][5] = treeType4;
	
	type[2][0] = treeType3;
	type[2][1] = treeType2;
	type[2][2] = treeType5;
	type[2][3] = treeType2;
	type[2][4] = treeType2;
	type[2][5] = treeType1;
	
	type[3][0] = treeType3;
	type[3][1] = treeType2;
	type[3][2] = treeType2;
	type[3][3] = treeType4;
	type[3][4] = treeType3;
	type[3][5] = treeType3;

	type[4][0] = treeType3;
	type[4][1] = treeType2;
	type[4][2] = treeType2;
	type[4][3] = treeType2;
	type[4][4] = treeType4;
	type[4][5] = treeType3;

	type[5][0] = treeType3;
	type[5][1] = treeType3;
	type[5][2] = treeType2;
	type[5][3] = treeType1;
	type[5][4] = treeType1;
	type[5][5] = treeType4;

	return type;
}
MonsterType* MonsterType::getPhysicalEvolution()
{
	return m_physicalEvolution;
}
MonsterType* MonsterType::getBalancedEvolution()
{
	return m_balancedEvolution;
}
MonsterType* MonsterType::getMagicalEvolution()
{
	return m_magicalEvolution;
}

MonsterType** MonsterType::readMonsters(std::string fileName)
{
		// Declares the ifstream to read in the file from the string file name.
		
		std::ifstream file;
		file.open(fileName);
		//If the file isn't there, then print no file, and return NULL
		if (!file.is_open())
		{
				std::cout << "No file\n";
				return NULL;
		}
		int numMonsters;
		//Reads in total number of monsters
		//Assumes the file size is on top of the text file's data
		file >> numMonsters;

		//Creation of monster array that will contain all of the monsters
		MonsterType** monsters = new MonsterType*[numMonsters];

		//Monster pointer for creation of new monster instances
		MonsterType* newMonster;

		//Curent index in monster array
		int index = 0;

		//Temporary types that will pass in data
		std::string line;
		int intVal;
		std::getline(file, line);

		//Main loop for passing in monster data
		//Assumes completed monster descriptions. (might break if they aren't?)
		//While the index is smaller (or equal to, since its index starts at 0) to the total number of monsters that's read in from the top of the file data
		while (index < numMonsters)
		{
				//Create new monster instance
				newMonster = new MonsterType;

				//Reading in data given how it looks like you're formatting the text files
				//   std::getline(file,line);
				std::getline(file, line);
				std::getline(file, line); //Gets the monster name here
				newMonster->setName(line); //Sets the monster name

				std::getline(file, line); //Gets the monster description
				newMonster->setDescription(line); //Sets the monster description

				file >> intVal; //Gets the primary element in integer form
				newMonster->setPrimary(intVal); //Sets the primary element

				file >> intVal; //Gets the secondary element
				newMonster->setSecondary(intVal); //Sets the secondary element

				file >> intVal; //Gets the evolution stage
				newMonster->setEvolutionStage(intVal); //Sets the evolution stage

				file >> intVal; //Gets the evolution type
				newMonster->setEvolutionType(intVal); //Sets the evolution type

				std::getline(file, line);
				std::getline(file, line); //Gets the texture
				newMonster->setTexture(line); //Sets the texture

																			//Evolutions are not currently set because you mentioned it's not finished yet?
				std::getline(file, line); //Gets the Physical Evolution
																	//newMonster->setPhysicalEvolution(line);

				std::getline(file, line); //Gets the Balanced Evolution
																	//newMonster->setBalancedEvolution(line);

				std::getline(file, line); //Gets the Magical Evolution
																	//newMonster->setMagicalEvolution(line);

				monsters[index] = newMonster; //Places the monster in the array
				index++; //Increment the index
		}
		file.close(); //Close the data text file
		return monsters; //Return the monster array
}