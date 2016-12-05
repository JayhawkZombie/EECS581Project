#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H
#include "HumanActor.h"
class MainCharacter: public HumanActor
{
public:
	MainCharacter();
	~MainCharacter();
	void IncrementAffinity(int index, int value);
	int getAffinity(int index);

private:
	int m_affinity[6];
	virtual bool TakeDamage(const Damage recieved);
	virtual void Levelup();
	virtual bool gainExp();
};

#endif