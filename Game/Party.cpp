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

BattleActor* Party::getActor(int index)
{
	if (index < 0||index > 3)
	{
		return nullptr;
	}
	else
	{
		return fighters[index];
	}

}

float Party::levelAverage()
{
	int size = 0;
	int total = 0;
	//if(!(fighters[0] && fighters[1] && fighters[2] && fighters[3]))
	if (fighters[0])
	{
		total += fighters[0]->getLevel();
		size++;
	}
	if (fighters[1])
	{
		total += fighters[1]->getLevel();
		size++;
	}
	if (fighters[2])
	{
		total += fighters[2]->getLevel();
	}
	if (fighters[3])
	{
		total += fighters[3]->getLevel();
	}
	if (total == 0 ||size ==0)
	{
		return 0;
	}
	else
	{
		return(total / size);
	}
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

void Party::selectChar()
{
	int choice;
	while (true)
	{
		std::cout << "Which fighter would you like to examine?\n";
		for (int i = 0; i < 4; i++)
		{
			if (fighters[i])
			{
				std::cout << i << ") " << fighters[i]->getName();
				if (fighters[i]->getHpCur() < 0)//this if block is so we dont print out negative hp/mp numbers
				{
					fighters[i]->setHpCur(0);
				}
				if (fighters[i]->getMpCur() < 0)
				{
					fighters[i]->setMpCur(0);
				}
				std::cout << " HP: " << fighters[i]->getHpCur() << "/" << fighters[i]->getHpMax();
				std::cout << " MP: " << fighters[i]->getMpCur() << "/" << fighters[i]->getMpMax();
			}
		}
		std::cout << "5) Exit\n";
		try
		{
			std::cin >> choice;
			if (choice == 5)
			{
				return;
			}
			else if (!fighters[choice])
			{
				std::cout << "Sorry we dont have a fighter at index: " << choice << "\n";
			}
			else if (fighters[choice])
			{
				charScreen(choice);
			}
			else
			{
				std::cout << "How did you get here?\n";
			}
		}
		catch (int e)
		{
			std::cout << "Error code " << e <<"\n";
		}
	}
}

void Party::charScreen(int index)
{
	//Name Info
	std::cout << "Name:        " << fighters[index]->getName() << "\n";
	
	//Hp Mp Status info
	if (fighters[index]->getHpCur() < 0)
	{
		fighters[index]->setHpCur(0);
	}
	if (fighters[index]->getMpCur() < 0)
	{
		fighters[index]->setMpCur(0);
	}
	std::cout << "Hp: " << fighters[index]->getHpCur() << "/" << fighters[index]->getHpMax() << "\n";
	std::cout << "Mp: " << fighters[index]->getMpCur() << "/" << fighters[index]->getMpMax() << "\n";

	//Programming Class info
	if (fighters[index]->getIsHuman())
	{
		std::cout << "Human\n";
	}
	else if (fighters[index]->getIsMonster())
	{
		std::cout << "Monster\n";
	}


}