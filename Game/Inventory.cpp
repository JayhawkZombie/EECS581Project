#include "Inventory.h"

Inventory::Inventory()
{
	m_gold = 0;
}

Inventory::~Inventory()
{

}

int Inventory::getGold()
{
	return m_gold;
}