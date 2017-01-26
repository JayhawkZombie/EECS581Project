#include "Shop.h"
Shop::Shop(Inventory* playerInventory, Inventory* shopInventory)
{
  m_playerInventory = playerInventory;
  m_shopInventory = shopInventory;
}
Shop::~Shop()
{
}
void Shop::Buy()
{
  displayPlayerInventory();
  displayShopInventory();
  std::cout << "\nBuying; [1] for Useables, [2] for Weapons, [3] for Armor, [-1] to go back to menu: ";

  int option = 0;
  int amount;
  int item;
  while (-1 != option)
  {
    std::cin >> option;
    switch (option)
    {
    case 1:
      std::cout << "\nItem #: ";
      std::cin >> item;
      std::cout << "\nInsert amount: ";
      std::cin >> amount;

      if (m_shopInventory->incrementUseables(item, (-amount)))
      {
        std::cout << "\nInvalid";
      }
      else
      {
        m_playerInventory->incrementUseables(item, amount);
      }
      break;
    case 2:
      std::cout << "\nItem #: ";
      std::cin >> item;
      std::cout << "\nInsert amount: ";
      std::cin >> amount;

      if (m_shopInventory->incrementWeapons(item, (-amount)))
      {
        std::cout << "\nInvalid";
      }
      else
      {
        m_playerInventory->incrementWeapons(item, amount);
      }
      break;
    case 3:
      std::cout << "\nItem #: ";
      std::cin >> item;
      std::cout << "\nInsert amount: ";
      std::cin >> amount;

      if (m_shopInventory->incrementArmor(item, (-amount)))
      {
        std::cout << "\nInvalid";
      }
      else
      {
        m_playerInventory->incrementArmor(item, amount);
      }
      break;
    case -1:
      menu();
      break;
    default:
      break;
    }
  }
}
void Shop::Sell()
{
  displayPlayerInventory();
  displayShopInventory();
  std::cout << "\nSelling; [1] for Useables, [2] for Weapons, [3] for Armor, [-1] to go back to menu: ";

  int option = 0;
  int amount;
  int item;

  while (-1 != option)
  {
    std::cin >> option;
    switch (option)
    {
    case 1:
      std::cout << "\nItem #: ";
      std::cin >> item;
      std::cout << "\nInsert amount: ";
      std::cin >> amount;

      if (m_playerInventory->incrementUseables(item, (-amount)))
      {
        std::cout << "\nInvalid";
      }
      else
      {
        m_shopInventory->incrementUseables(item, amount);
      }
      break;
    case 2:
      std::cout << "\nItem #: ";
      std::cin >> item;
      std::cout << "\nInsert amount: ";
      std::cin >> amount;

      if (m_playerInventory->incrementWeapons(item, (-amount)))
      {
        std::cout << "\nInvalid";
      }
      else
      {
        m_shopInventory->incrementWeapons(item, amount);
      }
      break;
    case 3:
      std::cout << "\nItem #: ";
      std::cin >> item;
      std::cout << "\nInsert amount: ";
      std::cin >> amount;

      if (m_playerInventory->incrementArmor(item, (-amount)))
      {
        std::cout << "\nInvalid";
      }
      else
      {
        m_shopInventory->incrementArmor(item, amount);
      }
      break;
    case -1:
      menu();
      break;
    default:
      break;
    }
  }
}
void Shop::displayPlayerInventory()
{
  //display useables
  for (int i = 0; i < sizeof(m_playerInventory->getUseables()); i++)
  {
    std::cout << "Useable #" << i << ", Amount: " << m_playerInventory->getUseables()[i] << "\n";
  }
  //display weapons
  for (int i = 0; i < sizeof(m_playerInventory->getWeapons()); i++)
  {
    std::cout << "Weapon #" << i << ", Amount: " << m_playerInventory->getWeapons()[i] << "\n";
  }
  //display armor
  for (int i = 0; i < sizeof(m_playerInventory->getArmor()); i++)
  {
    std::cout << "Armor #" << i << ", Amount: " << m_playerInventory->getArmor()[i] << "\n";
  }

}
void Shop::displayShopInventory()
{
  //display useables
  for (int i = 0; i < sizeof(m_shopInventory->getUseables()); i++)
  {
    std::cout << "Useable #" << i << ", Amount: " << m_shopInventory->getUseables()[i] << "\n";
  }
  //display weapons
  for (int i = 0; i < sizeof(m_shopInventory->getWeapons()); i++)
  {
    std::cout << "Weapon #" << i << ", Amount: " << m_shopInventory->getWeapons()[i] << "\n";
  }
  //display armor
  for (int i = 0; i < sizeof(m_shopInventory->getArmor()); i++)
  {
    std::cout << "Armor #" << i << ", Amount: " << m_shopInventory->getArmor()[i] << "\n";
  }
}
void Shop::menu()
{
  int playerSelection;
  bool exitMenu = false;
  std::cout << "Buy [1], Sell [2], or Exit [3]\n";
  std::cin >> playerSelection;
  while (!exitMenu)
  {
    switch (playerSelection)
    {
    case 1:
      Buy();
      break;
    case 2:
      Sell();
      break;
    case 3:
      exitMenu = true;
      break;
    default:
      break;
    }
  }
}
