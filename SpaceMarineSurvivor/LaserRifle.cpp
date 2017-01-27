#include "LaserRifle.h"

#include <sstream>
#include <math.h>

#include "Tools.h"

LaserRifle::LaserRifle() : Weapon(2, true, "LaserRifle"), Energy(0)
{
}


LaserRifle::~LaserRifle()
{
}

int LaserRifle::calcDamage()
{
	return round(2.5 * Energy::getDamageDice()*rollD12() + Energy::getDamageBonus());
}

bool LaserRifle::hasHit()
{
	return (Energy::getToHit() >= rollD100());
}

std::string LaserRifle::shootingSound()
{
	return "Tssskkk!";
}

std::string LaserRifle::hittingSound()
{
	return "...Pfft!";
}

std::string LaserRifle::reloadingSound()
{
	return "TwwwwwrrrriiiIIIIIII...";
}

std::string LaserRifle::toString()
{
	std::stringstream ss;

	ss << "LaserRifle:\n" << Weapon::toString() << Energy::toString();

	return ss.str();
}