#include "Shotgun.h"

#include <sstream>
#include <math.h>

#include "Tools.h"

Shotgun::Shotgun() : Weapon(2, true, "Shotgun"), Physical(0)
{
}


Shotgun::~Shotgun()
{
}

int Shotgun::calcDamage()
{
	return round(2.5 * Physical::getDamageDice()*rollD12() + Physical::getDamageBonus());
}

bool Shotgun::hasHit()
{
	return (Physical::getToHit() >= rollD100());
}

std::string Shotgun::shootingSound()
{
	return "BANG!";
}

std::string Shotgun::hittingSound()
{
	return "...THUD!";
}

std::string Shotgun::reloadingSound()
{
	return "Click..Click..Click..Click..Click..Click..Click..";
}

std::string Shotgun::toString()
{
	std::stringstream ss;

	ss << "Shotgun:\n" << Weapon::toString() << Physical::toString();

	return ss.str();
}