#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H
#include "HumanActor.h"
class MainCharacter : public HumanActor
{
public:
	/*
	virtual bool takeDamage(const Damage recieved);
	virtual Damage baseDamage();
	virtual void levelUp();
	virtual void gainExp(int gain);
	*/
	MainCharacter();
	~MainCharacter();
	virtual bool IncrementAffinity(int index, int value);
	int getAffinity(int index);
	virtual void printAffinities();

private:
	int m_affinity[6];
};

#endif