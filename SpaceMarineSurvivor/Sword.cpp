#include "Sword.h"

#include <sstream>

#include "Tools.h"

Sword::Sword() : Weapon(1, false, "Sword"), Physical(20)
{

}

Sword::~Sword()
{
}

int Sword::calcDamage()
{
	return Physical::getDamageDice()*rollD12() + Physical::getDamageBonus();
}

bool Sword::hasHit()
{
	return (Physical::getToHit() >= rollD100());
}

std::string Sword::shootingSound()
{
	return "SSSSSSSSST";
}

std::string Sword::hittingSound()
{
	return "...THUD!";
}

std::string Sword::reloadingSound()
{
	return "";
}

std::string Sword::toString()
{
	std::stringstream ss;

	ss << "Sword:\n" << Weapon::toString() << Physical::toString();

	return ss.str();
}