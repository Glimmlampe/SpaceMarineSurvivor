#include "Blaster.h"

#include <sstream>

#include "Tools.h"


Blaster::Blaster() : Weapon(1, true, "Blaster"), Energy(0)
{
}


Blaster::~Blaster()
{
}

int Blaster::calcDamage()
{
	return Energy::getDamageDice()*rollD12() + Energy::getDamageBonus();
}

bool Blaster::hasHit()
{
	return Energy::getToHit() >= rollD100();
}

std::string Blaster::shootingSound()
{
	return "Tssskkk!";
}

std::string Blaster::hittingSound()
{
	return "...Pfft!";
}

std::string Blaster::reloadingSound()
{
	return "TwwwwwrrrriiiIIIIIII...";
}

std::string Blaster::toString()
{
	std::stringstream ss;

	ss << "Blaster:\n" << Weapon::toString() << Energy::toString();

	return ss.str();
}