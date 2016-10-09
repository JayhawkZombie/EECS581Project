#include "RPGActor.h"


//Constructors/Destructors

RPGActor::RPGActor()
{
	m_name = "";
}


RPGActor::~RPGActor()
{
}

//Getters/Setters
std::string RPGActor::getName() const
{
	return m_name;
}

void RPGActor::setName(std::string name)
{
	m_name = name;
}