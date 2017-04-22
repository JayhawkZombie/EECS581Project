#ifndef SFENGINE_TYPES_H
#define SFENGINE_TYPES_H

#include <cstdint>
#include <memory>
#include <mutex>

#include <SFML\Graphics.hpp>

#if defined( _M_X64 ) || defined ( _M_ARM64 ) || defined ( _WIN64 )
#    define SPLATFORM_X64
#    define MAX_REGISTER_LEN 64
#elif defined ( _M_IX86 ) || defined ( _WIN32 )
#    define SPLATFORM_X86
#    define MAX_REGISTER_LEN 32
#endif

#ifdef SPLATFORM_X64
#include "DefsX64.h"
#else
#include "DefsX86.h"
#endif

using SharedTexture = std::shared_ptr<sf::Texture>;

template<typename T>
using SPtrShared = std::shared_ptr<T>;

using SPtrSharedMutex = SPtrShared<std::mutex>;

using STexture = SPtrShared<sf::Texture>;
using STextureMap = std::map<std::string, STexture>;

template<typename T>
using SPtrUnique = std::unique_ptr<T>;

using SClockHigh = std::chrono::high_resolution_clock;
using SClockSys = std::chrono::system_clock;

#endif
