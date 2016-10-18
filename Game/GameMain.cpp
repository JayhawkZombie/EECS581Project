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
	std::cout << "ITS WORKING!\n";
	RPGTest::runTests(true);
	return 0;
}
