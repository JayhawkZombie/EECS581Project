#include "RPGTest.h"



RPGTest::RPGTest()
{
}


RPGTest::~RPGTest()
{
}

void RPGTest::runTests(bool quiet)
{
	int numPassed = 0;
	int numTotal = 0;
	if (testRPGActor1(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testRPGActor2(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testRPGItem1(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testRPGItem2(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}	
	if (testRPGItem3(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}	
	if (testRPGItem4(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testRPGItem5(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testTile1(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testTile2(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testTile3(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testTile4(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testTile5(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testTile6(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
  if (testDamage1(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testDamage2(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testArmor1(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testArmor2(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testArmor3(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testArmor4(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testArmor5(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testArmor6(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testArmor7(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testWeapon1(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testWeapon2(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testWeapon3(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testWeapon4(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
	std::cout << numPassed << "/" << numTotal << "Passed, " << ((double)numPassed / (double)numTotal) * 100 << "%\n";

}

bool RPGTest::testRPGActor1(bool quiet)
{//This function tests the constructor for the RPGActor
	RPGActor* myActor = new RPGActor();
	if (myActor->getName() == "")
	{
		if (!quiet)
		{
			std::cout << "RPGActor Test 1:  PASSED\n";
		}
		delete myActor;
		return true;
	}
	else
	{
		std::cout << "RPGActor Test 1: FAILED\n";
		std::cout << "myActor->getName() ==" << myActor->getName() << "\n";
		delete myActor;
		return false;
	}
}

bool RPGTest::testRPGActor2(bool quiet)
{//This function tests the getName and setName functions in the RPGActor Class
	RPGActor* myActor = new RPGActor();
	myActor->setName("test");
	if (myActor->getName() == "test")
	{
		if (!quiet)
		{
			std::cout << "RPGActor Test 2: PASSED\n";
		}
		delete myActor;
		return true;
	}
	else
	{
		std::cout << "RPGActor Test 2: FAILED\n";
		delete myActor;
		return false;
	}
}

bool RPGTest::testRPGItem1(bool quiet)
{//tests constructor and implicitly test getters and setters
	RPGItem* myItem = new RPGItem();
	if (  (myItem->getName().compare("")==0) && (myItem->getDescription().compare("")==0 ) && (myItem->getValue() == 0) && (myItem->getId() == 0)  )
	{
		if (!quiet)
		{
			std::cout << "RPGItem Test 1: PASSED\n";
		}
		delete myItem;
		return true;
	}
	else
	{
		std::cout << "RPGItem Test 1: FAILED\n";
		std::cout << "myItem->getName() = " << myItem->getName() << "\n";
		std::cout << "myItem->getDescription() = " << myItem->getDescription() << "\n";
		std::cout << "myItem->getValue() = " << myItem->getValue() << "\n";
		std::cout << "myItem->getId() = " << myItem->getId() << "\n";
		std::cout << "myItem->getName().compare(\"\") = " << myItem->getName().compare("") << "\n";
//		std::cout << "myItem->getName()==\"\" " << myItem->getName() == "";
		delete myItem;
		return false;
	}
}

bool RPGTest::testRPGItem2(bool quiet)
{//Tests getters and setters for m_name variable
	RPGItem* myItem = new RPGItem();
	myItem->setName("TestName");
	if (myItem->getName() == "TestName")
	{
		if (!quiet)
		{
			std::cout << "RPGItem Test 2: PASSED\n";
		}
		delete myItem;
		return true;
	}
	else
	{
		std::cout << "RPGItem Test 2: FAILED\n";
		delete myItem;
		return false;
	}
}

bool RPGTest::testRPGItem3(bool quiet)
{//Tests getters and setters for m_description variable
	RPGItem* myItem = new RPGItem();
	myItem->setDescription("TestDescription");
	if (myItem->getDescription() == "TestDescription")
	{
		if (!quiet)
		{
			std::cout << "RPGItem test 3: PASSED\n";
		}
		delete myItem;
		return true;
	}
	else
	{
		std::cout << "RPGItem test 3: FAILED\n";
		delete myItem;
		return false;
	}
}

bool RPGTest::testRPGItem4(bool quiet)
{
	RPGItem* myItem = new RPGItem();
	myItem->setValue(1337);
	if (myItem->getValue() == 1337)
	{
		if (!quiet)
		{
			std::cout << "RPGItem test 4: PASSED\n";
		}
		delete myItem;
		return true;
	}
	else
	{
		std::cout << "RPGItem test 4: FAILED\n";
		return false;
	}
}

bool RPGTest::testRPGItem5(bool quiet)
{
	RPGItem* myItem = new RPGItem();
	myItem->setId(1337);
	if (myItem->getId() == 1337)
	{
		if (!quiet)
		{
			std::cout << "RPGItem test 5: PASSED\n";
		}
		delete myItem;
		return true;
	}
	else
	{
		std::cout << "RPGItem test 5: FAILED\n";
		return false;
	}
}

bool RPGTest::testTile1(bool quiet)
{
	Tile* myTile = new Tile();
	if (  (myTile->getCanTravel()) && (myTile->getShow() == 'W') && (myTile->getSpriteBackground().compare("") == 0) && (myTile->getSpriteForeground().compare("") == 0))
	{
		if (!quiet)
		{
			std::cout << "Tile test 1: PASSED\n";
		}
		delete myTile;
		return true;
	}
	else
	{
		std::cout << "Tile test 1: FAILED\n";
		delete myTile;
		return false;
	}
}

bool RPGTest::testTile2(bool quiet)
{
	Tile* myTile = new Tile();
	myTile->setCanTravel(true);
	if (myTile->getCanTravel())
	{
		if (!quiet)
		{
			std::cout << "Tile test2: PASSED\n";
		}
		delete myTile;
		return true;
	}
	else
	{
		std::cout << "Tile test 2: FAILED\n";
		delete myTile;
		return false;
	}
}

bool RPGTest::testTile3(bool quiet)
{
	Tile* myTile = new Tile();
	myTile->setCanTravel(false);
	if (!(myTile->getCanTravel()))
	{
		if (!quiet)
		{
			std::cout << "Tile test 3: PASSED\n";
		}
		delete myTile;
		return true;
	}
	else
	{
		std::cout << "Tile test 3: FAILED\n";
		delete myTile;
		return false;
	}
}

bool RPGTest::testTile4(bool quiet)
{
	Tile* myTile = new Tile();
	myTile->setShow('X');
	if (myTile->getShow() == 'X')
	{
		if (!quiet)
		{
			std::cout << "Tile test 4: PASSED\n";
		}
		delete myTile;
		return true;
	}
	else
	{
		std::cout << "Tile test 4: FAILED\n";
		delete myTile;
		return false;
	}
}

bool RPGTest::testTile5(bool quiet)
{
	Tile* myTile = new Tile();
	myTile->setSpriteBackground("/pixels/Bgtile/Grass1.png");
	if (myTile->getSpriteBackground().compare("/pixels/Bgtile/Grass1.png") == 0)
	{
		if (!quiet)
		{
			std::cout << "Tile test 5: PASSED\n";
		}
		delete myTile;
		return true;
	}
	else
	{
		std::cout << "Tile test 5: FAILED\n";
		delete myTile;
		return false;
	}
}

bool RPGTest::testTile6(bool quiet)
{
	Tile* myTile = new Tile();
	myTile->setSpriteForeground("/pixels/Bgtile/Grass1.png");
	if (myTile->getSpriteForeground().compare("/pixels/Bgtile/Grass1.png") == 0)
	{
		if (!quiet)
		{
			std::cout << "Tile test 6: PASSED\n";
		}
		delete myTile;
		return true;
	}
	else
	{
		std::cout << "Tile test 6: FAILED\n";
		delete myTile;
		return false;
	}
}

bool RPGTest::testDamage1(bool quiet)
{
  Damage* myDamage = new Damage();
  {
    for (int i = 0; i < 30; i++)
    {
      if (myDamage->content[i] != 0)
      {
        std::cout << "Damage Test 1: FAILED\n";
        delete myDamage;
        return false;
      }
    }
    if(!quiet)
    {
      std::cout << "Damage Test 1: PASSED\n";
    }
    delete myDamage;
    return true;
  }
}

bool RPGTest::testDamage2(bool quiet)
{
  Damage* myDamage = new Damage();
  for (int i = 0; i < 30; i++)//loads damage into the array
  {
    myDamage->content[i] = ((i * 2) + (i%5));
  }
  for (int i = 0; i < 30; i++)//Testing that the array was loaded properly
  {
    if (myDamage->content[i] != ((i * 2) + (i % 5)))
    {
      std::cout << "Damage Test 2: FAILED\n";
      delete myDamage;
      return false;
    }
  }
  if (!quiet)
  {
    std::cout << "Damage Test 2: PASSED\n";
    delete myDamage;
    return true;
  }
}

bool RPGTest::testArmor1(bool quiet)
{
  Armor* myArmor = new Armor();
  for (int i = 0; i < Damage::size; i++)
  {
    if (myArmor->getDefense().content[i] != 0)
    {
      std::cout << "Armor Test 1: FAILED\n";
      delete myArmor;
      return false;
    }
  }
  if (!myArmor->getLegs() && !myArmor->getTorso() && !myArmor->getArms() && !myArmor->getHead() && !myArmor->getRing())
  {
    if (!quiet)
    {
      std::cout << "Armor Test 1: PASSED\n";
    }
    delete myArmor;
    return true;
  }
  else
  {
    std::cout << "Armor Test 1: FAILED\n";
    delete myArmor;
    return false;
  }
}

bool RPGTest::testArmor2(bool quiet)
{
  Armor* myArmor = new Armor();
  myArmor->setLegs(true);
  if (!myArmor->getLegs())
  {
    std::cout << "Armor Test 2: FAILED\n";
    delete myArmor;
    return false;
  }
  myArmor->setLegs(false);
  if (myArmor->getLegs())
  {
    std::cout << "Armor Test 2: FAILED\n";
    delete myArmor;
    return false;
  }
  else
  {
    if (!quiet)
    {
      std::cout << "Armor Test 2: PASSED\n";
    }
    delete myArmor;
    return true;
  }
}

bool RPGTest::testArmor3(bool quiet)
{
  Armor* myArmor = new Armor();
  myArmor->setTorso(true);
  if (!myArmor->getTorso())
  {
    std::cout << "Armor Test 3: FAILED\n";
    delete myArmor;
    return false;
  }
  myArmor->setTorso(false);
  if (myArmor->getTorso())
  {
    std::cout << "Armor Test 3: FAILED\n";
    delete myArmor;
    return false;
  }
  else
  {
    if (!quiet)
    {
      std::cout << "Armor Test 3: PASSED\n";
    }
    delete myArmor;
    return true;
  }
}

bool RPGTest::testArmor4(bool quiet)
{
  Armor* myArmor = new Armor();
  myArmor->setArms(true);
  if (!myArmor->getArms())
  {
    std::cout << "Armor Test 4: FAILED\n";
    delete myArmor;
    return false;
  }
  myArmor->setArms(false);
  if (myArmor->getArms())
  {
    std::cout << "Armor Test 4: FAILED\n";
    delete myArmor;
    return false;
  }
  else
  {
    if (!quiet)
    {
      std::cout << "Armor Test 4: PASSED\n";
    }
    delete myArmor;
    return true;
  }
}

bool RPGTest::testArmor5(bool quiet)
{
  Armor* myArmor = new Armor();
  myArmor->setHead(true);
  if (!myArmor->getHead())
  {
    std::cout << "Armor Test 5: FAILED\n";
    delete myArmor;
    return false;
  }
  myArmor->setHead(false);
  if (myArmor->getHead())
  {
    std::cout << "Armor Test 5: FAILED\n";
    delete myArmor;
    return false;
  }
  else
  {
    if (!quiet)
    {
      std::cout << "Armor Test 5: PASSED\n";
    }
    delete myArmor;
    return true;
  }
}

bool RPGTest::testArmor6(bool quiet)
{
  Armor* myArmor = new Armor();
  myArmor->setRing(true);
  if (!myArmor->getRing())
  {
    std::cout << "Armor Test 6: FAILED\n";
    delete myArmor;
    return false;
  }
  myArmor->setRing(false);
  if (myArmor->getRing())
  {
    std::cout << "Armor Test 6: FAILED\n";
    delete myArmor;
    return false;
  }
  else
  {
    if (!quiet)
    {
      std::cout << "Armor Test 6: PASSED\n";
    }
    delete myArmor;
    return true;
  }
}

bool RPGTest::testArmor7(bool quiet)
{
  Armor* myArmor = new Armor;
  Damage* myDamage = new Damage;
  for (int i = 0; i < Damage::size; i++)
  {
    myDamage->content[i] = ((i * 4) + (i % 5));
  }
  myArmor->setDefense(*myDamage);
  for (int i = 0; i < Damage::size; i++)
  {
    if (myArmor->getDefense().content[i] != ((i * 4) + (i % 5)))
    {
      std::cout << "Armor Test 7: FAILED\n";
      delete myArmor;
      return false;
    }
  }
  if (!quiet)
  {
    std::cout << "Armor Test 7: PASSED\n";
  }
  delete myArmor;
  return true;
}

bool RPGTest::testWeapon1(bool quiet)
{
  Weapon* myWeapon = new Weapon();
  for (int i = 0; i < Damage::size; i++)
  {
    if (myWeapon->getAddedDamage().content[i] != 0)
    {
      std::cout << "Weapon Test 1: FAILED\n";
      delete myWeapon;
      return false;
    }
  }
  if (!myWeapon->getRightHand() || myWeapon->getLeftHand())
  {
    std::cout << "Weapon Test 1: FAILED\n";
    delete myWeapon;
    return false;
  }
  else
  {
    if (!quiet)
    {
      std::cout << "Weapon Test 1: PASSED\n";
    }
    delete myWeapon;
    return true;
  }
}

bool RPGTest::testWeapon2(bool quiet)
{
  Weapon* myWeapon = new Weapon();
  Damage* myDamage = new Damage();
  for (int i = 0; i < Damage::size; i++)
  {
    myDamage->content[i] = ((i * 3) + (i % 5));
  }
  myWeapon->setAddedDamage(*myDamage);
  for (int i = 0; i < Damage::size; i++)
  {
    if (myWeapon->getAddedDamage().content[i] != ((i * 3) + (i % 5)))
    {
      std::cout << "Weapon Test 2: FAILED\n";
      delete myWeapon;
      return false;
    }
  }
  if (!quiet)
  {
    std::cout << "Weapon Test 2: PASSED\n";
    delete myWeapon;
    return true;
  }
}

bool RPGTest::testWeapon3(bool quiet)
{
  Weapon* myWeapon = new Weapon();
  myWeapon->setRightHand(true);
  if (!myWeapon->getRightHand())
  {
    std::cout << "Weapon Test 3: FAILED\n";
    delete myWeapon;
    return false;
  }
  myWeapon->setRightHand(false);
  if (myWeapon->getRightHand())
  {
    std::cout << "Weapon Test 3: FAILED\n";
    delete myWeapon;
    return false;
  }
  if (!quiet)
  {
    std::cout << "Weapon Test 3: PASSED\n";
  }
  delete myWeapon;
  return true;
}

bool RPGTest::testWeapon4(bool quiet)

{
  Weapon* myWeapon = new Weapon();
  myWeapon->setLeftHand(true);
  if (!myWeapon->getLeftHand())
  {
    std::cout << "Weapon Test 4: FAILED\n";
    delete myWeapon;
    return false;
  }
  myWeapon->setLeftHand(false);
  if (myWeapon->getLeftHand())
  {
    std::cout << "Weapon Test 4: FAILED\n";
    delete myWeapon;
    return false;
  }
  if (!quiet)
  {
    std::cout << "WeaponTest 4: PASSED/n";
  }
  delete myWeapon;
  return true;
}