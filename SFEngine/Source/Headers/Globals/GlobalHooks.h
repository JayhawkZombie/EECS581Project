#ifndef SFENGINE_GLOBAL_HOOKS_H
#define SFENGINE_GLOBAL_HOOKS_H

#include <SFML\Graphics.hpp>
#include <algorithm>
#include <unordered_set>
#include "../Resources/ResourceManager.h"



//remove this to launch the engine without editing tools
#define WITH_EDITOR

#ifdef WITH_EDITOR
namespace Engine
{
  class Editor;
}
#define EDITOR_FRIEND \
friend class Editor; 

#define EDITOR_VISIBLE

#define EDITOR_VISIBLE_TYPE(Type,Name) \
EDITOR_VISIBLE \
Type Name;
#else
#define EDITOR_FRIEND
#define EDITOR_VISIBLE
#define EDITOR_VISIBLE_TYPE(Type,Name)\
Type Name;
#endif

#ifdef WITH_EDITOR

#define EDITORONLY_VAR(VarType, VarName)\
VarType VarName;


#else
#define EDITORONLY(VarType, VarName)
#endif //WITH_EDITOR -> EDITORONLY DEFINITION


#define ___INTERNAL__SLASH(S)\
/##S

#define ___INTERNAL__COMMENT \
___INTERNAL__SLASH(/)


#ifdef WITH_EDITOR

#define EDITOR_ONLY

#define EDITOR_ONLY_CODE_BEGIN \
if (true)\
{

#define EDITOR_ONLY_CODE_END \
} \


#else //#ifdef WITH_EDITOR

#define EDITOR_ONLY ___INTERNAL__COMMENT

#define EDITORONLY_CODE_BEGIN \
if(false){

#define EDITORONLY_CODE_END \
}

#endif //#ifdef WITH_EDITOR

//remove this to build the engine without debugging output
#define ENGINE_DEBUG


//Remove this to build the engine without the widget construction debugging output
#define WIDGET_CONSTRUCT_DEBUG_OUT

#ifdef WIDGET_CONSTRUCT_DEBUG_OUT
#define WIDGET_DEBUG_ONLY
#else
#define WIDGET_DEBUG_ONLY ___INTERNAL__COMMENT
#endif //ifdef WIDGET_CONSTRUCT_DEBUG_OUT



#ifdef ENGINE_DEBUG
#define DEBUG_ONLY
#define DEBUG_ONLY_CODE_BEGIN \
if (true)\
{

#define DEBUG_ONLY_CODE_END \
} \

#else //#ifdef ENGINE_DEBUG
#define DEBUG_ONLY ___INTERNAL__COMMENT

#define DEBUG_ONLY_CODE_BEGIN \
if (false)\
{

#define DEBUG_ONLY_CODE_END \
} \


#endif //#ifdef ENGINE_DEBUG



//Testing for microsoft extensions, there are some nice extensions we can use
#ifdef _MSC_EXTENSIONS

#define INLINE _inline
#define MSINLINE __inline
#define FORCEINLINE __forceinline
#define NOINLINE __declspec(noinline)
#define ABSTRACT abstract
#define SEALED sealed

#else

#define INLINE inline
#define MSINLINE inline
#define FORCEINLINE inline
#define NOINLINE
#define ABSTRACT
#define SEALED

#endif



#define MAKE_PARENT(ParentClass) \
typedef ParentClass Super



//EXTERN DECLARATIONS

namespace Engine
{
  extern sf::RenderWindow *currentRenderWindow;
  extern std::shared_ptr<Resource::ResourceManager> ResourceManager;
  extern std::shared_ptr<sf::Texture> DefaultTexture;
  extern sf::Vector2f WindowSize;
  extern std::unordered_set<std::uint32_t> UsedIDs; //IDs that have been used. Can search this to verify an ID has not been used already

  extern bool IsIDUsed(const std::uint32_t &ID);
  extern void FreeID(const std::uint32_t &ID); //Make an ID available for use again
  extern std::uint32_t GenerateID(); //Use to try to generate a unique ID. This will throw an IDException if it cannot generate one after a set number of attempts

  extern std::uint32_t MaxIDGenerationAttempts; //max # of times we will try to generate an ID for an item before giving up - defined in Widget.cpp

  //ENGINE GLOBAL API EXTERNS
  extern sf::Vector2u GetCurrentWindowSize();
  
  extern decltype(auto) GetCurrentOpenGLVersionMajor();
  extern decltype(auto) GetCurrentOpenGLVersionMinor();
  extern decltype(auto) GetCurrentAASetting();
  extern decltype(auto) GetCurrentContextSettings();
  extern decltype(auto) GetCurrentContext();
  extern decltype(auto) GetCurrentTexturePoolSize();
  extern decltype(auto) GetCurrentShaderPoolSize();
  extern decltype(auto) GetCurrentFramerateSetting();

  extern decltype(auto) GetIsGlobalShadingEnabled();
  extern decltype(auto) GetIsStaticShadingEnabled();
  extern decltype(auto) GetIsDynamicShadingEnabled();
  extern decltype(auto) GetIsStaticShadowingEnabled();
  extern decltype(auto) GetIsDynamicShadowingEnabled();
  extern decltype(auto) GetIsMultiThreadedLightingEnabled();
  extern decltype(auto) GetIsUsingPreComputedLightMaps();
  extern decltype(auto) GetCanPhysicsApproxCollision();

#ifdef WITH_EDITOR
  class SFEngine;
  extern SFEngine *CurrentEngine;
  extern bool FlagForClose;
  namespace UI {
    class BaseUIElement;
  };

  extern void AddUI(std::shared_ptr<Engine::UI::BaseUIElement> element);
#endif

  extern void SetKeyRepeatEnabled(bool);

}

//This is pretty hacky, and will be changed later
// Just used to flag that we need to close down (since we can't use a close button when in fullscreen mode)


#define __TO_FLOAT__(VAR)\
static_cast<float>(VAR)
#define __TO_INT__(VAR)\
static_cast<int>(VAR)
#define __INT_FROM_FLOAT__(VAR)\
static_cast<int>(std::round(VAR))
#define __UINT_FROM_FLOAT__(VAR)\
static_cast<std::uint32_t>(std::round(VAR))



#endif
