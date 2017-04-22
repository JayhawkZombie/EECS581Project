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


#include "Globals\GlobalHooks.h"
#include "EngineTypes.h"
#include "Utils\ReadIni.h"
#include "Utils\Convert.h"
#include "Utils\Encoders.h"
#include "Utils\Decoders.h"
#include "Utils\Vec.hpp"
#include "Utils\ListTemplates.h"
#include "Render\Render.h"
#include "Threading\ASyncLoader.h"
#include "Exceptions\Exceptions.h"

#include "SFengine\ThirdParty\json\json.h"

#include <SFML/OpenGL.hpp>


#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>

#ifdef _MSC_EXTENSIONS
#define SFENGINE_INTERNAL_DEPRECATED __declspec(deprecated)
#define SFENGINE_DEPRECATED __declspec(deprecated)
#define SFENGINE_INLINE __inline
#define SFENGINE_FORCEINLINE __forceinline

#define ASM __asm
#define ABSTRACT abstract

#else


#define SFENGINE_INTERNAL_DEPRECATED [[deprecated]]
#define SFENGINE_DEPRECATED [[deprecated]]
#define SFENGINE_INLINE inline
#define SFENGINE_FORCEINLINE inline

typedef asm __asm
#define abstract 


#endif
