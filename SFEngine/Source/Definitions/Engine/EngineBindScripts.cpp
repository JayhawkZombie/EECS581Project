#include "../../Headers/Engine/Engine.h"

#include "../../../ThirdParty/chaiscript/chaiscript_defines.hpp"
#include "../../../ThirdParty/chaiscript/chaiscript.hpp"
#include "../../../ThirdParty/chaiscript/chaiscript_stdlib.hpp"
#include "../../Headers/Engine/InputInterface.h"
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

    InputInterface::BindMethods(EngineModule);
    Level::BindMethods(EngineModule);
    LevelObject::BindScriptMethods(EngineModule);

    ScriptEngine->add(EngineModule);

    //Bind GenericActor scripts
    chaiscript::ModulePtr __ActorPtr = chaiscript::ModulePtr(new chaiscript::Module);
    GenericActor::BindScriptMethods(__ActorPtr);
    (*ScriptEngine).add(__ActorPtr);

    //Add scripts for constructing objects


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

    //Bind Vector2f "class"
    chaiscript::utility::add_class<sf::Vector2f>
      (
      *__SFML,
      "Vector2f",
       /* Constructors */
      { chaiscript::constructor<sf::Vector2f()>(),
        chaiscript::constructor<sf::Vector2f(float, float)>(),
        chaiscript::constructor<sf::Vector2f(const sf::Vector2f &)>()
      },
       /* Member functions */
      {
        {
          { chaiscript::fun(&sf::Vector2f::x), "x" },
          { chaiscript::fun(&sf::Vector2f::y), "y" }
        }
      }
      );

    chaiscript::utility::add_class<sf::IntRect>
      (
        *__SFML,
        "IntRect",
        /* Constructors */
        {
          chaiscript::constructor<sf::IntRect()>(),
          chaiscript::constructor<sf::IntRect(float, float, float, float)>()
        },
        {
          {
            { chaiscript::fun(&sf::IntRect::left), "left" },
            { chaiscript::fun(&sf::IntRect::top), "top" },
            { chaiscript::fun(&sf::IntRect::width), "width" },
            { chaiscript::fun(&sf::IntRect::height), "height" }
          }
        }
        );
    //__SFML->add(chaiscript::user_type<sf::Vector2f>(), "Vector2f");
    //__SFML->add(chaiscript::user_type<sf::IntRect>(), "IntRect");
    //__SFML->add(chaiscript::user_type<sf::FloatRect>(), "FloatRect");
    //__SFML->add(chaiscript::user_type<sf::Time>(), "SFTime");


    chaiscript::utility::add_class<sf::Time>
      (*__SFML,
       "SFTime",

       { chaiscript::constructor<sf::Time()>() },
       {
         {
           { chaiscript::fun(&sf::Time::asMicroseconds), "AsMilliseconds" },
           { chaiscript::fun(&sf::Time::asMicroseconds), "AsMicroseconds" },
           { chaiscript::fun(&sf::Time::asSeconds), "AsSeconds" }
         }
       }
       );
    chaiscript::utility::add_class<sf::Clock>
      (*__SFML,
       "SFClock",
       { chaiscript::constructor<sf::Clock()>() },
       {
         //Class methods
         {
           { chaiscript::fun(&sf::Clock::getElapsedTime), "GetElapsedTime" },
           { chaiscript::fun(&sf::Clock::restart), "Restart" }
         } 
       }
       );
    chaiscript::utility::add_class<sf::Color>
      ( *__SFML,
       "SFColor",
       { //Constructors
         chaiscript::constructor<sf::Color()>(),
         chaiscript::constructor<sf::Color(const sf::Color &color)>(),
         chaiscript::constructor<sf::Color(sf::Uint8, sf::Uint8, sf::Uint8, sf::Uint8)>()
       }, //"methods", but we're really making lambdas to access the class members
       {
         {
           { chaiscript::fun([](const sf::Color &c)->sf::Uint8 { return c.a; }), "a" },
           { chaiscript::fun([](const sf::Color &c)->sf::Uint8 { return c.r; }), "r" },
           { chaiscript::fun([](const sf::Color &c)->sf::Uint8 { return c.g; }), "g" },
           { chaiscript::fun([](const sf::Color &c)->sf::Uint8 { return c.b; }), "b" }
         }
       }
       );
    
    chaiscript::utility::add_class<sf::Keyboard::Key>
      (*__SFML,
       "sf_Keyboard_Key",
       {
         {sf::Keyboard::A, "Key_A"}, {sf::Keyboard::B, "Key_B"}, {sf::Keyboard::C, "Key_C"}, {sf::Keyboard::D, "Key_D"}, {sf::Keyboard::E, "Key_E"},
         {sf::Keyboard::F, "Key_F"}, {sf::Keyboard::G, "Key_G"}, {sf::Keyboard::H, "Key_H"}, {sf::Keyboard::I, "Key_I"}, {sf::Keyboard::J, "Key_J"},
         {sf::Keyboard::K, "Key_K"}, {sf::Keyboard::L, "Key_L"}, {sf::Keyboard::M, "Key_M"}, {sf::Keyboard::N, "Key_N"}, {sf::Keyboard::O, "Key_O"},
         {sf::Keyboard::P, "Key_P"}, {sf::Keyboard::Q, "Key_Q"}, {sf::Keyboard::R, "Key_R"}, {sf::Keyboard::S, "Key_S"}, {sf::Keyboard::T, "Key_T"},
         {sf::Keyboard::U, "Key_U"}, {sf::Keyboard::V, "Key_V"}, {sf::Keyboard::W, "Key_W"}, {sf::Keyboard::X, "Key_X"}, {sf::Keyboard::Y, "Key_Y"},
         {sf::Keyboard::Z, "Key_Z"}, {sf::Keyboard::Escape, "Key_Esc"}, {sf::Keyboard::Space, "Key_Space"}, {sf::Keyboard::LShift, "Key_LShift"},
         {sf::Keyboard::RShift, "Key_RShift"},
         {sf::Keyboard::Left, "Key_Left"}, {sf::Keyboard::Right, "Key_Right"}, {sf::Keyboard::Up, "Key_Up"}, {sf::Keyboard::Down, "Key_Down"}
       });
    

    (*ScriptEngine).add(__SFML);
  }

}
