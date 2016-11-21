#include "../../Headers/Level/Level.h"

namespace Engine
{
  void Level::Render()
  {
    ResourceLock->lock();

    if (!ReadyToPlay)
      RenderLoadingScreen();
    else
      RenderRegular();

    ResourceLock->unlock();
  }

  void Level::RenderRegular()
  {
    Environment.DiagnosticText.setFont(*LevelFont);
    Environment.Render();
    Render::RenderText(&Environment.DiagnosticText);
  }

  void Level::RenderLoadingScreen()
  {
    
  }

}
