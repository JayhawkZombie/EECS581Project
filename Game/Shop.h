#ifndef _SHOP_H
#define _SHOP_H

#include "Inventory.h"
#include <array>
#include <iostream>

class Shop : public Inventory
{
public:
  Shop(Inventory* playerInventory, Inventory* shopInventory);
  ~Shop();
  //display all the useables, weapons, and armor of the player
  void displayPlayerInventory();
  //display all the useables, weapons, and armor of the shop
  void displayShopInventory();
  //buying items
  void Buy();
  //selling items
  void Sell();
  //the main shop menu
  void menu();

private:
  Inventory *m_playerInventory;
  Inventory *m_shopInventory;

};
#endif /* _SHOP_H */