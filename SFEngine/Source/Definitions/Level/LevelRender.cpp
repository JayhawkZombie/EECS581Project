#include "../../Headers/Level/Level.h"

namespace Engine
{
  void Level::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
    static sf::IntRect scenerect;

    scenerect.left = static_cast<int>(std::floor(CurrentView.left));
    scenerect.top = static_cast<int>(std::floor(CurrentView.top));
    scenerect.width = static_cast<int>(std::ceil(CurrentView.width));
    scenerect.height = static_cast<int>(std::ceil(CurrentView.height));
   
    Target->draw(testrect);

    for (auto & seg : TestSegments)
      seg->draw(*currentRenderWindow);

    for (auto & hit : TestLevelMeshes)
      hit->draw(*Target);
    
    for (auto & arr : GridLines)
      Target->draw(arr);

    Target->draw(LevelRectangle);
  }

  void Level::RenderRegular()
  {

  }

  void Level::RenderLoadingScreen()
  {

  }

}