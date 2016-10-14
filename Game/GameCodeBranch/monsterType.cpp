#include "monsterType.h"

monsterType::monsterType() : m_primary(-1), m_secondary(-1), m_evolutionStage(-1), m_evolutionType(-1), m_name(""), m_description(""), m_evolvesInto1(NULL), m_evolvesInto2(NULL), m_evolvesInto3(NULL), m_evolvesFrom1(NULL), m_evolvesFrom2(NULL), m_evolvesFrom3(NULL), m_numEvolutions(0)
{}
monsterType::~monsterType()
{}
void monsterType::setPrimary(int primary)
{
	m_primary = primary;
}
void monsterType::setSecondary(int secondary)
{
	m_secondary = secondary;
}
void monsterType::setEvolutionStage(int evolutionStage)
{
	m_evolutionStage = evolutionStage;
}
void monsterType::setEvolutionType(int evolutionType)
{
	m_evolutionType = evolutionType;
}
void monsterType::setName(std::string name)
{
	m_name = name;
}
void monsterType::setDescription(std::string description)
{
	m_description = description;
}
int monsterType::getPrimary()
{
	return m_primary;
}
int monsterType::getSecondary()
{
	return m_secondary;
}
int monsterType::getEvolutionStage()
{
	return m_evolutionStage;
}
int monsterType::getEvolutionType()
{
	return m_evolutionType;
}
std::string monsterType::getName()
{
	return m_name;
}
std::string monsterType::getDescription()
{
	return m_description;
}
void setEvolvesFrom1(monsterType* evolvesFrom1)
{
	m_evolvesFrom1 = evolvesFrom1;
}
void setEvolvesFrom2(monsterType* evolvesFrom2)
{
	m_evolvesFrom2 = evolvesFrom2;
}
void setEvolvesFrom3(monsterType* evolvesFrom3)
{
	m_evolvesFrom3 = evolvesFrom3;
}
monsterType* getEvolvesFrom1()
{
	return m_evolvesFrom1;
}
monsterType* getEvolvesFrom2()
{
	return m_evolvesFrom2;
}
monsterType* getEvolvesFrom3()
{
	return m_evolvesFrom3;
}
void setEvolvesInto1(monsterType* evolvesInto1)
{
	if (m_evolvesInto1 == NULL)
		m_numEvolutions++;
	m_evolvesInto1 = evolvesInto1;
}
void setEvolvesInto2(monsterType* evolvesInto2)
{
	if (m_evolvesInto2 == NULL)
		m_numEvolutions++;
	m_evolvesInto2 = evolvesInto2;
}
void setEvolvesInto3(monsterType* evolvesInto3)
{
	if (m_evolvesInto3 == NULL)
		m_numEvolutions++;
	m_evolvesInto3 = evolvesInto3;
}
monsterType* getEvolvesInto1()
{
	return m_evolvesInto1;
}
monsterType* getEvolvesInto3()
{
	return m_evolvesInto2;
}
monsterType* getEvolvesInto3()
{
	return = m_evolvesInto3;
}
int getNumOfEvolutions()
{
	return m_numEvolutions;
}
