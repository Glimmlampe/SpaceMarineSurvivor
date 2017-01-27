#pragma once
#include "DamageType.h"
class Energy :
	public DamageType
{
public:
	Energy(int toHitBonus);
	~Energy();
	
	std::string toString();
};

