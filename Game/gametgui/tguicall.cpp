#include "tguicall.h"

tguicall::tguicall()
{
}

tguicall::~tguicall()
{
}

void tguicall::convo(std::string filename, MainCharacter mc)
{
  ConvoCreator = std::make_shared<NewConvoCreator>();

  ConvoCreator->CreateConvoNode(filename, mc);
  ConvoCreator->OpenTheme(themePtr);
  
}

void tguicall::shop(Inventory pinv, Inventory sinv)
{
  
}

void tguicall::status()
{
}

void tguicall::setTheme(std::string filename)
{
  themePtr = std::make_shared<tgui::Theme>(filename);
}
