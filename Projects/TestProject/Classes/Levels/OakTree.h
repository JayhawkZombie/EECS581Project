#ifndef GAME_LEVEL_OAK_TREE_H
#define GAME_LEVEL_OAK_TREE_H

#include "../../../../SFEngine/Source/Headers/Level/BasicLevel.h"
#include "../../../../SFEngine/Source/Headers/Globals/GlobalHooks.h"
#include "../../../../SFEngine/Source/Headers/Physics/Collider.h"

class OakTreeLevel : public Engine::BasicLevel
{
public:
  OakTreeLevel();
  OakTreeLevel(const sf::Vector2u &LevelSize, const sf::FloatRect &DefaultView, bool showlines = false, const sf::Vector2f &GridSpacing = { 0,0 });

  void TickUpdate(const double &delta) override;
  void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture) override;
  void HandleInputEvent(const Engine::UserEvent &evnt) override;

protected:
	std::shared_ptr<Engine::GenericActor> MainCharacter;
};

#endif
