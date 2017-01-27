#pragma once
#include "Weapon.h"
#include "Physical.h"

class ClawFang :
	public Weapon, public Physical
{
public:
	ClawFang();
	~ClawFang();

	int calcDamage();
	bool hasHit();

	std::string shootingSound();
	std::string hittingSound();
	std::string reloadingSound();

	std::string toString();
};

