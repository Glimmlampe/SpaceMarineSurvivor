#include "Alien.h"

#include <sstream>

int Alien::count = 0;

Alien::Alien() : Critter("Hatchling", 5+count)
{
	count++;
	if (this->getHP() > 30)
		this->setName("Queen");
	else if (this->getHP() > 20)
		this->setName("Guard");
	else if (this->getHP() > 10)
		this->setName("Worker");
}

Alien::~Alien()
{
}

int Alien::getCount()
{
	return count;
}

Spit Alien::getSpit()
{
	return spit;
}

ClawFang Alien::getClawFang()
{
	return clawFang;
}

std::string  Alien::soundHit()
{
	return "CHHHHHHHH";
}

std::string  Alien::battleCry()
{
	return "Grrrrawwww!";
}

std::string Alien::toString()
{
	std::stringstream ss;

	ss << "Alien:\n" << Critter::toString() << std::endl;

	return ss.str();
}