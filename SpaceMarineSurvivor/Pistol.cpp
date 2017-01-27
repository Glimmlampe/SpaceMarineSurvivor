#include "Pistol.h"

#include <sstream>

#include "Tools.h"

Pistol::Pistol() : Weapon(1, true, "Pistol"), Physical(0)
{
}


Pistol::~Pistol()
{
}

int Pistol::calcDamage()
{
	return Physical::getDamageDice()*rollD12() + Physical::getDamageBonus();
}

bool Pistol::hasHit()
{
	return (Physical::getToHit() >= rollD100());
}

std::string Pistol::shootingSound()
{
	return "BANG!";
}

std::string Pistol::hittingSound()
{
	return "...TACK!";
}

std::string Pistol::reloadingSound()
{
	return "Click...Clack";
}

std::string Pistol::toString()
{
	std::stringstream ss;

	ss << "Pistol:\n" << Weapon::toString() << Physical::toString();

	return ss.str();
}