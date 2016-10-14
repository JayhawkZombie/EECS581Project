#ifndef MONSTERTYPE_H
#define MONSTERTYPE_H
#include <string>
#include <iostream>
class monsterType{

	public:	
		monsterType();
		~monsterType();
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
		void setEvolvesFrom1(monsterType* evolvesFrom1);
		void setEvolvesFrom2(monsterType* evolvesFrom2);
		void setEvolvesFrom3(monsterType* evolvesFrom3);
		monsterType* getEvolvesFrom1();
		monsterType* getEvolvesFrom2();
		monsterType* getEvolvesFrom3();
		void setEvolvesInto1(monsterType* evolvesInto1);
		void setEvolvesInto2(monsterType* evolvesInto2);
		void setEvolvesInto3(monsterType* evolvesInto3);
		monsterType* getEvolvesInto1();
		monsterType* getEvolvesInto2();
		monsterType* getEvolvesInto3();
		int getNumOfEvolutions();
		
	
	private:
		int m_primary;
		int m_secondary;
		int m_evolutionStage;
		int m_evolutionType;
		std::string m_name;
		std::string m_description;
		monsterType* m_evolvesInto1;
		monsterType* m_evolvesInto2;
		monsterType* m_evolvesInto3;
		monsterType* m_evolvesFrom1;
		monsterType* m_evolvesFrom2;
		monsterType* m_evolvesFrom3;
		int m_numEvolutions;
};
#endif
