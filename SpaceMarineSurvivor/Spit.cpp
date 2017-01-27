#include "Spit.h"

#include <sstream>

#include "Tools.h"

Spit::Spit() : Weapon(1, true, "Spit"), Acid()
{
}


Spit::~Spit()
{
}

int Spit::calcDamage()
{
	return Acid::getDamageDice()*rollD12() + Acid::getDamageBonus();
}

bool Spit::hasHit()
{
	return (Acid::getToHit() >= rollD100());
}

std::string Spit::shootingSound()
{
	return "Pfffft!";
}

std::string Spit::hittingSound()
{
	return "...tzzzzzz!";
}

std::string Spit::reloadingSound()
{
	return "";
}

std::string Spit::toString()
{
	std::stringstream ss;

	ss << "Spit:\n" << Weapon::toString() << Acid::toString();

	return ss.str();
}