#ifndef SFENGINE_LEVEL_LAYER_H
#define SFENGINE_LEVEL_LAYER_H

#include "../BasicIncludes.h"

namespace Engine
{
  struct LevelLayer
  {
    LevelLayer();
    LevelLayer(const LevelLayer &layer);
    ~LevelLayer();
    void MakeSpriteWithBG();

    sf::Sprite *BGSprite;

    std::vector<std::shared_ptr<sf::Sprite>> LayerSprites;
    sf::RenderTexture BackgroundTexture;
  };
}

#endif
