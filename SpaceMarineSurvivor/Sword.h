#pragma once
#include "Weapon.h"
#include "Physical.h"

class Sword :
	public Weapon, public Physical
{
public:
	Sword();
	~Sword();

	int calcDamage();
	bool hasHit();

	std::string shootingSound();
	std::string hittingSound();
	std::string reloadingSound();

	std::string toString();
};

