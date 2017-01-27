#include "DamageType.h"

#include <sstream>

DamageType::DamageType(int toHit, int damageDice, int damageBonus)
{
	this->toHit = toHit;
	this->damageDice = damageDice;
	this->damageBonus = damageBonus;
}


DamageType::~DamageType()
{
}

int DamageType::getToHit()
{
	return toHit;
}

int DamageType::getDamageDice()
{
	return damageDice;
}

int DamageType::getDamageBonus()
{
	return damageBonus;
}

std::string DamageType::toString()
{
	std::stringstream ss;

	ss << "Chance to hit: " << toHit;
	ss << "\nDamage: " << damageDice << "d12+" << damageBonus << "\n";

	return ss.str();
}