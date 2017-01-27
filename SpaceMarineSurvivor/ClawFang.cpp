#include "ClawFang.h"

#include <sstream>

#include "Tools.h"

ClawFang::ClawFang() : Weapon(1, false, "Claws and Fang"), Physical(20)
{
}


ClawFang::~ClawFang()
{
}

int ClawFang::calcDamage()
{
	return Physical::getDamageDice()*rollD12() + Physical::getDamageBonus();
}

bool ClawFang::hasHit()
{
	return (Physical::getToHit() >= rollD100());
}

std::string ClawFang::shootingSound()
{
	return "SNAP, SLASH, SLASH";
}

std::string ClawFang::hittingSound()
{
	return "...";
}

std::string ClawFang::reloadingSound()
{
	return "";
}

std::string ClawFang::toString()
{
	std::stringstream ss;

	ss << "Claws and fangs:\n" << Weapon::toString() << Physical::toString();

	return ss.str();
}