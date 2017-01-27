#include "Critter.h"

#include "GUI.h"

#include <sstream>

Critter::Critter(std::string name, int hp) : MAX_HP(hp)
{
	this->name = name;
	this->hp = hp;
}


Critter::~Critter()
{
}

std::string Critter::getName()
{
	return name;
}

void Critter::setHP(int hp)
{
	this->hp = hp;
}

void Critter::setName(std::string name)
{
	this->name = name;
}

int Critter::getHP()
{
	return hp;
}

void Critter::applyDamage(int hp)
{
	this->hp -= hp;
	GUI::instance()->paintStatusBar();
}

std::string Critter::toString()
{
	std::stringstream ss;

	ss << name << "\t" << hp << "/" << MAX_HP;

	return ss.str();
}