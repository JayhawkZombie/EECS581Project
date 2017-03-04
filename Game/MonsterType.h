#ifndef MONSTERTYPE_H
#define MONSTERTYPE_H

#include "ListReader.h" //to read old Bestiary in rewriteBestiary
#include "GameMain.h"   //to read old Bestiary in rewriteBestiary



#include <string>
#include <iostream>
#include <fstream>  //to write a file in rewriteBestiary
#include <map>
class MonsterType{

public:	
	MonsterType();
	~MonsterType();
    int getPrimary();
    int getSecondary();
    int getEvolutionStage();
    int getEvolutionType();
	int getConcatenation();
	
	std::string getTexture();
    std::string getName();
    std::string getDescription();

    MonsterType* getPhysicalEvolution();
    MonsterType* getBalancedEvolution();
    MonsterType* getMagicalEvolution();

	void setPrimary(int primary);
	void setSecondary(int secondary);
	void setEvolutionStage(int evolutionStage);
	void setEvolutionType(int evolutionType);
	void setName(std::string name);
	void setDescription(std::string description);
	void setTexture(std::string texture);
	
	void setPhysicalEvolutionIndex(int index);
	void setBalancedEvolutionIndex(int index);
	void setMagicalEvolutionIndex(int index);

	void setPhysicalEvolutionName(std::string name);
	void setBalancedEvolutionName(std::string name);
	void setMagicalEvolutionName(std::string name);
	
	void setPhysicalEvolution(MonsterType* physicalEvolution);
	void setBalancedEvolution(MonsterType* balancedEvolution);
	void setMagicalEvolution(MonsterType* magicalEvolution);
	static std::map<int, std::map<int, std::map<int, std::map<int, int>>>> getMBPType();
	static std::map<int, std::map<int, int>> getTreeType();

//	void rewriteBestiary();

	std::string m_physicalEvolutionName;
	std::string m_balancedEvolutionName;
	std::string m_magicalEvolutionName;

private:
	int m_primary;
	int m_secondary;
	int m_evolutionStage;
	int m_evolutionType;
	int m_concatenation;
	std::string m_name;
	std::string m_description;

	int m_physicalEvolutionIndex;
	int m_balancedEvolutionIndex;
	int m_magicalEvolutionIndex;
	MonsterType* m_physicalEvolution;
	MonsterType* m_balancedEvolution;
	MonsterType* m_magicalEvolution;
	int m_numEvolutions;
	std::string m_texture;
};
#endif
