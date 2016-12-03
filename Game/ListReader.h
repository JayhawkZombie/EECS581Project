#ifndef ListReader_H
#define ListReader_H

#include "MonsterType.h"
#include "Armor.h"
#include "Weapon.h"
#include "Useable.h"
#include "Conversation.h"

#include <ctype.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <regex>
#include <memory>

class ListReader{
  public:
    ListReader();
    ~ListReader();
    //reads in the file and fills in an array
    //returns the array
//    shared_ptr<MonsterType> readMonsters(std::string &fileName);
    MonsterType** readMonsters(std::string fileName);
    Armor** readArmor(std::string fileName);
    Weapon** readWeapons(std::string fileName);    
    Useable** readUseables(std::string fileName);
    Conversation** readConversation(std::string fileName);
    void menu();
  
    //returns the number on top of the file
    const int getNumMonsters();
    const int getNumArmor();
    const int getNumWeapons();
    const int getNumUseables();
    const int getNumConversations();

  private:
    int num_monsters;
    int num_armor;
    int num_weapons;
    int num_useables;
    int num_convos;
    MonsterType** monsters;
    Armor** armor;
    Weapon** weapons;
    Useable** useables;
    Conversation** conversations;
};
#endif
