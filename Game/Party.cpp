#include "Party.h"

Party::Party()
{
	fighters = new BattleActor*[4];
	fighters[0] = NULL;
	fighters[1] = NULL;
	fighters[2] = NULL;
	fighters[3] = NULL;
	myInventory = new Inventory();
}

Party::~Party()
{
	delete fighters;
	delete myInventory;
}

bool Party::assignFighter(int index, BattleActor* fighter)
{
	if (index < 0 || index>3)//reject the assignment if the index is invalid
	{
		return false;
	}
	if (fighters[index] != NULL)//reject the assignment if there is already a fighter there
	{
		return false;
	}
	fighters[index] = fighter; //assign
	return true;
}

BattleActor* Party::removeFighter(int index)
{
	if (index < 0 || index > 3)//reject the removal if index is invalid
	{
		return NULL;
	}
	return fighters[index];
}

bool Party::hasLost()
{
	for(int i = 0; i < 4; i++)
	{
		if (fighters[i] != NULL)//if there is a fighter in i
		{
			if (fighters[i]->isAlive())//if he is alive, we haven't lost
			{
				return false;
			}
		}
	}//if none of them are alive, we've lost
	return true;
}