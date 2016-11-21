#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <vector>
#include <memory>
#include <functional>
#include <thread>
#include <string>
#include <chrono>
#include <random>
#include <cassert>
#include <unordered_map>
#include <bitset>

#include "EngineTypes.h"
#include "Events\EventHandler.h"
#include "Globals\GlobalHooks.h"
#include "Utils\ReadIni.h"
#include "Utils\Convert.h"

#include "Render\Render.h"



#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../../ThirdParty/chaiscript/chaiscript_defines.hpp"
#include "../../ThirdParty/chaiscript/chaiscript.hpp"
#include "../../ThirdParty/chaiscript/chaiscript_stdlib.hpp"

#define SFENGINE_INTERNAL_DEPRECATED __declspec(deprecated)
#define SFENGINE_DEPRECATED __declspec(deprecated)
