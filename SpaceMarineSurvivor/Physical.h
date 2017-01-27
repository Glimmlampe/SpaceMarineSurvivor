#pragma once
#include "DamageType.h"
class Physical :
	public DamageType
{
public:
	Physical(int toHitBonus);
	~Physical();
	
	std::string toString();
};

