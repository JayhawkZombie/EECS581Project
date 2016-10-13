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
	std::cin >> choice;
	std::cout << choice;
	return 0;
}
