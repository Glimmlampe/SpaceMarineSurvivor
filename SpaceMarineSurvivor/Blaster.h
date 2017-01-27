#pragma once
#include "Weapon.h"
#include "Energy.h"

class Blaster :
	public Weapon, public Energy
{
public:
	Blaster();
	~Blaster();

	int calcDamage();
	bool hasHit();

	std::string shootingSound();
	std::string hittingSound();
	std::string reloadingSound();

	std::string toString();
};

