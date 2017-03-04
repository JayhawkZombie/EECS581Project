#include "Monster.h"



Monster::Monster()
{
	m_generation = 0;
	srand(time(NULL));
	int primaryElement = rand() % 6;
	int secondaryElement = rand() % 6;
	ListReader list;
//	MonsterType** myArray = list.readMonsters("Game/ContentFiles/MonsterTypes/MonsterTypes.txt");
	auto monsters = GameMain::Monsters(list.readMonsters("Game/ContentFiles/MonsterTypes/MonsterTypes.txt"));
	m_monsterType = monsters[primaryElement][secondaryElement][1][0];
	m_numPhysical = 0;
	m_numMagical = 0;
	m_generation = 0;
	setPrimary(m_monsterType->getPrimary());
	setSecondary(m_monsterType->getSecondary());


}


Monster::~Monster()
{
}

int Monster::getGeneration()const
{
	return m_generation;
}

bool Monster::takeDamage(const Damage recieved)
{
	auto dominated = BattleActor::ElementDominated();
	auto dominator = BattleActor::ElementDominator();
//	return dominator[1];
	//Damage* incurred = new Damage(recieved, m_defense);
	//For every element of this logic block,
	//determine the appropriate damage muliplier
	for (int i = 0; i < 9; i++)
	{
		//if I am attacked by an element that is both my primary and secondary element
		if (i == getPrimary() && i == getSecondary())
		{//I only take 70% damage
			this->setHpCur((int)(getHpCur() - recieved.content[i] * .7));
		}
		else if (i == getPrimary() && i == dominator[getSecondary()])
		{
			this->setHpCur((int)(getHpCur() - recieved.content[i] * .75));
		}
		else if (i == getPrimary() && i == dominated[getSecondary()])
		{
			this->setHpCur((int)(getHpCur() - recieved.content[i] * .9));
		}
		else if (i == getPrimary())
		{
			this->setHpCur((int)(getHpCur() - recieved.content[i] * .8));
		}
		else if (i == dominator[getPrimary()] && i == getSecondary())
		{
			this->setHpCur((int)(getHpCur() - recieved.content[i] * .8));
		}
		else if (i == dominator[getPrimary()] && i == dominator[getSecondary()])
		{
			this->setHpCur((int)(getHpCur() - recieved.content[i] * .85));
		}
		else if (i == dominator[getPrimary()] && i == dominated[getSecondary()])
		{
			this->setHpCur((int)(getHpCur() - recieved.content[i]));
		}
		else if (i == dominator[getPrimary()])
		{
			this->setHpCur((int)(getHpCur() - recieved.content[i] * .9));
		}
		else if (i == dominated[getPrimary()] && i == getSecondary())
		{
			this->setHpCur((int)(getHpCur() - recieved.content[i] * 1.1));
		}
		else if (i == dominated[getPrimary()] && i == dominator[getSecondary()])
		{
			this->setHpCur((int)(getHpCur() - recieved.content[i] * 1.15));
		}//if I am attacked by an element that dominates both my primary and secondary element
		else if (i == dominated[getPrimary()] && i == dominated[getSecondary()])
		{//I take 30% extra damage
			this->setHpCur((int)(getHpCur() - recieved.content[i] * 1.3));
		}
		else if (i == dominated[getPrimary()])
		{
			this->setHpCur((int)(getHpCur() - recieved.content[i] * 1.2));
		}
		else if (i == getSecondary())
		{
			this->setHpCur((int)(getHpCur() - recieved.content[i] * .9));
		}
		else if (i == dominator[getSecondary()])
		{
			this->setHpCur((int)(getHpCur() - recieved.content[i] * .95));
		}
		else if (i == dominated[getSecondary()])
		{
			this->setHpCur((int)(getHpCur() - recieved.content[i] * 1.1));
		}
		else
		{
			this->setHpCur((int)(getHpCur() - recieved.content[i]));
		}
	}
	return(isAlive());
}

