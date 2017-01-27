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
	list.readConversation("Game/ContentFiles/Conversation/ConvoJohnWakeUp.txt",*(mchar));
	/*
	* int reply;
	* reply = list.readConversation(...);
	*/
	list.menu();
	delete mchar;
	return 0;
}

void GameMain::TickUpdate(const double &Delta)
{

}

void GameMain::Render(std::shared_ptr<sf::RenderTexture> Target)
{

}

/*
void GameMain::Init(std::shared_ptr<Engine::Level> GameLevel)
{
  Level = GameLevel;
  LoadLevel();
}

void GameMain::LoadLevel()
{
  

void GameMain::printAssetStatus()
{

}

*/