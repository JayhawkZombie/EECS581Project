#include "Skill.h"



Skill::Skill()
{
  m_name = "";
  m_filePath = "";
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
  return m_filePath;
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
void Skill::setFilePath(std::string filePath)
{
  m_filePath = filePath;
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

void Skill::makeMonsterSkills()
{
		MonsterType* current;
//		ListReader list;
		Skill currentSkill;


		auto animationFilePaths = Skill::AnimationFilePaths();
		MonsterType** myArray = MonsterType::readMonsters("Game/ContentFiles/MonsterTypes/MonsterTypes.txt");
//		MonsterType** myArray = list.readMonsters("Game/ContentFiles/MonsterTypes/MonsterTypes.txt");
		std::map<int, std::map<int, std::string>> subElements = SubElementNames2();
		std::map<int, std::map<int, std::map<int, std::map<int, int>>>> MBPType = MonsterType::getMBPType();
		std::ofstream myfile;
		myfile.open("Game/ContentFiles/Generic/GenericMonsterSkills.txt");

		if (myfile.is_open())
		{
				myfile << "319\n";
				for (int i = 0; i < 319; i++)
				{
//						current = new MonsterType();//just for compilaiton
						current = myArray[i];

						//The follow super block of code makes the generic monster skills


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
						currentSkill.m_filePath = animationFilePaths[current->getPrimary()][current->getSecondary()];

						//sets battle direction booleans to default
						currentSkill.m_castOnSelf = false;
						currentSkill.m_castOnSingle = (current->getEvolutionStage() < 3);
						currentSkill.m_castOnEnemy = true;

						//sets mp cost
						currentSkill.m_mpCost = current->getEvolutionStage() * 10;

						//sets description
						currentSkill.m_description = "Unfortunately, due to a lazy developer, this content is not yet added";

						//sets generic damage
						Damage myDamage;
						float total;
						if (current->getEvolutionStage() == 1)
						{
								total = 12*1.2;
						}
						else if (current->getEvolutionStage() == 2)
						{
								total = 40*1.2;
						}
						else if (current->getEvolutionStage() ==3)
						{
								total = 70*1.2;
						}
						else if (current->getEvolutionStage() ==4)
						{
								total = 130*1.2;
						}
						else
						{
								total = 0;
						}

						if (current->getPrimary() == current->getSecondary())//theres a ten percent bonus to elemental damage if it is 'pure'
						{
								if (MBPType[current->getPrimary()][current->getSecondary()][current->getEvolutionStage()][current->getEvolutionType()]==0)
								{
										myDamage.content[current->getPrimary()] = (int)ceil(total*.7);
										myDamage.content[6] = (int)ceil(total*.4);
								}
								else if (MBPType[current->getPrimary()][current->getSecondary()][current->getEvolutionStage()][current->getEvolutionType()] == 1)
								{
										myDamage.content[current->getPrimary()] = (int)ceil(total*.8);
										myDamage.content[6] = (int)ceil(total*.15);
										myDamage.content[7] = (int)ceil(total*.15);
								}
								else
								{
										myDamage.content[current->getPrimary()] = (int)ceil(total*.9);
										myDamage.content[7] = (int)ceil(total*.2);
								}
						}
						else
						{
								if (MBPType[current->getPrimary()][current->getSecondary()][current->getEvolutionStage()][current->getEvolutionType()] == 0)
								{
										myDamage.content[current->getPrimary()] = (int)ceil(total*.35);
										myDamage.content[current->getSecondary()] = (int)ceil(total*.25);
										myDamage.content[6] = (int)ceil(total*.4);
								}
								else if (MBPType[current->getPrimary()][current->getSecondary()][current->getEvolutionStage()][current->getEvolutionType()] == 1)
								{
										myDamage.content[current->getPrimary()] = (int)ceil(total*.4);
										myDamage.content[current->getSecondary()] = (int)ceil(total*.3);
										myDamage.content[6] = (int)ceil(total*.15);
										myDamage.content[7] = (int)ceil(total*.15);
								}
								else
								{
										myDamage.content[current->getPrimary()] = (int)ceil(total*.45);
										myDamage.content[current->getSecondary()] = (int)ceil(total*.35);
										myDamage.content[7] = (int)ceil(total*.2);
								}
						}
						
	//					myfile << subElements[current->getPrimary()][current->getSecondary()];
						/*
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
						}*/
						myfile << current->getEvolutionStage() << "\n";
						
						//						myfile << MBPType[current->getPrimary()][current->getSecondary()][current->getEvolutionStage()][current->getEvolutionType()];//check that it should be stage then type

						

						}
		}
}


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
return result;
}

std::map<int, std::map<int, std::string>> Skill::SubElementNames2()//coped from GameMain to please compiler
{
		std::map<int,
				std::map<int, std::string>> SubElementNames;
		SubElementNames[0][0] = "Pyro";
		SubElementNames[0][1] = "Lava";
		SubElementNames[0][2] = "Dinosaur";
		SubElementNames[0][3] = "Phoenix";
		SubElementNames[0][4] = "Justice";
		SubElementNames[0][5] = "Vengence";
		SubElementNames[1][0] = "Steam";
		SubElementNames[1][1] = "Aqua";
		SubElementNames[1][2] = "Amphibious";
		SubElementNames[1][3] = "Weather";
		SubElementNames[1][4] = "Ice";
		SubElementNames[1][5] = "Deep";
		SubElementNames[2][0] = "Fairy";
		SubElementNames[2][1] = "Swamp";
		SubElementNames[2][2] = "Tera";
		SubElementNames[2][3] = "Pegasus";
		SubElementNames[2][4] = "Compassion";
		SubElementNames[2][5] = "Rotten";
		SubElementNames[3][0] = "Sands";
		SubElementNames[3][1] = "SeaBreeze";
		SubElementNames[3][2] = "Birds";
		SubElementNames[3][3] = "Aero";
		SubElementNames[3][4] = "Cocka";
		SubElementNames[3][5] = "NightWing";
		SubElementNames[4][0] = "Solar";
		SubElementNames[4][1] = "Lunar";
		SubElementNames[4][2] = "Guardian";
		SubElementNames[4][3] = "Holy";
		SubElementNames[4][4] = "Light";
		SubElementNames[4][5] = "Redemption";
		SubElementNames[5][0] = "Demonic";
		SubElementNames[5][1] = "Poison";
		SubElementNames[5][2] = "Undead";
		SubElementNames[5][3] = "Storm";
		SubElementNames[5][4] = "Betrayer";
		SubElementNames[5][5] = "Umbral";
		return SubElementNames;
}

std::map<int, std::string> Skill::specificSkillNames()
{
		std::map<int, std::string> result;
		result[0] = "Flare";
		result[12] = "Lava spit";
		result[19] = "DinoBite";
		result[29] = "Thermal";
		result[36] = "FireBrace";
		result[43] = "Spite";
		result[50] = "Sauna";
		result[54] = "Bubble";
		result[66] = "Tapple TailSlap";
		result[76] = "Rain";
		result[86] = "SnowBall Throw";
		result[98] = "Bends";
		result[110] = "FeyDust";
		result[127] = "Babadger Slash";
		result[128] = "Leaf Slash";
		result[129] = "PhotoSynthesis";
		result[145] = "Minor Pegasus";
		result[152] = "Compassion 1";
		result[159] = "Poison Fang";
		result[163] = "Sand Fang";
		result[173] = "Ocean Spray";
		result[180] = "Colour";
		result[187] = "Feather Strike";
		result[199] = "Inspire";
		result[209] = "Evil Intention";
		result[219] = "SunShine";
		result[220] = "Solar Fang";
		result[229] = "(nonalcoholic) MoonShine";
		result[230] = "Lunar Fang";
		result[236] = "Guard 1";
		result[243] = "Bless";
		result[250] = "Shine";
		result[262] = "Regret";
		result[272] = "HellBurn";//this is probably too cool a name for a baby monster
		result[282] = "Stinger";
		result[292] = "Spook";
		result[299] = "Harsh Rain";
		result[303] = "Condemn";
		result[307] = "Shadow";

		return result;


}

std::map<int, std::string> Skill::skillDefinitions()
{
		std::map<int, std::string> result;
		return result;
}