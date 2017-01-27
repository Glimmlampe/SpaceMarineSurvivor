#pragma once
#include "Weapon.h"
#include "Energy.h"

class LaserRifle :
	public Weapon, public Energy
{
public:
	LaserRifle();
	~LaserRifle();

	int calcDamage();
	bool hasHit();

	std::string shootingSound();
	std::string hittingSound();
	std::string reloadingSound();

	std::string toString();
};

