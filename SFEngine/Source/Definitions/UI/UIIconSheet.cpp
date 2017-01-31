#include "../../Headers/UI/UIIconSheet.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace Engine
{

  namespace UI
  {

    std::map<std::string, sf::IntRect> IconSheetRects;

    void LoadIconSheet(const std::string &SheetMapPath)
    {
      std::ifstream in(SheetMapPath);

      if (!in) {
        std::cerr << "Unable to load Icon sheet map" << std::endl;
        return;
      }

      std::stringstream converter;
      std::string icon_ = "";
      std::string discard{ "" }, num1{ "" }, num2{ "" }, num3{ "" }, num4{ "" };
      int left{ 0 }, top{ 0 }, width{ 0 }, height{ 0 };

      while (in >> icon_) {
        in >> discard >> left >> top >> width >> height;

        std::cerr << icon_ << " -> { " << left << ", " << top << ", " << width << ", " << height << " }" << std::endl;
        IconSheetRects[icon_] = sf::IntRect(left, top, width, height);
      }
      in.close();
    }

  }

}
