#include "Headers\Engine\Engine.h"
#include "../../Game/RPGTest.h"
#include "../../Game/GameMain.h"
#include <windows.h>
int main(int argc, char **argv)
{

  Engine::SFEngine GameEngine;
	GameMain::run();
  return (GameEngine.Go(argc, argv));
  return 0;
}


