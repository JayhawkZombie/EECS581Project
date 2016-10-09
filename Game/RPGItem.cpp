#include "RPGItem.h"


//constructors
RPGItem::RPGItem()
{
	m_name = "";
	m_description = "";
	m_value = 0;
	m_id = 0;
	num++;
}


RPGItem::~RPGItem()
{
}

//Getters- Setters
std::string RPGItem::getName() const
{
	return m_name;
}

std::string RPGItem::getDescription() const
{
	return m_description;
}

int RPGItem::getValue() const
{
	return m_value;
}

int RPGItem::getId() const
{
	return m_id;
}


void RPGItem::setName(std::string name)
{
	m_name = name;
}

void RPGItem::setDescription(std::string description)
{
	m_description = description;
}

void RPGItem::setValue(int value)
{
	m_value = value;
}

void RPGItem::setId(int id)
{
	m_id = id;
}

//Other functions

void RPGItem::InitializeRPGItem()
{
	num = 0;
}

int RPGItem::HowMany()
{
	return num;
}