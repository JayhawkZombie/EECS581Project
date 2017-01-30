#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include "../SFEngine/Source/Headers/BasicIncludes.h"
#include "../SFEngine/Source/Headers/Level/Level.h"
#include <vector>
#include <map>
#include "MonsterType.h"

enum class Type : std::uint32_t
{
	Fire = 0,
	Water = 1,
	Earth = 2,
	Air   = 3,
	Light = 4,
	Dark  = 5,
	Count
};

struct MonsterTree
{
	int TreeType;
	std::vector<MonsterType> myvec;
	MonsterTree() = default;
	MonsterTree(const MonsterTree &copy) : myvec(copy.myvec), TreeType(copy.TreeType) {};
};




class GameMain
{
public:
	GameMain();
	~GameMain();
	static int run();
	static std::map<int, std::map<int, std::string>> SubElementNames();
    void TickUpdate(const double &Delta);
    void Render(std::shared_ptr<sf::RenderTexture> Target);
	static std::map<int, std::map<int, std::string>> Symbols();
	MonsterType*** returnTree(int primary, int secondary);
    std::map<Type, std::map<Type, MonsterTree>> m_MonsterMap;
	MonsterType***** MonsterArray;

private:
//  std::shared_ptr<Engine::Level> Level;
  

//	void printAssetStatus();

};

#endif