Damage Monster::baseDamage()
{
	Damage result;//this is the result we will return that we have to add to
	int total;//this is the total amount of damage we should do
	//this else if block determines what the total damage should be
	if (this->getLevel() < 5)
	{
		total = 8 + (getLevel() - 1);
	}
	else if (this->getLevel() < 15)
	{
		total = 25 + (getLevel() - 15);
	}
	else if (this->getLevel() < 25)
	{
		total = 45 + (getLevel()-25);
	}
	else if (this->getLevel() < 35)
	{
		total = 65 + (getLevel()-35);
	}
	else
	{
		total = 65 + (getLevel() - 40) * 3;
	}
	result.content[getPrimary()] = (int)total*.3;

	float balance;//balance is a number between 0 and 1 representing the ratio of physical attacks against magical attacks
	float magMultiplier;//this is the multiplier that will be determined by the balance that multiplies magical damage
	float phyMultiplier;//above except physical
	if (m_numPhysical < 0)
	{
		m_numPhysical = 0;
	}
	if (m_numMagical < 0)
	{
		m_numMagical = 0;
	}
	if (m_numPhysical == m_numMagical && m_numPhysical == 0)//makes sure we don't divide by zero - if there have been no attacks,
	{//the balance is .5
		balance = .5;
	}
	else
	{
		balance = ((m_numMagical) / (m_numMagical + m_numPhysical));//the denom cant be zero because of the above logic block
	}
	int size = m_numMagical + m_numPhysical;//int size is just the number of attacks

	if (balance > 1)//redundant code that shouldn't ever be used, balance should always be <=1, but left just in case
	{
		balance = 1;
	}
	else if (balance < 0)//redundant, balance should always be >=0, but just in case
	{
		balance = 0;
	}

	/*This block establishes the elemental damage done by the monster*/
	if (getPrimary() == getSecondary())//case where the two elements are the same, we do bonus damage
	{//using the ceil function because we want there to be some damage in the case of a small float
		result.content[getPrimary()] = ceil(.5*total);//half of the total damage should be elemental - there is a 10% bonus because of 'pure' elementality
	}
	else//case where the elements are different
	{
		result.content[getPrimary()] = ceil(.27*total);//27% of the total damage will be of  the primary element
		result.content[getSecondary()] = ceil(.13*total);//13% of the total damage will be of the secondary element
	}





	/*This block establishes a physical and magical multiplier based on the
	balance of physical attacks to magical attacks, and is copied directly
	from HumanActor.cpp*/
	if (balance <= .2)
	{
		phyMultiplier = 1;
		magMultiplier = 0;
	}
	else if (balance <= .4)
	{
		phyMultiplier = .65;
		magMultiplier = .25;
	}
	else if (balance <= .6)
	{
		phyMultiplier = .4;
		magMultiplier = .4;
	}
	else if (balance <= .8)
	{
		phyMultiplier = .25;
		magMultiplier = .65;
	}
	else
	{
		phyMultiplier = 0;
		magMultiplier = 1;
	}


	/*This else if block assigns the physical and magical component of the base damage
	content[6] refers to physical, content[7] refers to magical. Total is the total amount of
	damage that the attack should do, adjusted for leveling etc. It is further adjusted based on 
	number of physical and magical attacks made, and then by the multiplier .6 because we want the
	physical and magical portion of a monsters damage to be 60% of the total damage- this gets adjusted
	based on the number of attacks they have made (size)*/
	if (size < 10)
	{
		result.content[6] = (int)(total*.6*phyMultiplier);
		result.content[7] = (int)(total*.6*magMultiplier);
	}
	else if (size < 50)
	{
		result.content[6] = (int)((total + 1)*.6*1.2*phyMultiplier);
		result.content[7] = (int)((total + 1)*.6*1.2*magMultiplier);
	}
	else if (size < 100)
	{
		result.content[6] = (int)((total + 2)*.6*1.4*phyMultiplier);
		result.content[7] = (int)((total + 2)*.6*1.4*magMultiplier);
	}
	else if (size < 250)
	{
		result.content[6] = (int)((total + 4)*.6*1.6*phyMultiplier);
		result.content[7] = (int)((total + 4)*.6*1.6*magMultiplier);
	}
	else if (size < 500)
	{
		result.content[6] = (int)((total + 6)*.6*1.8*phyMultiplier);
		result.content[7] = (int)((total + 6)*.6*1.8*magMultiplier);
	}
	else if (size < 1000)
	{
		result.content[6] = (int)((total + 10)*.6 * 2 * phyMultiplier);
		result.content[7] = (int)((total + 10)*.6 * 2 * magMultiplier);
	}
	else if (size < 5000)
	{
		result.content[6] = (int)((total + 13)*.6*2.2*phyMultiplier);
		result.content[7] = (int)((total + 13)*.6*2.2*magMultiplier);
	}
	else if (size < 10000)
	{
		result.content[6] = (int)((total + 17)*.6*2.4*phyMultiplier);
		result.content[7] = (int)((total + 17)*.6*2.4*magMultiplier);
	}
	else if (size < 50000)
	{
		result.content[6] = (int)((total + 20)*.6*2.6*phyMultiplier);
		result.content[7] = (int)((total + 20)*.6*2.6*magMultiplier);
	}
	else if (size < 100000)
	{
		result.content[6] = (int)((total + 25)*.6*2.8*phyMultiplier);
		result.content[7] = (int)((total + 25)*.6*2.8*magMultiplier);
	}
	else if (size < 500000)
	{
		result.content[6] = (int)((total + 35)*.6 * 3 * phyMultiplier);
		result.content[7] = (int)((total + 35)*.6 * 3 * magMultiplier);
	}
	else
	{
		result.content[6] = (int)((total + 50)*.6 * 4 * phyMultiplier);
		result.content[7] = (int)((total + 50)*.6 * 4 * magMultiplier);
	}
	return result;
}

