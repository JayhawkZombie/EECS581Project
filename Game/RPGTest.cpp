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
	if (  (myItem->getName().compare("")) && (myItem->getDescription().compare("") ) && (myItem->getValue() == 0) && (myItem->getId() == 0)  )
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
	}
}