#include "..\..\Headers\Factory\Factory.h"
#include "../../../ThirdParty/json/json.h"
#include "../../Headers/Actor/Actor.h"
#include "../../Headers/Actor/Player.h"
#include "../../Headers/Animation/Animation.h"
#include "../../Headers/Level/Level.h"
#include "../../Headers/Tiles/LevelTile.h"
#include "../../Headers/Tiles/TileSheet.h"


namespace Engine
{

  std::shared_ptr<Engine::GenericActor> Factory::GenericActor(const Json::Value & jsonobj)
  {
    try
    {
      std::shared_ptr<Engine::GenericActor> Actor = std::make_shared<Engine::GenericActor>();

      return Actor;
    }
    catch (Json::Exception &e)
    {

    }
  }

  std::shared_ptr<Engine::Player> Factory::Player(const Json::Value & jsonobj)
  {
    try
    {
      std::shared_ptr<Engine::Player> Player = std::make_shared<Engine::Player>();

      return Player;
    }
    catch (Json::Exception &e)
    {

    }
  }

  std::shared_ptr<Engine::Level> Factory::Level(const Json::Value & jsonobj)
  {
    try
    {
      std::shared_ptr<Engine::Level> Level = std::make_shared<Engine::Level>();

      return Level;
    }
    catch (Json::Exception &e)
    {

    }
  }

  std::shared_ptr<Engine::TileSheet> Factory::TileSheet(const Json::Value & jsonobj)
  {
    try
    {
      std::shared_ptr<Engine::TileSheet> TileSheet = std::make_shared<Engine::TileSheet>();



      return TileSheet;
    }
    catch (Json::Exception &e)
    {

    }
  }

  std::shared_ptr<Engine::LevelTile> Factory::Tile(const Json::Value & jsonobj)
  {
    try
    {
      std::shared_ptr<Engine::LevelTile> LevelTile = std::make_shared<Engine::LevelTile>();

      return LevelTile;
    }
    catch (Json::Exception &e)
    {

    }
  }

  std::shared_ptr<Engine::Animation> Factory::Animation(const Json::Value & jsonobj)
  {
    try
    {
      std::shared_ptr<Engine::Animation> Animation = std::make_shared<Engine::Animation>();

      return Animation;
    }
    catch (Json::Exception &e)
    {

    }
  }

}
