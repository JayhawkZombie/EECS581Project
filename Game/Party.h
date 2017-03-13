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
	BattleActor* getActor(int index);//returns a pointer to the battleActor at the given index
	float levelAverage();
//	void status();//this is the method that handles the status screen
	void selectChar();
	void charScreen(int index);

private:
	BattleActor** fighters;//holds the fighters
	Inventory* myInventory;
};

#endif