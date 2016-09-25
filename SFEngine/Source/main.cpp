#include "Headers\Engine\Engine.h"

int main(int argc, char **argv)
{
  Engine::SFEngine GameEngine;

  return (GameEngine.Go(argc, argv));
}