void Monster::gainExp(int gain)
{

	//this else if block makes the level restrictions
	if (m_generation == 0 && getLevel() == 10)
	{
		return;
	}
	else if (m_generation == 1 && getLevel() == 20)
	{
		return;
	}
	else if (m_generation == 2 && getLevel() == 30)
	{
		return;
	}
	else if (m_generation == 3 && getLevel() == 40)
	{
		return;
	}
	else if (m_generation == 4 && getLevel() == 50)
	{
		return;
	}

	setExp(getExp() + (gain*(1.15 + (m_generation*.1))));//the monster gets a 10% bonus for each generation level, and a 15% bonus for being a monster
	if (getLevel() < 10)//if the level is less than ten, the required exp to level up is the level*100 + 1000
	{
		while (getExp()> (getLevel() * 100 + 1000))
		{
			levelUp();
			setExp(getExp() - (getLevel() * 100 + 1000));
		}
	}
	else//if the level is ten or greater, the required exp to level up has a power function as well
	{
		//this loop continues until we shouldn't level up any more, in case a low level monster gets a lot of exp and
		//needs to level up more than once
		while (getExp() > ((getLevel() * 100 + 1000) + (int)(12 * (pow(getLevel(), 1.65)))))
		{
			levelUp();
			setExp(getExp() - ((getLevel() * 100 + 1000) + (int)(12 * (pow(getLevel(), 1.65)))));
		}
	}
}

