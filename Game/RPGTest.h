#ifndef RPG_TEST_H
#define RPG_TEST_H

#include "Armor.h"
#include "RPGActor.h"
#include "RPGItem.h"
#include "Damage.h"
#include "Tile.h"
#include "Weapon.h"
#include <iostream>
class RPGTest
{
public:
	RPGTest();
	~RPGTest();
	static void runTests(bool quiet);
	static bool testRPGActor1(bool quiet);
	static bool testRPGActor2(bool quiet);
	static bool testRPGItem1(bool quiet);
	static bool testRPGItem2(bool quiet);
	static bool testRPGItem3(bool quiet);
	static bool testRPGItem4(bool quiet);
	static bool testRPGItem5(bool quiet);
	static bool testTile1(bool quiet);
	static bool testTile2(bool quiet);
	static bool testTile3(bool quiet);
	static bool testTile4(bool quiet);
	static bool testTile5(bool quiet);
	static bool testTile6(bool quiet);
  static bool testDamage1(bool quiet);
  static bool testDamage2(bool quiet);
  static bool testArmor1(bool quiet);
  static bool testArmor2(bool queit);
  static bool testArmor3(bool quiet);
  static bool testArmor4(bool quiet);
  static bool testArmor5(bool quiet);
  static bool testArmor6(bool quiet);
  static bool testArmor7(bool quiet);
  static bool testWeapon1(bool quiet);
  static bool testWeapon2(bool quiet);
  static bool testWeapon3(bool quiet);
  static bool testWeapon4(bool quiet);


};
#endif
