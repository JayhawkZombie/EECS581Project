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

void GameMain::Init(std::shared_ptr<Engine::Level> GameLevel)
{
  Level = GameLevel;
  LoadLevel();
}

void GameMain::LoadLevel()
{
  
}
