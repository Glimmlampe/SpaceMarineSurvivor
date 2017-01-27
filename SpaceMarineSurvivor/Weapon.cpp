#include "Weapon.h"

#include <sstream>


Weapon::Weapon(int attachmentPoints, bool ranged, std::string name) : Gear(attachmentPoints, name)
{
	this->ranged = ranged;
	usedThisRound = false;
}


Weapon::~Weapon()
{
}

bool Weapon::isRanged()
{
	return ranged;
}

bool Weapon::isUsedThisRound()
{
	return usedThisRound;
}

void Weapon::useWeapon()
{
	usedThisRound = true;
}

void Weapon::resetRound()
{
	usedThisRound = false;
}

std::string Weapon::toString()
{
	std::stringstream ss;

	if (ranged)
		ss << "Ranged weapon, ";
	else
		ss << "Melee weapon, ";

	return ss.str();
}