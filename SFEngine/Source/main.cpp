#include "Headers\Engine\Engine.h"
#include "../../Game/RPGTest.h"
#include "../../Game/GameMain.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include "CoreTests\TestDefs.h"

//If doing engine tests, let Catch provide its own main and run the unit tests
//otherwise run the engine like normal
#if ENGINE_TESTS
#include "CoreTests\CoreTests.h"
#else

int main(int argc, char **argv)
{
  GameMain::run();

  Engine::SFEngine GameEngine;
  return (GameEngine.Go(argc, argv));
}
#endif


