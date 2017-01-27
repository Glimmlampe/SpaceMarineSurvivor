#pragma once
#include "Weapon.h"
#include "Acid.h"

class Spit :
	public Weapon, public Acid
{
public:
	Spit();
	~Spit();

	int calcDamage();
	bool hasHit();

	std::string shootingSound();
	std::string hittingSound();
	std::string reloadingSound();

	std::string toString();
};

