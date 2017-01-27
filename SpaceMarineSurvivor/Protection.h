#pragma once
#include "Gear.h"

class Protection :
	public Gear
{
private:
	int bonusHP;

public:
	Protection(int attachmentPoints, int bonusHP, std::string name);
	~Protection();

	int getBonusHP();

	std::string toString();
};

