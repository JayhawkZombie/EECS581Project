#ifndef SFENGINE_UI_ICON_SHEET_H
#define SFENGINE_UI_ICON_SHEET_H

#include <map>
#include <string>
#include <SFML\Graphics.hpp>

namespace Engine
{

  namespace UI
  {

    extern std::map<std::string, sf::IntRect> IconSheetRects;
    void LoadIconSheet(const std::string &SheetMapPath);
  }

}

#endif