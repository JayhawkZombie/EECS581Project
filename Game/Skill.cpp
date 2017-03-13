#include "Skill.h"



Skill::Skill()
{
  m_name = "";
  m_animationFilePath = "";
  m_description = "";
  m_isPhysical = false;
  m_isMagical = false;
  m_castOnSelf = false;
  m_castOnSingle = false;
  m_castOnEnemy = false;
  m_mpCost = 0;
  m_effect = Damage();
}


Skill::~Skill()
{
}

std::string Skill::getName()
{
  return m_name;
}
std::string Skill::getFilePath()
{
  return m_animationFilePath;
}
std::string Skill::getDescription()
{
  return m_description;
}

bool Skill::getIsPhysical()
{
  return m_isPhysical;
}
bool Skill::getIsMagical()
{
  return m_isMagical;
}
bool Skill::getCastOnSelf()
{
  return m_castOnSelf;
}
bool Skill::getCastOnSingle()
{
  return m_castOnSingle;
}
bool Skill::getCastOnEnemy()
{
  return m_castOnEnemy;
}
int Skill::getMpCost()
{
  return m_mpCost;
}
Damage Skill::getDamage()
{
  return m_effect;
}
//int Skill::getSize()//returns how many skills there are for use as the parameter of SkillSet(s)
//{
 // return m_size;
//}


//setters
void Skill::setName(std::string name)
{
  m_name = name;
}
void Skill::setAnimationFilePath(std::string filePath)
{
	m_animationFilePath = filePath;
}
void Skill::setDescription(std::string description)
{
  m_description = description;
}
void Skill::setIsPhysical(bool isPhysical)
{
  m_isPhysical = isPhysical;
}
void Skill::setIsMagical(bool isMagical)
{
  m_isMagical = isMagical;
}
void Skill::setCastOnSelf(bool castOnSelf)
{
  m_castOnSelf = castOnSelf;
}
void Skill::setCastOnSingle(bool castOnSingle)
{
  m_castOnSingle = castOnSingle;
}
void Skill::setCastOnEnemy(bool castOnEnemy)
{
  m_castOnEnemy = castOnEnemy;
}
void Skill::setMpCost(int mpCost)
{
  m_mpCost = mpCost;
}
void Skill::setDamage(Damage newDamage)
{
  m_effect =  newDamage;
}

Skill** Skill::readSkills(std::string filePath)
{

}

void Skill::makeMonsterSkills()
{
		MonsterType* current;
		ListReader list;
		Skill currentSkill;


		auto animationFilePaths = Skill::AnimationFilePaths();
		MonsterType** myArray = list.readMonsters("Game/ContentFiles/MonsterTypes/MonsterTypes.txt");
		std::map<int, std::map<int, std::string>> subElements = GameMain::SubElementNames();
		std::map<int, std::map<int, std::map<int, std::map<int,int>>>> MBPType = MonsterType::getMBPType();
		std::ofstream myfile;
		myfile.open("Game/ContentFiles/Generic/GenericMonsterSkills.txt");

		if (myfile.is_open())
		{
				myfile << "319\n";
				for (int i = 0; i < 319; i++)
				{
						current = myArray[i];


						//this block writes the generic name to the skill
						currentSkill.m_name = subElements[current->getPrimary()][current->getSecondary()];
						if (MBPType[current->getPrimary()][current->getSecondary()][current->getEvolutionStage()][current->getEvolutionType()] == 0)
						{
								currentSkill.m_name.append(" Physical");
								currentSkill.m_isPhysical = true;
								currentSkill.m_isMagical = false;
						}
						else if (MBPType[current->getPrimary()][current->getSecondary()][current->getEvolutionStage()][current->getEvolutionType()] == 1)
						{
								currentSkill.m_name.append(" Balanced");
								currentSkill.m_isPhysical = true;
								currentSkill.m_isMagical = false;
						}
						else
						{
								currentSkill.m_name.append(" Magical");
								currentSkill.m_isPhysical = false;
								currentSkill.m_isMagical = true;
						}
						currentSkill.m_name.append(std::to_string(current->getEvolutionStage()));
						//currentSkill.m_name.append("\n");//may need this later depending

						//sets file path
						currentSkill.m_animationFilePath = animationFilePaths[current->getPrimary()][current->getSecondary()];
						
						//sets battle direction booleans to default
						currentSkill.m_castOnSelf = false;
						currentSkill.m_castOnSingle = (current->getEvolutionStage() < 3);
						currentSkill.m_castOnEnemy = true;

						//sets mp cost
						currentSkill.m_mpCost = current->getEvolutionStage() * 10;

						//sets description
						currentSkill.m_description = "Unfortunately, due to a lazy developer, this content is not yet added";

						//sets generic 
						
						/*
						myfile << subElements[current->getPrimary()][current->getSecondary()];
						
						if (MBPType[current->getPrimary()][current->getSecondary()][current->getEvolutionStage()][current->getEvolutionType()] == 0)
						{
								myfile << " Physical";
						}
						else if (MBPType[current->getPrimary()][current->getSecondary()][current->getEvolutionStage()][current->getEvolutionType()]==1)
						{
								myfile << " Balanced";
						}
						else
						{
								myfile << " Magical";
						}
						myfile << current->getEvolutionStage() << "\n";
						*/
//						myfile << MBPType[current->getPrimary()][current->getSecondary()][current->getEvolutionStage()][current->getEvolutionType()];//check that it should be stage then type



				}
		}
}


