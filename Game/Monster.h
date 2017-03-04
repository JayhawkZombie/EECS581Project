#ifndef MONSTER_H
#define MONSTER_H

#include "BattleActor.h"//superclass
#include "ElementsEnum.h"
#include "MonsterType.h"
#include "GameMain.h"//Monsters map

#include <math.h>//ceil, pow for damages
#include <stdlib.h>//rand, srand in default constructor
#include <time.h> //to seed rand


class Monster: public BattleActor
{
public:
	Monster();
	~Monster();

	virtual bool takeDamage(const Damage recieved);
	virtual Damage baseDamage();
	virtual void levelUp();
	virtual void gainExp(int gain);
	virtual void evolve();
	
	//getters
	int getSecondary()const;
	int getGeneration()const;

	//setters
	void setSecondary(int Secondary);

private:
	MonsterType* m_monsterType;
	int m_secondary;
	int m_numPhysical;
	int m_numMagical;
	int m_generation;
};

#endif