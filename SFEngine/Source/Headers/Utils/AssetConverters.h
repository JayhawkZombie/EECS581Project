#ifndef SFENGINE_ASSET_CONVERTERS_H
#define SFENGINE_ASSET_CONVERTERS_H

//--DEFINE IN_GAME WHEN COOKING FOR RELEASE!!!
#ifndef IN_GAME //if we aren't actually launching a game (ie we are in the compiler)

#include "Encoders.h"
#include "ReadIni.h"

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <sstream>

#include <SFML/Graphics.hpp>

namespace Engine
{


  namespace Convert
  {


    void Level(const std::string &SourceIni);

    void Animation(const std::string &SourceIni);

    void Tile(const std::string &SourceIni);


  }


}

#endif


#endif
