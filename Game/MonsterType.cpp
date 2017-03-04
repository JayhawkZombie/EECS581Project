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

std::map<int, std::map<int, int>> MonsterType::getTreeType()
{
	std::map<int, std::map<int, int>> TreeType;

	TreeType[0][0] = 4;
	TreeType[0][1] = 2;
	TreeType[0][2] = 3;
	TreeType[0][3] = 2;
	TreeType[0][4] = 2;
	TreeType[0][5] = 2;

	TreeType[1][0] = 1;
	TreeType[1][1] = 4;
	TreeType[1][2] = 3;
	TreeType[1][3] = 3;
	TreeType[1][4] = 4;
	TreeType[1][4] = 4;

	TreeType[2][0] = 3;
	TreeType[2][1] = 2;
	TreeType[2][2] = 5;
	TreeType[2][3] = 2;
	TreeType[2][4] = 2;
	TreeType[2][5] = 1;

	TreeType[3][0] = 3;
	TreeType[3][1] = 2;
	TreeType[3][2] = 2;
	TreeType[3][3] = 4;
	TreeType[3][4] = 3;
	TreeType[3][5] = 3;

	TreeType[4][0] = 3;
	TreeType[4][1] = 2;
	TreeType[4][2] = 2;
	TreeType[4][3] = 2;
	TreeType[4][4] = 4;
	TreeType[4][5] = 3;

	TreeType[5][0] = 3;
	TreeType[5][1] = 3;
	TreeType[5][2] = 2;
	TreeType[5][3] = 1;
	TreeType[5][4] = 1;
	TreeType[5][5] = 4;
	
	return TreeType;
}


//the following three methods are temporary for use by rewriteBestiary
void MonsterType::setPhysicalEvolutionName(std::string name)
{
	m_physicalEvolutionName = name;
}

void MonsterType::setBalancedEvolutionName(std::string name)
{
	m_balancedEvolutionName = name;
}

void MonsterType::setMagicalEvolutionName(std::string name)
{
	m_magicalEvolutionName = name;
}

void MonsterType::setPhysicalEvolutionIndex(int index)
{
	m_physicalEvolutionIndex = index;
}

void MonsterType::setBalancedEvolutionIndex(int index)
{
	m_balancedEvolutionIndex = index;
}

void MonsterType::setMagicalEvolutionIndex(int index)
{
	m_magicalEvolutionIndex = index;
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

/* //I think I have a better Idea, but if it doesnt work, I'll do it this way
void rewriteBestiary()
{
	ListReader list;
	MonsterType** myArray = list.readMonsters2("Game/ContentFiles/MonsterTypes/MonsterTypes.txt");
	std::map<int, std::map<int, std::map<int, std::map<int, MonsterType*>>>> myMonsters = GameMain::Monsters(myArray);
	int physicalEvolutionIndexes[319];
	int balancedEvolutionIndexes[319];
	int magicalEvolutionIndexes[319];

	for (int i = 0; i < 319; i++)
	{
		if (myArray[i]->m_physicalEvolutionName.compare("NULL") == 0)
		{
			myArray[i]->setPhysicalEvolutionIndex(-1);//sets
		}
	}

}
*/