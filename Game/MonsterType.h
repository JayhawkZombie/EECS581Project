#ifndef MONSTERTYPE_H
#define MONSTERTYPE_H
#include <string>
#include <iostream>
class MonsterType{

	public:	
		MonsterType();
		~MonsterType();
		void setPrimary(int primary);
		void setSecondary(int secondary);
		void setEvolutionStage(int evolutionStage);
		void setEvolutionType(int evolutionType);
		void setName(std::string name);
		void setDescription(std::string description);
		int getPrimary();
		int getSecondary();
		int getEvolutionStage();
		int getEvolutionType();
		std::string getName();
		std::string getDescription();
		void setEvolvesFrom1(MonsterType* evolvesFrom1);
		void setEvolvesFrom2(MonsterType* evolvesFrom2);
		void setEvolvesFrom3(MonsterType* evolvesFrom3);
		MonsterType* getEvolvesFrom1();
		MonsterType* getEvolvesFrom2();
		MonsterType* getEvolvesFrom3();
		void setEvolvesInto1(MonsterType* evolvesInto1);
		void setEvolvesInto2(MonsterType* evolvesInto2);
		void setEvolvesInto3(MonsterType* evolvesInto3);
		MonsterType* getEvolvesInto1();
		MonsterType* getEvolvesInto2();
		MonsterType* getEvolvesInto3();
		int getNumOfEvolutions();
		
	
	private:
		int m_primary;
		int m_secondary;
		int m_evolutionStage;
		int m_evolutionType;
		std::string m_name;
		std::string m_description;
		MonsterType* m_evolvesInto1;
		MonsterType* m_evolvesInto2;
		MonsterType* m_evolvesInto3;
		MonsterType* m_evolvesFrom1;
		MonsterType* m_evolvesFrom2;
		MonsterType* m_evolvesFrom3;
		int m_numEvolutions;
};
#endif
