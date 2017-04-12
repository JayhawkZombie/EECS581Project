#include "OakTree.h"
#include "../../../../SFEngine/Source/Headers/Level/LevelObject.h"
#include "../../../../Game/RPGActor.h"
#include <map>

OakTreeLevel::OakTreeLevel()
 : BasicLevel({ 800,800 }, { 0,0,800,800 })//: BasicLevel({ 50 * 16, 50 * 16 }, { 28 * 16, 18 * 16, 9 * 16, 9 * 16 }) //:BasicLevel({ 144,144 }, { 0,0,144,144 })//
{
  LoadFromFile("./Projects/TestProject/testproject.json");

  //sf::Texture LayeredTree;
  //LayeredTree
  
  //sw::TileMap tileMap;
  /*
  tileMap.setSize({ 800,800 });
  tileMap.setGridSize({ 50,50 });
  */
  
  std::vector<unsigned char> levelData(100000);
  levelData = {

// row	  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 
  /*-1*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /* 0*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /* 1*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /* 2*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /* 3*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /* 4*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,16,16,16,16,16,17,17,17,17,17,17,17,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,
  /* 5*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,24,24,24,24,24,24,24,17,17,17,17,17,17,17,17,
  /* 6*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,24,17,17,17,17,17,24,17,17,17,17,17,17,17,17,
  /* 7*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,24,17,17,17,17,17,24,17,17,17,17,17,17,17,17,
  /* 8*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,17,17,17,17,17,17,17,17,17,17,17,17,17,24,17,17,17,17,17,24,17,17,17,17,17,17,17,17,
  /* 9*/ 17,17,17,17,17,17,17,17,17,17,17,17,16,17,17,17,17,17,17,17,16,20,17,17,17,17,17,17,17,17,17,17,17,17,16,24,24,24,24,24,24,24,17,17,17,17,17,17,17,17,
  /*10*/ 17,17,17,17,17,17,16,17,16,17,17,16,18,16,17,17,17,17,17,16,19,20,17,17,17,17,17,17,17,17,17,17,17,16, 0,14,14,11,15,15,15,15,17,17,17,17,17,17,17,17,
  /*11*/ 17,17,17,17,17,16,18,16,18,16,16,18,18,18,17,17,17,17,17,18,19,20,17,17,17,17,17,17,17,17,17,17,17, 0, 8,15,15,15,17,17,17,17,17,17,17,17,17,17,17,17,
  /*12*/ 17,17,17,17,16,19,19,19,19,19,19,19,19,19,19,17,17,17,16,18,19,20,17,17,17,17,17,17,17,17,17,17,16,13,15,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*13*/ 17,17,17,17,18,20,20,20,20,20,20,20,20,20,20,16,17,17,19,18,19,20,17,17,17,17,17,17,16,17,17,16, 0, 8,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*14*/ 17,17,17,17,19,20,17,17,17,17,17,17,17,20,20,19,16,16,20,18,19,20,20,20, 0, 2,20,20,20,17,16, 0, 8,15,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*15*/ 17,17,17,17,15,20,17,17,17,17,17,17,17,20,20,18,18,20,20,20,20,20,20,20, 3, 5,20,20,20,16, 0, 8,15,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*16*/ 17,17,17,17,17,20,17,17,17,17,17,17,17,20,15,18,18,20, 0, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 5,18,16,16,16,16,16,17,17,16,16,16,16,16,17,17,17,17,17,17,
  /*17*/ 17,17,17,17,16,20,17,17,17,17,17,17,17,20,16,19,15,20, 3, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 5,19,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*18*/ 17,17,17,17,18,20,17,17,17,17,17,17,17,20,20,19,16,20, 3, 5,26,17,17,17,17,17,17,17,26, 3, 5,20,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*19*/ 17,17,17,17,18,20,20,20,20, 9,20,20,20,20,20,18,19,20, 3, 5,26,17,17,17,17,17,17,17,26, 3, 5,20,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*20*/ 17,17,17,17,15,15,15,15,15, 6,14,14,14,14, 2,15,19,20, 3, 5,26,17,17,17,17,17,17,17,26, 3, 5,20,17,17,17,17,17,16,17,17,17,17,17,17,17,17,17,17,17,17,
  /*21*/ 17,17,17,17,17,16,16,16,16,20,20,20,20,20,13,16,19,20, 3, 5,26,17,17,17,17,17,17,17,26, 3, 5,20,17,17,17,17,17,18,17,17,17,17,17,17,17,17,17,17,17,17,
  /*22*/ 17,17,17,17,17,20,17,17,17,17,17,17,24,20, 6,14,14,14, 4, 5,26,17,17,17,17,17,17,17,26, 3, 5,20,18,13,18,18,18,18,16,16, 9,15,15,15,17,17,17,17,17,17,
  /*23*/ 17,17,17,17,17,20,17,17,17,17,17,17,24,20,19,19,19,19, 3, 5,26,17,17,17,17,17,17,17,26, 3, 5,14,14, 7,14,14,14,14,14,14, 8,17,17,17,17,17,17,17,17,17,
  /*24*/ 17,17,17,17,17,20,17,17,17,17,17,17,24,20,19,19,19,20, 3, 5,26,17,17,17,17,17,17,17,26, 3, 5,20,20,20,20,20,20,20,20,20,20,17,16,16,16,16,17,17,17,17,
  /*25*/ 17,17,17,17,17,20,17,17,17,17,17,17,24,20,19,15,18,20, 3, 5,26,17,17,17,17,17,17,17,26, 3, 5,20,17,17,17,17,20,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*26*/ 17,17,17,17,17,20,17,17,17,17,17,17,24,20,19,16,19,20, 3, 5,26,26,26,26,26,26,26,26,26, 3, 5,20,17,17,17,17,15,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*27*/ 17,17,17,17,17,15,20,20,20,13,20,20,20,20,19,19,19,20, 3, 5,15,18,15,18,15,18,15,18,15, 3, 5,20,17,17,17,17,16,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*28*/ 17,17,17,17,17,17,15,15,15, 6,14,14,14,14,14,14,14,14, 4, 5,16,19,16,19,16,19,16,19,16, 3, 5,20,17,17,17,17,20,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*29*/ 17,17,17,17,17,17,17,17,17,15,15,15,15,15,15,15,15,15, 3, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 5,20,20,20, 9,20,20,20,20, 9,20,16,20,20, 9,20,17,17,17,17,
  /*30*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 6, 7, 7, 7, 7, 4, 4, 4, 4, 7, 7, 7, 7,14,14,14, 7,14,14,14,14, 7,14,14,14,14, 8,15,17,17,17,17,
  /*31*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,15,19,15,19,15, 3, 4, 4, 5,20,20,20,20,20,15,20,20,20,20,20,20,20,20,19,20,18,20,17,17,17,17,17,
  /*32*/ 17,17,17,17,17,17,17,17,17,16,16,16,16,16,17,16,16,16,16,18,16,15,16, 3, 4, 4, 5,15,19,20,20,20,16,20,20,20,20,20,20,20,20,20,20,20,20,17,17,17,17,17,
  /*33*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,15,19,17,19, 3, 4, 4, 5,16,18,15,17,17,17,17,17,17,17,15,15,17,17,17,17,17,15,17,17,17,17,17,
  /*34*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,17,17,17,17,17,19,16,19, 3, 4, 4, 5,20,18,16,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*35*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,20,17,17,17,17,16,15,19,19, 3, 4, 4, 5,20,19,20,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*36*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,20,17,17,17,17,15,16,15,19, 3, 4, 4, 5,20,15,20,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*37*/ 17,17,17,17,17,17,17,16,16,17,17,17,17,17,20,17,17,17,17,16,19,16,19, 3, 4, 4, 5,20,16,20,17,17,17,17,17,17,17,16,16,16,17,17,17,17,17,17,17,17,17,17,
  /*38*/ 17,17,17,17,17,17,17,18,19,19, 9,20,20,20,20,20, 9,19,19,19,19,19,19, 3, 4, 4, 5,20,20,20,20,13,20,20,20,20,20,20,20,20,13,15,15,15,17,17,17,17,17,17,
  /*39*/ 17,17,17,17,17,17,17,15,18,19, 6,14,14,14,14,14, 7,14,14,14,14,14,14, 4, 4, 4, 4,14,14,14,14, 7,14,14,14,14,14,14,14,14, 8,17,17,17,17,17,17,17,17,17,
  /*40*/ 17,17,17,17,17,17,17,17,15,15,15,18,15,19,19,15,18,15,19,19,15,20,20, 3, 4, 4, 5,20,20,20,20,20,20,19,19,15,15,15,15,15,15,17,17,17,17,17,17,17,17,17,
  /*41*/ 17,17,17,17,17,17,17,17,17,17,17,15,17,18,18,17,15,17,19,19,17,15,20, 3, 4, 4, 5,20,15,20,15,20,20,15,15,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*42*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,15,15,17,17,17,15,15,16,16,15, 3, 4, 4, 5,15,17,15,17,15,15,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*43*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,15,17,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*44*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*45*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*46*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*47*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*48*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*49*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  /*50*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17};

  TileMap.setSize({ 800,800 });
  TileMap.setGridSize({ 50,50 });
  TileMap.setTexture(*Textures["ForestSpriteSheet"]);
  TileMap.setNumberOfTextureTilesPerRow(3);
  TileMap.setTextureTileSize({ 16,16 });
  TileMap.update(levelData,50);
  //for (auto& tile : levelData)
	//	  tile = rand() % 9;
  




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
  std::shared_ptr <Engine::LevelObject> WeaponShop = std::make_shared<Engine::LevelObject>();//WeaponShop Declaration
  std::shared_ptr <Engine::LevelObject> BrahmHouse = std::make_shared<Engine::LevelObject>();//BrahmHouse Declaration - looks like an inn for now
  std::shared_ptr <Engine::LevelObject> Inn = std::make_shared<Engine::LevelObject>();//Inn declaration
  std::shared_ptr <Engine::LevelObject> BigHouse1 = std::make_shared<Engine::LevelObject>(); //Main Characters house
  std::shared_ptr <Engine::LevelObject> BigHouse2 = std::make_shared<Engine::LevelObject>(); //Another big house
  std::shared_ptr <Engine::LevelObject> SmallHouse1 = std::make_shared<Engine::LevelObject>();//A small house
  std::shared_ptr <Engine::LevelObject> SmallHouse2 = std::make_shared<Engine::LevelObject>();//another small house
  std::shared_ptr <Engine::LevelObject> SmallHouse3 = std::make_shared<Engine::LevelObject>();//yet another small house

  //Declaration of The Trees-Texture Set of the Trees
  std::map<int, std::shared_ptr <Engine::LevelObject>> Trees;//Declares an array of trees -these will be the 5x5 tree blocks for filler
  std::shared_ptr <Engine::LevelObject> BigOakTreeTree = std::make_shared<Engine::LevelObject>(); //Declares The big tree in the middle of town
  /* //decided to do the trees a different way
  for (int i = 0; i <= 15; i++)//Declares/gives textures to all of the big tree blocks
  {
    Trees[i] = std::make_shared<Engine::LevelObject>();
    Trees[i]->SetTexture(Textures["TreeBlock"]);
  }*/
  BigOakTreeTree->SetTexture(Textures["Bigoaktree"]);//sets the texture for the big oak tree in the middle of town
  BigOakTreeTree->SetTextureRect({ 0,0,144,144 });

  //Position Set of the Trees
  /*
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
  Trees[15]->SetPosition({ 16 * 20,0 });*/
  BigOakTreeTree->SetPosition({ 20 * 16,19 * 16 });

  //Sets the Textures and the positions of the buildings
  Barracks->SetTexture(Textures["BigBuildings"]);
  Barracks->SetTextureRect({ 112,80,112,80 });
  Barracks->SetPosition({ 6 * 16,15 * 16 });

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

  WeaponShop->SetTexture(Textures["5by5Shops"]);
  WeaponShop->SetTextureRect({ 0,0,80,80 });
  WeaponShop->SetPosition({ 39 * 16,34 * 16 });

  BrahmHouse->SetTexture(Textures["BigBuildings"]);
  BrahmHouse->SetTextureRect({ 112,0,112,80 });
  BrahmHouse->SetPosition({ 35 * 16,6 * 16 });

  Inn->SetTexture(Textures["BigBuildings"]);
  Inn->SetTextureRect({ 0,0,112,80 });
  Inn->SetPosition({ 16 * 30,16 * 34 });

  BigHouse1->SetTexture(Textures["5House"]);
  BigHouse1->SetTextureRect({ 0,0,80,80 });
  BigHouse1->SetPosition({ 16 * 32,16 * 18 });

  BigHouse2->SetTexture(Textures["5House"]);
  BigHouse2->SetTextureRect({ 80,80,80,80 });
  BigHouse2->SetPosition({ 16 * 39,16 * 18 });

  SmallHouse1->SetTexture(Textures["4House"]);
  SmallHouse1->SetTextureRect({ 0,0,64,64 });
  SmallHouse1->SetPosition({ 32 * 16,26 * 16 });

  SmallHouse2->SetTexture(Textures["4House"]);
  SmallHouse2->SetTextureRect({ 0,64,64,64 });
  SmallHouse2->SetPosition({ 37 * 16,26 * 16 });

  SmallHouse3->SetTexture(Textures["4House"]);
  SmallHouse3->SetTextureRect({ 64,0,64,64 });
  SmallHouse3->SetPosition({ 42 * 16,26 * 16 });

  LevelObjects["BarracksObj"] = Barracks;
  LevelObjects["TownHallObj"] = TownHall;
  LevelObjects["ChurchObj"] = Church;
  LevelObjects["ItemShopObj"] = ItemShop;
  LevelObjects["ArmorShopObj"] = ArmorShop;
  LevelObjects["WeaponShopObj"] = WeaponShop;
  LevelObjects["BrahmsHouseObj"] = BrahmHouse;
  LevelObjects["InnObj"] = Inn;
  LevelObjects["BigHouse1Obj"] = BigHouse1;
  LevelObjects["BigHouse2Obj"] = BigHouse2;
  LevelObjects["SmallHouse1Obj"] = SmallHouse1;
  LevelObjects["SmallHouse2Obj"] = SmallHouse2;
  LevelObjects["SmallHouse3Obj"] = SmallHouse3;
  LevelObjects["BigOakTree"] = BigOakTreeTree;
  

  std::shared_ptr<RPGActor> myActor = std::make_shared<RPGActor>();
  
  myActor->SetTexture(Textures["ActorGuy"]);
  SpawnActor(myActor, { 24*16,33*16 });
  LevelObjects["MainGuy"] = myActor;
  MainCharacter = myActor;
  myActor->AddCollider(Engine::Collider2D::CreatePolygonMesh(4, 1, 0, { myActor->GetActorPosition().x, myActor->GetActorPosition().y }, { 0,0 }, 1, 1, sf::Color::White));

  for (auto & obj : LevelObjects)
  {
		  if (!(obj.first == "MainGuy"))
		  {
			  Segments.push_back(Engine::BuildSegmentMesh('b', obj.second->getTopLeft(), obj.second->getBottomRight()));
		}
  }


    
}

OakTreeLevel::OakTreeLevel(const sf::Vector2u & LevelSize, const sf::FloatRect & DefaultView, bool showlines, const sf::Vector2f & GridSpacing)
  : BasicLevel(LevelSize, DefaultView, showlines, GridSpacing)
{
		
}

void OakTreeLevel::TickUpdate(const double & delta)
{
	LevelObjects["MainGuy"]->TickUpdate(delta);
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



	Texture->draw(TileMap);
	
  for (auto & obj : LevelObjects)
    obj.second->Render(Texture);
	


  //If we are using the editor, draw the meshes too
  //Make this configurable later

 // Texture->setView(oldView);
}

void OakTreeLevel::HandleInputEvent(const Engine::UserEvent & evnt)
{
	MainCharacter->HandleInputEvent(evnt);
}
