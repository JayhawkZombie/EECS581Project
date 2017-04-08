#ifndef TGUI_CALL
#define TGUI_CALL
#include <string>
#include <memory>
#include "../Inventory.h"
#include "CreateNewConvo.h"

class tguicall
{
public:
  tguicall();
  ~tguicall();
  void convo(std::string filename, MainCharacter mc);
  void shop(Inventory pinv, Inventory sinv);
  void status();
  void setTheme(std::string filename);

private:
  tgui::Theme::Ptr themePtr;
  //std::shared_ptr<NewShopCreator> ShopCreator;
  std::shared_ptr<NewConvoCreator> ConvoCreator;
 // tgui::Theme::Ptr UIThemePtr = std::make_shared<tgui::Theme>("./SFEngine/Source/CoreFiles/UIThemes/Black.txt");
 
};


#endif