#include "Headers\Engine\Engine.h"
#include "../../Game/RPGTest.h"
#include "../../Game/GameMain.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char **argv)
{
  Engine::SFEngine GameEngine;
  GameMain::run();
  return (GameEngine.Go(argc, argv));
}


