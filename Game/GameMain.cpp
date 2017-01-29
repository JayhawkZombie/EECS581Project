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
	MonsterType** myArray = list.readMonsters("Game/ContentFiles/MonsterTypes/MonsterTypes.txt");
	std::cout << "Myarray's length " << sizeof(myArray) << "\n";
	
	//for (int i = 0; i < sizeof(myArray); i++)
	for(int i=0; i<320; i++)
	{
		std::cout << "Index:            " << i << "\n";
		std::cout << "Name:             " << myArray[i]->getName() << "\n";
		std::cout << "Description:      " << myArray[i]->getDescription() << "\n";
		std::cout << "PrimaryElement:   " << myArray[i]->getPrimary() << "\n";
		std::cout << "SecondaryElement: " << myArray[i]->getSecondary() << "\n";
		std::cout << "EvolutionStage:   " << myArray[i]->getEvolutionStage() << "\n";
		std::cout << "EvolutionType:    " << myArray[i]->getEvolutionType() << "\n";
		std::cout << "Texture:          " << myArray[i]->getTexture() << "\n";
//		std::cout << "PhysicalEvolution:" << myArray[i]->getPhysicalEvolution() << "\n";
//		std::cout << "BalancedEvolution:" << myArray[i]->getBalancedEvolution() << "\n";
//		std::cout << "MagicalEvolution: " << myArray[i]->getMagicalEvolution() << "\n";

		std::cout << "\n\n";
	}
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