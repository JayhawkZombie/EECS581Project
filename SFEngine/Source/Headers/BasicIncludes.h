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
#include "Globals\GlobalHooks.h"
#include "Utils\ReadIni.h"
#include "Utils\Convert.h"
#include "Utils\Encoders.h"
#include "Utils\Decoders.h"
#include "Utils\Vec.hpp"
#include "Render\Render.h"

#include <SFML/OpenGL.hpp>


#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>

#define SFENGINE_INTERNAL_DEPRECATED __declspec(deprecated)
#define SFENGINE_DEPRECATED __declspec(deprecated)
