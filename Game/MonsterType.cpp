#include "MonsterType.h"

MonsterType::MonsterType() : m_primary(-1), m_secondary(-1), m_evolutionStage(-1), m_evolutionType(-1), m_name(""), m_description(""), m_evolvesInto1(NULL), m_evolvesInto2(NULL), m_evolvesInto3(NULL), m_evolvesFrom1(NULL), m_evolvesFrom2(NULL), m_evolvesFrom3(NULL), m_numEvolutions(0)
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
std::string MonsterType::getName()
{
	return m_name;
}
std::string MonsterType::getDescription()
{
	return m_description;
}
void MonsterType::setEvolvesFrom1(MonsterType* evolvesFrom1)
{
	m_evolvesFrom1 = evolvesFrom1;
}
void MonsterType::setEvolvesFrom2(MonsterType* evolvesFrom2)
{
	m_evolvesFrom2 = evolvesFrom2;
}
void MonsterType::setEvolvesFrom3(MonsterType* evolvesFrom3)
{
	m_evolvesFrom3 = evolvesFrom3;
}
MonsterType* MonsterType::getEvolvesFrom1()
{
	return m_evolvesFrom1;
}
MonsterType* MonsterType::getEvolvesFrom2()
{
	return m_evolvesFrom2;
}
MonsterType* MonsterType::getEvolvesFrom3()
{
	return m_evolvesFrom3;
}
void MonsterType::setEvolvesInto1(MonsterType* evolvesInto1)
{
	if (m_evolvesInto1 == NULL)
		m_numEvolutions++;
	m_evolvesInto1 = evolvesInto1;
}
void MonsterType::setEvolvesInto2(MonsterType* evolvesInto2)
{
	if (m_evolvesInto2 == NULL)
		m_numEvolutions++;
	m_evolvesInto2 = evolvesInto2;
}
void MonsterType::setEvolvesInto3(MonsterType* evolvesInto3)
{
	if (m_evolvesInto3 == NULL)
		m_numEvolutions++;
	m_evolvesInto3 = evolvesInto3;
}
MonsterType* MonsterType::getEvolvesInto1()
{
	return m_evolvesInto1;
}
MonsterType* MonsterType::getEvolvesInto2()
{
	return m_evolvesInto2;
}
MonsterType* MonsterType::getEvolvesInto3()
{
	return m_evolvesInto3;
}
int MonsterType::getNumOfEvolutions()
{
	return m_numEvolutions;
}
