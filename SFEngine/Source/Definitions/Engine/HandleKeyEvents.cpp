#include "../../Headers/Engine/Engine.h"

std::map<sf::Keyboard::Key, std::string> KeyToString = {
  { sf::Keyboard::A, "A" },{ sf::Keyboard::B, "B" },{ sf::Keyboard::C, "C" },{ sf::Keyboard::D, "D" },{ sf::Keyboard::E, "E" }, 
  { sf::Keyboard::F, "F" },{ sf::Keyboard::G, "G" },{ sf::Keyboard::H, "H" },{ sf::Keyboard::I, "I" },{ sf::Keyboard::J, "J" },
  { sf::Keyboard::K, "K" },{ sf::Keyboard::L, "L" },{ sf::Keyboard::M, "M" },{ sf::Keyboard::N, "N" },{ sf::Keyboard::O, "O" },
  { sf::Keyboard::P, "P" },{ sf::Keyboard::Q, "Q" },{ sf::Keyboard::R, "R" },{ sf::Keyboard::S, "S" },{ sf::Keyboard::T, "T" },
  { sf::Keyboard::U, "U" },{ sf::Keyboard::V, "V" },{ sf::Keyboard::W, "W" },{ sf::Keyboard::X, "X" },{ sf::Keyboard::Y, "Y" },
  { sf::Keyboard::Z, "Z" },{ sf::Keyboard::Add, "Add" },{ sf::Keyboard::BackSlash, "Bkslsh" },{ sf::Keyboard::BackSpace, "Bckspc" },{ sf::Keyboard::Comma, "Comma" },
};

namespace Engine
{

  void SFEngine::HandleKeyPress(const sf::Keyboard::Key &k)
  {
    (*ScriptEngine).eval("Engine_KeyPressed(\"" + KeyToString[k] + "\")");
    std::string command{ "" };
    
    if (k == sf::Keyboard::Key::Up)
      command = "Up";
    else if (k == sf::Keyboard::Key::Down)
      command = "Down";
    else if (k == sf::Keyboard::Key::Left)
      command = "Left";
    else if (k == sf::Keyboard::Key::Right)
      command = "Right";

    if (command != "") {
      (*ScriptEngine).eval("Key" + command + "Pressed();");
    }

    if (k == sf::Keyboard::Escape)
      EngineUIController.ToggleShown();
    else
      EngineUIController.Handler.HandleKeyPress(k);

    for (auto & level : Levels) {
      level->Handler.HandleKeyPress(k);
    }
  }

  void SFEngine::HandleKeyRelease(const sf::Keyboard::Key &k)
  {
    EngineUIController.Handler.HandleKeyRelease(k);

    switch (k)
    {
      case sf::Keyboard::Num0:
        RenderSettings.PostProcess = 0;
        break;
      case sf::Keyboard::Num1:
        RenderSettings.PostProcess = 1;
        break;
      case sf::Keyboard::Num2:
        RenderSettings.PostProcess = 2;
        break;
      case sf::Keyboard::Num3:
        RenderSettings.PostProcess = 3;
        break;
    }

    Render::__Set__Render__Settings(RenderSettings);

    for (auto & level : Levels) {
      level->HandleKeyRelease(k);
    }
  }

}