/* //decided just to use GameMain.cpp's SubElementNames
std::map<int, std::map<int, std::string>> Skill::skillPrefixes()
{
		std::map<int, std::map<int, std::string>> prefixes;
		prefixes[0][0] = "Pyro";
		prefixes[0][1] = "Lava";
		prefixes[0][2] = "Dino";

}
*/

std::map<int, std::map<int, std::string>> Skill::AnimationFilePaths()
{
		std::map<int, std::map<int, std::string>> result;
		result[0][0] = "SFEngine/Samples/Animations/SkillAnimations/FlareAnimation.png";
		result[0][1] = "SFEngine/Samples/Animations/SkillAnimations/LavaSpitAnimation.png";
		result[0][2] = "SFEngine/Samples/Animations/SkillAnimations/DinoBiteAnimation.png";
		result[0][3] = "SFEngine/Samples/Animations/SkillAnimations/ThermalAnimation.png";
		result[0][4] = "SFEngine/Samples/Animations/SkillAnimations/FireBraceAnimation.png";
		result[0][5] = "SFEngine/Samples/Animations/SkillAnimations/SpiteAnimation.png";
		result[1][0] = "SFEngine/Samples/Animations/SkillAnimations/SaunaAnimation.png";
		result[1][1] = "SFEngine/Samples/Animations/SkillAnimations/BubbleAnimation.png";
		result[1][2] = "SFEngine/Samples/Animations/SkillAnimations/TappleTailSlapAnimation.png";
		result[1][3] = "SFEngine/Samples/Animations/SkillAnimations/RainAnimation.png";
		result[1][4] = "SFEngine/Samples/Animations/SkillAnimations/SnowBallThrowAnimation.png";
		result[1][5] = "SFEngine/Samples/Animations/SkillAnimations/TheBendsAnimation.png";
		result[2][0] = "SFEngine/Samples/Animations/SkillAnimations/FeyDustAnimation.png";
		result[2][1] = "SFEngine/Samples/Animations/SkillAnimations/MudSlapAnimation.png";
		result[2][2] = "SFEngine/Samples/Animations/SkillAnimations/LeafSlashAnimation.png";
		result[2][3] = "SFEngine/Samples/Animations/SkillAnimations/DustAnimation.png";
		result[2][4] = "SFEngine/Samples/Animations/SkillAnimations/Compassion1Animation.png";
		result[2][5] = "SFEngine/Samples/Animations/SkillAnimations/PoisonFangAnimation.png";
		result[3][0] = "SFEngine/Samples/Animations/SkillAnimations/SandFang.png";
		result[3][1] = "SFEngine/Samples/Animations/SkillAnimations/OceanSpray.png";
		result[3][2] = "SFEngine/Samples/Animations/SkillAnimations/Dazzle.png";
		result[3][3] = "SFEngine/Samples/Animations/SkillAnimations/FeatherStrike.png";
		result[3][4] = "SFEngine/Samples/Animations/SkillAnimations/Inspire.png";
		result[3][5] = "SFEngine/Samples/Animations/SkillAnimations/EvilIntention.png";
		result[4][0] = "SFEngine/Samples/Animations/SkillAnimations/Sunshine.png";
		result[4][1] = "SFEngine/Samples/Animations/SkillAnimations/MoonShine.png";
		result[4][2] = "SFEngine/Samples/Animations/SkillAnimations/Guard.png";
		result[4][3] = "SFEngine/Samples/Animations/SkillAnimations/Bless.png";
		result[4][4] = "SFEngine/Samples/Animations/SkillAnimations/Shine.png";
		result[4][5] = "SFEngine/Samples/Animations/SkillAnimations/Regret.png";
		result[5][0] = "SFEngine/Samples/Animations/SkillAnimations/HellBurn.png";
		result[5][1] = "SFEngine/Samples/Animations/SkillAnimations/PoisonSting.png";
		result[5][2] = "SFEngine/Samples/Animations/SkillAnimations/Spook.png";
		result[5][3] = "SFEngine/Samples/Animations/SkillAnimations/HarshRain.png";
		result[5][4] = "SFEngine/Samples/Animations/SkillAnimations/Condemn.png";
		result[5][5] = "SFEngine/Samples/Animations/SkillAnimations/Shadow.png";
		return result;
}

std::map<int, std::string> skillDefinitions()
{
		std::map<int, std::string> result;
		result[0] = "The Flarial's skill is usually used in the wild to signal its parents that its in trouble, however it can still burn if it his an enemy.";
//		result[1] = "When a Philammon feels threatened it spits lava from its guts to warn off attackers";
//		result[2] = ""
}