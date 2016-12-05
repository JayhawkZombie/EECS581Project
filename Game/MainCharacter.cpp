#include "MainCharacter.h"



MainCharacter::MainCharacter()
{
	for (int i = 0; i < 6; i++)
	{
		m_affinity[i] = 0;
	}
}


MainCharacter::~MainCharacter()
{
}

void MainCharacter::IncrementAffinity(int index, int value)
{
	if (index < 1 || index>6)//no work done on bad values
	{
		return;
	}
	if (value > 20)
	{
		value = 20;
	}
	else if (value < -20)
	{
		value = -20;
	}
	m_affinity[index] = m_affinity[index] + value;
}

int MainCharacter::getAffinity(int index)
{
	if (index < 1 || index>6)
	{
		return -1;
	}
	else
	{
		return m_affinity[index];
	}
}
void MainCharacter::printAffinities()
{
	std::cout << "fire:    " << m_affinity[0] << "\n";
	std::cout << "water:   " << m_affinity[1] << "\n"; 
	std::cout << "earth:   " << m_affinity[2] << "\n";
	std::cout << "air:     " << m_affinity[3] << "\n";
	std::cout << "light:   " << m_affinity[4] << "\n";
	std::cout << "dark:    " << m_affinity[5] << "\n";
}


/*
void HumanActor::LevelUp()
{
	double balance;
	setLevel(getLevel() + 1);
	if (m_numPhysical < 0)
	{
		m_numPhysical = 0;
	}
	if (m_numMagical < 0)
	{
		m_numMagical = 0;
	}
	if (m_numMagical == 0 && m_numPhysical == 0)
	{
		balance = .5;
	}
	else
	{
		balance = m_numMagical / (m_numMagical + m_numPhysical);
	}

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
	if (getLevel() <= 5)
	{
		setHpCur((int)(getHpCur() + 5 * hpMultiplier));
		setHpMax((int)(getHpMax() + 5 * hpMultiplier));
		setMpCur(getMpCur() + 4 * mpMultiplier);
		setMpMax(getMpMax() + 4 * mpMultiplier);
	}
	else if (getLevel() <= 10)
	{
		setHpCur((int)(getHpCur() + 20 * hpMultiplier));
		setHpMax((int)(getHpMax() + 20 * hpMultiplier));
		setMpCur(getMpCur() + 4 * mpMultiplier);
		setMpMax(getMpMax() + 4 * mpMultiplier);
	}
	else if (getLevel() <= 20)
	{
		setHpCur((int)(getHpCur() + 30 * hpMultiplier));
		setHpMax((int)(getHpMax() + 30 * hpMultiplier));
		setMpCur(getMpCur() + 2 * mpMultiplier);
		setMpMax(getMpMax() + 2 * mpMultiplier);
	}
	else if (getLevel() <= 30)
	{
		setHpCur(((int)getHpCur() + 40 * hpMultiplier));
		setHpMax(((int)getHpMax() + 40 * hpMultiplier));
		setMpCur(getMpCur() + 2 * mpMultiplier);
		setMpMax(getMpMax() + 2 * mpMultiplier);
	}
	else if (getLevel() <= 40)
	{
		setHpCur(((int)getHpCur() + 50 * hpMultiplier));
		setHpMax(((int)getHpMax() + 50 * hpMultiplier));
		setMpCur(getMpCur() + 3 * mpMultiplier);
		setMpMax(getMpMax() + 3 * mpMultiplier);
	}
	else if (getLevel() <= 50)
	{
		setHpCur((int)(getHpCur() + 60 * hpMultiplier));
		setHpMax((int)(getHpMax() + 60 * hpMultiplier));
		setMpCur(getMpCur() + 3 * mpMultiplier);
		setMpMax(getMpCur() + 3 * mpMultiplier);
	}
	else
	{
		setHpCur((int)(getHpCur() + 70 * hpMultiplier));
		setHpMax((int)(getHpCur() + 70 * hpMultiplier));
		setMpCur(getMpCur() + 4 * mpMultiplier);
		setMpCur(getMpMax() + 4 * mpMultiplier);
	}
}*/

/*void MainCharacter::Levelup()//fix this later
{
	//TODO Fix this later
}
void MainCharacter::gainExp(int gain)
{
	return;
}
*/