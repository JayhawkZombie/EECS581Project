#include "RPGActor.h"


//Constructors/Destructors

RPGActor::RPGActor()
{
	m_name = "";
  m_filePath = "";
}


RPGActor::~RPGActor()
{
}

//Getters/Setters
std::string RPGActor::getName() const
{
	return m_name;
}

std::string RPGActor::getFilePath() const
{
  return m_filePath;
}

void RPGActor::setName(std::string name)
{
	m_name = name;
}

void RPGActor::setFilePath(std::string filePath)
{
  m_filePath = filePath;
}