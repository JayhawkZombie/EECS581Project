#include "BattleActor.h"



BattleActor::BattleActor()
{
}


BattleActor::~BattleActor()
{
}

bool BattleActor::isAlive()const
{
  return m_hpCur > 0;
}

Element BattleActor::getPrimary()const
{
  return m_primary;
}

Damage BattleActor::getThorns()const
{
  return m_thorns;
}

int BattleActor::getHpCur()const
{
  return m_hpCur;
}

int BattleActor::getHpMax()const
{
  return m_hpMax;
}

int BattleActor::getMpCur()const
{
  return m_mpCur;
}

int BattleActor::getMpMax()const
{
  return m_mpMax;
}

int BattleActor::getMpRegen()const
{
  return m_mpRegen;
}

SkillSet BattleActor::getSkillSet()const
{
  return m_skillSet;
}

int BattleActor::getLevel()const
{
  return m_level;
}

int BattleActor::getExp()const
{
  return m_exp;
}

//setters
void BattleActor::setPrimary(Element primary)
{
  m_primary = primary;
}

void BattleActor::setThorns(Damage thorns)
{
  m_thorns = thorns;
}

void BattleActor::setHpCur(int hpCur)
{
  m_hpCur = hpCur;
}

void BattleActor::setHpMax(int hpMax)
{
  m_hpMax = hpMax;
}

void BattleActor::setMpCur(int mpCur)
{
  m_mpCur = mpCur;
}

void BattleActor::setMpMax(int mpMax)
{
  m_mpMax = mpMax;
}

void BattleActor::setMpRegen(int mpRegen)
{
  m_mpRegen = mpRegen;
}

void BattleActor::setLevel(int level)
{
  m_level = level;
}

void BattleActor::setExp(int exp)
{
  m_exp = exp;
}