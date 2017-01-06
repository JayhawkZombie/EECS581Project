#include "../../Headers/Level/Level.h"

namespace Engine
{
  void Level::Render()
  {
    
    for (auto & loader : Loaders)
    {
      loader->TestRender();
    }

  }

  void Level::RenderRegular()
  {
    
  }

  void Level::RenderLoadingScreen()
  {
    
  }

}
