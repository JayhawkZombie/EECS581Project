#include "GameMain.h"
#include "RPGTest.h"
#include <iostream>

GameMain::GameMain()
{
}


GameMain::~GameMain()
{
}

int GameMain::run()
{
	int choice;
	std::cout << "ITS WORKING!\n";
	RPGTest::runTests(true);
	return 0;
}
