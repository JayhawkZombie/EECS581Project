#include "GameMain.h"
#include "RPGTest.h"
#include <iostream>
#include "ListReader.h"
#include "MainCharacter.h"
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
	MainCharacter* mchar = new MainCharacter();
	ListReader list;
	list.readConversation("ConvoJohnWakeUp.txt",*(mchar));
	list.menu();
	delete mchar;
	return 0;
}
