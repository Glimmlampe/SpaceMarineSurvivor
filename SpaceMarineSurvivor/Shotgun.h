#pragma once
#include "Weapon.h"
#include "Physical.h"


//TODO 2.5 x dmg!
class Shotgun :
	public Weapon, public Physical
{
public:
	Shotgun();
	~Shotgun();

	int calcDamage();
	bool hasHit();

	std::string shootingSound();
	std::string hittingSound();
	std::string reloadingSound();

	std::string toString();
};

