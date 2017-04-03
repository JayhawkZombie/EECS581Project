#ifndef SFENGINE_THOR_UTILS_H
#define SFENGINE_THOR_UTILS_H

#include <SFML\Graphics.hpp>
#include <Thor\Animations.hpp>

namespace Engine
{

  void CreateFrameAnimation(thor::AnimationMap<sf::Sprite, std::string> &AnimMap, std::string AnimName, sf::Time AnimDuration) {
    thor::FrameAnimation fAnim;
    AnimMap.addAnimation(AnimName, fAnim, AnimDuration);
  }

  void AddFramesToFrameAnimation(thor::FrameAnimation &fAnim, const std::vector<sf::IntRect> &Frames) {
    
  }

}

#endif
