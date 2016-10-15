#include "../../Headers/Level/Layer.h"

namespace Engine
{

  LevelLayer::LevelLayer()
  {
    BGSprite = new sf::Sprite;
  }

  LevelLayer::~LevelLayer()
  {
    delete BGSprite;
  }

  void LevelLayer::MakeSpriteWithBG()
  {
    BGSprite->setTexture(BackgroundTexture.getTexture());
  }

  LevelLayer::LevelLayer(const LevelLayer &layer)
  {
    LayerSprites = layer.LayerSprites;
    BackgroundTexture.clear();

    //We can only get a read-only reference to the render texture,
    //so draw the texture to a sprite, and then draw that sprite onto the
    //render texture of the copied layer
    sf::Sprite spr;
    spr.setTexture(layer.BackgroundTexture.getTexture());

    BackgroundTexture.draw(spr);
  }

}
