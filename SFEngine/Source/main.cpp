#include "Headers\Engine\Engine.h"
#include "../../Game/RPGTest.h"
#include "../../Game/GameMain.h"

//If doing engine tests, let Catch provide its own main and run the unit tests
//otherwise run the engine like normal
#if ENGINE_TESTS
#include "CoreTests\CoreTests.h"
#else

int main(int argc, char **argv)
{
  //Your tests are blocking. Please don't leave them in
  //GameMain::run();

  Engine::SFEngine GameEngine;
  return (GameEngine.Go(argc, argv));
}
#endif


