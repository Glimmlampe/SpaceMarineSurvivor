#pragma once
#include "Gear.h"
#include <string>

class Weapon :
	public Gear
{
private:
	bool ranged;
	bool usedThisRound;

public:
	Weapon(int attachmentPoints, bool ranged, std::string name);
	~Weapon();

	bool isRanged();
	bool isUsedThisRound();
	void useWeapon();
	void resetRound();

	virtual int calcDamage() = 0;
	virtual bool hasHit() = 0;

	virtual std::string shootingSound() = 0;
	virtual std::string hittingSound() = 0;
	virtual std::string reloadingSound() = 0;

	std::string toString();
};

