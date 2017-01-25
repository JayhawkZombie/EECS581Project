
#ifndef BATTLE_H
#define BATTLE_H

#include <time.h>
#include <stdlib.h>
#include "BattleActor.h"
#include "Party.h"
class Battle
{
public:
	Battle(Party allies, Party enemies, bool canEscape);
	~Battle();
/*
	int run();
	int alliesTurn();//unfinished
	int enemiesTurn();//unfinished
	void printActorInfo(BattleActor ba);
	void printPartyInfo(Party p);//unfinished
	bool isBattleOver();//unfinished
	void victory();//unfinished
	*/
private:
	Party m_allies;
	Party m_enemies;
	bool m_canEscape;
	int lastEnemyAttackIndex;
	int lastAllyAttackIndex;

};

#endif