void Monster::levelUp()
{
	double balance;//this is the balance between numPhysical and numMagical - used later on
	setLevel(getLevel() + 1);//increments the level

	if (getLevel() == 5 || getLevel() == 15 || getLevel() == 25)
	{
		evolve();
	}


	//This block determines the balance value and checks m_numPhysical and m_numMagical
	if (m_numPhysical < 0)//sets negative values to zero
	{
		m_numPhysical = 0;
	}
	if (m_numMagical < 0)
	{
		m_numMagical = 0;
	}
	if (m_numMagical == 0 && m_numPhysical == 0)//if both are zero sets balance to .5 to avoid
	{//divide by zero errors
		balance = .5;
	}
	else//sets balance to be a double between zero and one
	{
		balance = m_numMagical / (m_numMagical + m_numPhysical);
	}


	//sets mp regen based on the number of magical techniques used
	if (m_numMagical <= 10)
	{
		setMpRegen(1);
	}
	else if (m_numMagical <= 50)
	{
		setMpRegen(2);
	}
	else if (m_numMagical <= 100)
	{
		setMpRegen(3);
	}
	else if (m_numMagical <= 250)
	{
		setMpRegen(4);
	}
	else if (m_numMagical <= 500)
	{
		setMpRegen(5);
	}
	else if (m_numMagical <= 1000)
	{
		setMpRegen(7);
	}
	else if (m_numMagical <= 5000)
	{
		setMpRegen(9);
	}
	else if (m_numMagical <= 10000)
	{
		setMpRegen(12);
	}
	else if (m_numMagical <= 50000)
	{
		setMpRegen(15);
	}
	else if (m_numMagical <= 100000)
	{
		setMpRegen(20);
	}
	else if (m_numMagical <= 500000)
	{
		setMpRegen(25);
	}
	else
	{
		setMpRegen(30);
	}

	//these mulitpliers are used later to determine how much health/magic the player recieves
	//upon leveling up- they are based on the balance variable
	double hpMultiplier;
	double mpMultiplier;


	if (balance <= .2)
	{
		hpMultiplier = 1.3;
		mpMultiplier = .65;
	}
	else if (balance <= .4)
	{
		hpMultiplier = 1.15;
		mpMultiplier = .8;
	}
	else if (balance <= .6)
	{
		hpMultiplier = 1;
		mpMultiplier = 1;
	}
	else if (balance <= .8)
	{
		hpMultiplier = .85;
		mpMultiplier = 1.2;
	}
	else
	{
		hpMultiplier = .7;
		mpMultiplier = 1.35;
	}

	//this block actually distributes the added mp and hp based on the multiplier above
	if (getLevel() <= 5)
	{
		setHpCur((int)(getHpCur() + 5 * hpMultiplier));
		setHpMax((int)(getHpMax() + 5 * hpMultiplier));
		setMpCur((int)(getMpCur() + 4 * mpMultiplier));
		setMpMax((int)(getMpMax() + 4 * mpMultiplier));
	}
	else if (getLevel() <= 10)
	{
		setHpCur((int)(getHpCur() + 20 * hpMultiplier));
		setHpMax((int)(getHpMax() + 20 * hpMultiplier));
		setMpCur((int)(getMpCur() + 4 * mpMultiplier));
		setMpMax((int)(getMpMax() + 4 * mpMultiplier));
	}
	else if (getLevel() <= 20)
	{
		setHpCur((int)(getHpCur() + 30 * hpMultiplier));
		setHpMax((int)(getHpMax() + 30 * hpMultiplier));
		setMpCur((int)(getMpCur() + 2 * mpMultiplier));
		setMpMax((int)(getMpMax() + 2 * mpMultiplier));
	}
	else if (getLevel() <= 30)
	{
		setHpCur((int)(getHpCur() + 40 * hpMultiplier));
		setHpMax((int)(getHpMax() + 40 * hpMultiplier));
		setMpCur((int)(getMpCur() + 2 * mpMultiplier));
		setMpMax((int)(getMpMax() + 2 * mpMultiplier));
	}
	else if (getLevel() <= 40)
	{
		setHpCur((int)(getHpCur() + 50 * hpMultiplier));
		setHpMax((int)(getHpMax() + 50 * hpMultiplier));
		setMpCur((int)(getMpCur() + 3 * mpMultiplier));
		setMpMax((int)(getMpMax() + 3 * mpMultiplier));
	}
	else if (getLevel() <= 50)
	{
		setHpCur((int)(getHpCur() + 60 * hpMultiplier));
		setHpMax((int)(getHpMax() + 60 * hpMultiplier));
		setMpCur((int)(getMpCur() + 3 * mpMultiplier));
		setMpMax((int)(getMpCur() + 3 * mpMultiplier));
	}
	else
	{
		setHpCur((int)(getHpCur() + 70 * hpMultiplier));
		setHpMax((int)(getHpCur() + 70 * hpMultiplier));
		setMpCur((int)(getMpCur() + 4 * mpMultiplier));
		setMpCur((int)(getMpMax() + 4 * mpMultiplier));
	}
}

void Monster::evolve()
{
	//bounds checking- if we are already at stage 4 we shouldn't evolve
	if (m_monsterType->getEvolutionStage() == 4)
	{
		return;
	}
	
	double balance;//this is the balance between numPhysical and numMagical - used later on

	//This block determines the balance value and checks m_numPhysical and m_numMagical
	if (m_numPhysical < 0)//sets negative values to zero
	{
		m_numPhysical = 0;
	}
	if (m_numMagical < 0)
	{
		m_numMagical = 0;
	}
	if (m_numMagical == 0 && m_numPhysical == 0)//if both are zero sets balance to .5 to avoid
	{//divide by zero errors
		balance = .5;
	}
	else//sets balance to be a double between zero and one
	{
		balance = m_numMagical / (m_numMagical + m_numPhysical);
	}

	auto numStages = GameMain::numStagesLookup();
	auto TreeType = MonsterType::getTreeType();

	//if(numStages[getPrimary()][getSecondary()])

	//case where all evolutions are possible
	/*
	if (m_monsterType->getPhysicalEvolution() && m_monsterType->getBalancedEvolution() && m_monsterType->getMagicalEvolution())
	{
		//TODO: Finish this... need to fix monstertype sheet first
	}
	*/
}

int Monster::getSecondary()const
{
	return m_secondary;
}

void Monster::setSecondary(int secondary)
{
	m_secondary = secondary;
}