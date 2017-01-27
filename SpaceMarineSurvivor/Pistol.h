#pragma once
#include "Weapon.h"
#include "Physical.h"

class Pistol :
	public Weapon, public Physical
{
public:
	Pistol();
	~Pistol();

	int calcDamage();
	bool hasHit();

	std::string shootingSound();
	std::string hittingSound();
	std::string reloadingSound();

	std::string toString();
};

