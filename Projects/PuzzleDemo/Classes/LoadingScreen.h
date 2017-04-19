#ifndef GAME_LOADING_SCREEN_H
#define GAME_LOADING_SCREEN_H

#include "../../../SFEngine/ProjectIncludes.h"
#include "../../../SFEngine/Source/Headers/Weather/Lightning.h"

class LoadingScreen : public Engine::BasicLevel
{
public:
  LoadingScreen();
  ~LoadingScreen();

  std::string GetClass() const override final;
protected:

};

#endif
