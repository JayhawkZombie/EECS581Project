

#include "Battle.h"



Battle::Battle(Party allies, Party enemies, bool canEscape)
{
	m_allies = allies;
	m_enemies = enemies;
	m_canEscape = canEscape;
	lastAllyAttackIndex = 3;
	lastEnemyAttackIndex = 3;
}

/*
Battle::~Battle()
{
}

int Battle::run()
{
	srand(time(NULL));
	int r = rand();
	if (r % 2 == 0)
	{
		alliesTurn();
	}
	while (!isBattleOver())
	{
		enemiesTurn();
		alliesTurn();
	}
}
*/

/*
* Return Values Breakdown for alliesTurn()
* -1 no result, do nothing
* 0 failure, go to loading screen
* 1 success, go back to map, victory screen?
* 2 ran away, go back to map, no victory screen
*/
/*
int Battle::alliesTurn()
{
	int choice=-1;//holds the choice the user makes
	bool decided = false;//makes sure the user has made a decision, controls the loop
	while (!decided)
	{
		//print options
		std::cout << "1) Attack\n";
		std::cout << "2) Use Skill\n";
		std::cout << "3) Wait\n";
		if (m_canEscape)
		{
			std::cout << "4) Run\n";
		}
		try
		{
			std::cin >> choice;
			if (m_canEscape)
			{
				if (choice < 1 || choice>4)
				{
					std::cout << "Please input a number between 1 and 4";
					choice = -1;
				}
			}
			else
			{
				if (choice < 1 || choice > 3)
				{
					std::cout << "Please input a number between 1 and 3";
					choice = -1;
				}
			}
		}
		catch (int e)
		{
			if (m_canEscape)
			{
				std::cout << "Please input a number between 1 and 4";
			}
			else
			{
				std:cout << "Please input a number between 1 and 3";
			}
		}
		if (choice == 1)
		{
			//logic for attack here, select enemy maybe?
		}
		else if (choice == 2)//Logic for use skill here
		{

		}
		else if (choice == 3)//logic for wait here 
	}
}


void Battle::printActorInfo(BattleActor ba)
{
	std::cout << "Name:        " << ba.getName() << "\n";
	std::cout << "HP:          " << ba.getHpCur() << "/" << ba.getHpMax() << "\n";
	std::cout << "MP:          " << ba.getMpCur() << "/" << ba.getMpMax() << "\n";
	//TODO: add status stuff
}
*/