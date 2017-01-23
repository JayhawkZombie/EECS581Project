#include "../../Headers/Engine/Engine.h"

namespace Engine
{

  void SFEngine::BindScripts()
  {
    //Bind Engine scripts
    EngineModule = chaiscript::ModulePtr(new chaiscript::Module);
    EngineModule->add(chaiscript::fun(&SFEngine::SetBrightness, this), "SetBrightness");
    EngineModule->add(chaiscript::fun(&SFEngine::SetAALevel, this), "SetAALevel");
    EngineModule->add(chaiscript::fun(&SFEngine::SetContrast, this), "SetContrast");
    EngineModule->add(chaiscript::fun(&SFEngine::SetGamma, this), "SetGamma");

    ScriptEngine->add(EngineModule);

    //Bind GenericActor scripts
    chaiscript::ModulePtr __ActorPtr = chaiscript::ModulePtr(new chaiscript::Module);
    GenericActor::BindScriptMethods(__ActorPtr);
    (*ScriptEngine).add(__ActorPtr);

    //Bind Level scripts

    //Bind LevelObject scripts
    (*ScriptEngine).add(chaiscript::fun(static_cast<void(Player::*)()>(&Player::KeyDownPressed)), "KeyDownPressed");
    (*ScriptEngine).add(chaiscript::fun(static_cast<void(Player::*)()>(&Player::KeyUpPressed)), "KeyUpPressed");
    (*ScriptEngine).add(chaiscript::fun(static_cast<void(Player::*)()>(&Player::KeyRightPressed)), "KeyRightPressed");
    (*ScriptEngine).add(chaiscript::fun(static_cast<void(Player::*)()>(&Player::KeyLeftPressed)), "KeyLeftPressed");
    (*ScriptEngine).add(chaiscript::fun(static_cast<void(Player::*)(float, float)>(&Player::ForcePosition)), "ForcePosition");
    (*ScriptEngine).add(chaiscript::fun(static_cast<float(Player::*)()>(&Player::GetPositionX)), "GetPositionX");
    (*ScriptEngine).add(chaiscript::fun(static_cast<float(Player::*)()>(&Player::GetPositionY)), "GetPositionY");

    //Bind SFML scripts
    chaiscript::ModulePtr __SFML = chaiscript::ModulePtr(new chaiscript::Module);
    __SFML->add(chaiscript::user_type<sf::Vector2f>(), "Vector2f");
    __SFML->add(chaiscript::user_type<sf::IntRect>(), "IntRect");
    __SFML->add(chaiscript::user_type<sf::FloatRect>(), "FloatRect");
    __SFML->add(chaiscript::user_type<sf::Keyboard::Key>(), "KeyboardKey");
    

    (*ScriptEngine).add(__SFML);
  }

}
