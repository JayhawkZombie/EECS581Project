#ifndef PARTY_H
#define PARTY_H
#include "BattleActor.h"
#include "Inventory.h"
#include "RPGItem.h"
class Party
{
public:
	Party();
	~Party();
	bool assignFighter(int index, BattleActor* fighter);
	BattleActor* removeFighter(int index);
	bool hasLost();//returns true if the party has lost the battle false else



private:
	BattleActor** fighters;//holds the fighters
	Inventory* myInventory;
};

#endif