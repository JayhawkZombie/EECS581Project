#ifndef INVENTORY_H
#define INVENTORY_H
#include "ListReader.h"
class Inventory
{
public:
	Inventory();
	~Inventory();
	//int* getArmor();
	//int* getWeapons();
	//int* getUseables();
	int getGold();
private:
	//int m_Armor[ListReader::getNumArmor()];
	//int m_Weapons[ListReader::getNumWeapon()];
	//int m_Useables[ListReader::getNumUseable()];
	int m_gold;
};
#endif