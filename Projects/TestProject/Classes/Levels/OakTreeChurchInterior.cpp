#include "OakTreeChurchInterior.h"
#include "../../../../SFEngine/Source/Headers/Level/LevelObject.h"
#include "../../../../Game/RPGActor.h"
#include <map>
#include <cmath>


OakTreeChurchInterior::OakTreeChurchInterior(): BasicLevel({352,208},{0,0,352,208})
{
	LoadFromFile("./Projects/TestProject/testproject.json");
	std::vector<unsigned char> levelData(100000);
	levelData = {
		// row 0  1  2  3  4  5  6  7  8  9 10 11 12
		/*0*/ 43,42,42,41,41,40,40,40,41,41,42,42,43,
		/*1*/ 42,42,41,41,40, 1, 2, 3,40,41,41,42,42,
		/*2*/ 42,20,21,41,40, 5, 6, 7,40,41,22,23,42,
		/*3*/ 42,24,25,41,40, 9,10,11,40,41,26,27,42,
		/*4*/ 43,42,42,41,41,40,40,40,41,41,42,42,43,
		/*5*/ 52,57,57,57,57,57,57,57,57,57,57,57,55,
		/*6*/ 54,59,44,44,44,13,14,15,44,44,44,59,57,
		/*7*/  4, 8,56,44,44,17,18,19,44,44,58, 4, 8,
		/*8*/ 12,16,54,59,59,59,59,59,59,59,55,12,16,
		/*9*/ 44,44,49,50,50,50,50,50,50,50,51,44,44,
		/*10*/44,44,44,44,44,44,44,44,44,44,44,44,44,
		/*11*/44,45,46,46,46,47,44,45,46,46,46,47,44,
		/*12*/44,44,44,44,44,44,44,44,44,44,44,44,44,
		/*13*/44,45,46,46,46,47,44,45,46,46,46,47,44,
		/*14*/44,44,44,44,44,44,44,44,44,44,44,44,44,
		/*15*/44,45,46,46,46,47,44,45,46,46,46,47,44,
		/*16*/44,44,44,44,44,44,44,44,44,44,44,44,44,
		/*17*/28,29,44,45,46,47,44,45,46,47,44,30,31,
		/*18*/32,33,44,44,44,44,44,44,44,44,44,34,35,
		/*19*/36,37,44,45,46,47,44,45,46,47,44,38,39,
		/*20*/44,44,44,44,44,44,44,44,44,44,44,44,44,
		/*21*/44,44,44,44,44,44,44,44,44,44,44,44,44
	};
	TileMap->setSize({ 208,352 });
	TileMap->setGridSize({ 13,22 });
	TileMap->setTexture(*Textures["ChurchInterior"]);
	TileMap->setNumberOfTextureTilesPerRow(4);
	TileMap->setTextureTileSize({ 16,16 });
	TileMap->update(levelData, 13);

	std::shared_ptr<RPGActor> myActor = std::make_shared<RPGActor>();
	myActor->SetTexture(Textures["MyActor_sheet"]);
	SpawnActor(myActor,{ 6 * 16,22 * 16 });
	myActor->SetPosition({ 6 * 16,21 * 16 });
	myActor->SetActorSize({ 15,15 });//could be 16 but collisiions
	MainCharacter = myActor;

	sf::FloatRect myActor_spawnLocation(72.f, 72.f, 16.f, 16.f);
	sf::FloatRect full_map_view(0.f, 0.f, 208.f, 352.f);

	myActor_camera.AttachToActor(myActor);
//	myActor_camera.SetView(myActor_spawnLocation);
	myActor_camera.SetView({ 325.f,176.f,325.f,176.f });
	Gravity->x = 0;
	Gravity->y = 0;
	Engine::SetGravity(Gravity);
}


OakTreeChurchInterior::~OakTreeChurchInterior()
{
}

void OakTreeChurchInterior::TickUpdate(const double & delta)
{
	BasicLevel::TickUpdate(delta);
	//LevelObjects["MainGuy"]->TickUpdate(delta);
	myActor_camera.Update();
}

void OakTreeChurchInterior::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
	Texture->draw(*TileMap);
	BasicLevel::RenderOnTexture(Texture);
}

void OakTreeChurchInterior::HandleInputEvent(const Engine::UserEvent & evnt)
{
	MainCharacter->HandleInputEvent(evnt);
}

void OakTreeChurchInterior::OnBegin()
{
	Engine::SetGravity(Gravity);
}

void OakTreeChurchInterior::OnEnd()
{
}

std::string OakTreeChurchInterior::GetClass() const
{
	return std::string("OakTreeChurchInterior");
}
