#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include "../SFEngine/Source/Headers/BasicIncludes.h"
#include "../SFEngine/Source/Headers/Level/Level.h"

class GameMain
{
public:
	GameMain();
	~GameMain();
	static int run();

 // void Init(std::shared_ptr<Engine::Level> GameLevel);
 // void LoadLevel();

private:
//  std::shared_ptr<Engine::Level> Level;
  

	void printAssetStatus();

};

#endif
