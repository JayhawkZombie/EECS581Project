#include "OakTree.h"
#include "../../../../SFEngine/Source/Headers/Level/LevelObject.h"
#include <map>

OakTreeLevel::OakTreeLevel()
 : BasicLevel({ 1200,1200 }, { 0,0,800,800 })//: BasicLevel({ 50 * 16, 50 * 16 }, { 28 * 16, 18 * 16, 9 * 16, 9 * 16 }) //:BasicLevel({ 144,144 }, { 0,0,144,144 })//
{
  LoadFromFile("./Projects/TestProject/testproject.json");
  /*
  std::shared_ptr <Engine::LevelObject> Tree = std::make_shared<Engine::LevelObject>();
  std::shared_ptr <Engine::LevelObject> Shop = std::make_shared<Engine::LevelObject>();

  Tree->SetTexture(Textures["Oaktree"]);
  Tree->SetPosition({ 0,0 });
  LevelObjects["Oaktree"] = Tree;

  Shop->SetTexture(Textures["5by5Shops"]);
  Shop->SetTextureRect({ 0,0,80,80 });
  Shop->SetPosition({ 0,144 });
  */

  //Declaration of the Buildings
  std::shared_ptr <Engine::LevelObject> Barracks = std::make_shared<Engine::LevelObject>(); //Barracks Declaration
  std::shared_ptr <Engine::LevelObject> TownHall = std::make_shared<Engine::LevelObject>(); //TownHall Declaration
  std::shared_ptr <Engine::LevelObject> Church = std::make_shared<Engine::LevelObject>();  //Church Declaration
  std::shared_ptr <Engine::LevelObject> ItemShop = std::make_shared<Engine::LevelObject>(); //ItemShop Declaration
  std::shared_ptr <Engine::LevelObject> ArmorShop = std::make_shared<Engine::LevelObject>();//ArmorShop Declaration

  //Declaration of The Trees-Texture Set of the Trees
  std::map<int, std::shared_ptr <Engine::LevelObject>> Trees;//Declares an array of trees -these will be the 5x5 tree blocks for filler
  std::shared_ptr <Engine::LevelObject> BigOakTreeTree = std::make_shared<Engine::LevelObject>(); //Declares The big tree in the middle of town
  for (int i = 0; i <= 15; i++)//Declares/gives textures to all of the big tree blocks
  {
    Trees[i] = std::make_shared<Engine::LevelObject>();
    Trees[i]->SetTexture(Textures["TreeBlock"]);
  }
  BigOakTreeTree->SetTexture(Textures["Bigoaktree"]);//sets the texture for the big oak tree in the middle of town
  BigOakTreeTree->SetTextureRect({ 0,0,144,144 });

  //Position Set of the Trees
  for (int i = 0; i <= 8; i++)
  {
    Trees[i]->SetPosition({ 0, (float) i*16*5 });
  }
  Trees[9]->SetPosition({ 16 * 5,0 });
  Trees[10]->SetPosition({ 16 * 5,16 * 5 });
  Trees[11]->SetPosition({ 16 * 10,0 });
  Trees[12]->SetPosition({ 16 * 10,16 * 5 });
  Trees[13]->SetPosition({ 16 * 15,0 });
  Trees[14]->SetPosition({ 16 * 15,16 * 5 });
  Trees[15]->SetPosition({ 16 * 20,0 });
  BigOakTreeTree->SetPosition({ 20 * 16,19 * 16 });

  //Sets the Textures and the positions of the buildings
  Barracks->SetTexture(Textures["BigBuildings"]);
  Barracks->SetTextureRect({ 112,80,112,80 });
  Barracks->SetPosition({ 7 * 16,14 * 16 });

  TownHall->SetTexture(Textures["BigBuildings"]);
  TownHall->SetTextureRect({ 0,80,112,80 });
  TownHall->SetPosition({ 6 * 16,23 * 16 });

  Church->SetTexture(Textures["Church"]);//may be a bad idea to double use 'church'
  Church->SetPosition({ 22 * 16,6 * 16 });

  ItemShop->SetTexture(Textures["5by5Shops"]);
  ItemShop->SetTextureRect({ 0 , 80, 80 ,80 });
  ItemShop->SetPosition({ 9 * 16 , 34 * 16 });

  ArmorShop->SetTexture(Textures["5by5Shops"]);
  ArmorShop->SetTextureRect({ 80,80,80,80 });
  ArmorShop->SetPosition({ 15 * 16,34 * 16 });

  LevelObjects["BarracksObj"] = Barracks;
  LevelObjects["TownHallObj"] = TownHall;
  LevelObjects["ChurchObj"] = Church;
  LevelObjects["ItemShopObj"] = ItemShop;
  LevelObjects["ArmorShopObj"] = ArmorShop;
  LevelObjects["Trees0"] = Trees[0];
  LevelObjects["Trees1"] = Trees[1];
  LevelObjects["Trees2"] = Trees[2];
  LevelObjects["Trees3"] = Trees[3];
  LevelObjects["Trees4"] = Trees[4];
  LevelObjects["Trees5"] = Trees[5];
  LevelObjects["Trees6"] = Trees[6];
  LevelObjects["Trees7"] = Trees[7];
  LevelObjects["Trees8"] = Trees[8];
  LevelObjects["Trees9"] = Trees[9];
  LevelObjects["Trees10"] = Trees[10];
  LevelObjects["Trees11"] = Trees[11];
  LevelObjects["Trees12"] = Trees[12];
  LevelObjects["Trees13"] = Trees[13];
  LevelObjects["Trees14"] = Trees[14];
  LevelObjects["Trees15"] = Trees[15];
  LevelObjects["BigOakTree"] = BigOakTreeTree;
  


//  LevelObjects["Shop1"] = Shop;
  //Shop

    
}

OakTreeLevel::OakTreeLevel(const sf::Vector2u & LevelSize, const sf::FloatRect & DefaultView, bool showlines, const sf::Vector2f & GridSpacing)
  : BasicLevel(LevelSize, DefaultView, showlines, GridSpacing)
{
		
}

void OakTreeLevel::TickUpdate(const double & delta)
{
}

void OakTreeLevel::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
  /*
  sf::View _view;
  _view.setViewport(CurrentView);

  sf::View oldView = Texture->getView();

  Texture->setView(_view);

  SceneBlendTexture->clear(sf::Color::Transparent);

  if (ShowGridLines) {
    for (auto & arr : GridLines)
      Texture->draw(arr);
  }
  */
  for (auto & obj : LevelObjects)
    obj.second->Render(Texture);

  //If we are using the editor, draw the meshes too
  //Make this configurable later

 // Texture->setView(oldView);
}
