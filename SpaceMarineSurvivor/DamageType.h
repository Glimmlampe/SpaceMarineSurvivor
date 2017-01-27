#pragma once
#include <string>

class DamageType
{
private:
	int toHit;
	int damageDice;
	int damageBonus;

public:
	DamageType(int toHit, int damageDice, int damageBonus);
	~DamageType();

	int getToHit();
	int getDamageDice();
	int getDamageBonus();

	std::string toString();
};

