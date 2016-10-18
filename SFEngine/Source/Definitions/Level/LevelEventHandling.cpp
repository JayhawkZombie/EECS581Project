#include "../../Headers/Level/Level.h"

namespace Engine
{
  void Level::HandleKeyEvent(const sf::Keyboard::Key &key)
  {
    //std::cerr << "Level got key event!" << std::endl;

    //If the PlayerActor moved on top of a collision box, place the actor back at their old position
    //TODO: CORRECT movement instead of disallowing all movement
    //  ie PLACE ACTOR AT EDGE OF BOX

    static std::size_t currColor = 0;
    sf::Color colors[4] = { sf::Color::Blue, sf::Color::Red, sf::Color::Green, sf::Color::Magenta };

    if (key == sf::Keyboard::Num1)
      currColor = (currColor - 1) % 4;
    else if (key == sf::Keyboard::Num2)
      currColor = (currColor + 1) % 4;
    else if (key == sf::Keyboard::Num3)
      GlobalLight.SetIntensity(GlobalLight.GetIntensity() - 5);
    else if (key == sf::Keyboard::Num4)
      GlobalLight.SetIntensity(GlobalLight.GetIntensity() + 5);

    GlobalLight.SetColor(colors[currColor]);
    Render::AddGlobalLight(GlobalLight);



    if (PlayerActor.WantsInputEvent(Events::KeyPressed)) {
      PlayerActor.Handler.HandleKeyPress(key);
    }

  }

  void Level::CorrectActorMovement(const std::size_t &boxIndex)
  {

    sf::FloatRect FR = CollisionBoxes[boxIndex].GetBox();

    sf::FloatRect AC = PlayerActor.Collsion.GetBox();

    //TODO finish
    //For now, place actor at old position


  }
}
