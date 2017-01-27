#pragma once
#include "DamageType.h"

class Acid :
	public DamageType
{
public:
	Acid();
	~Acid();
	
	std::string toString();
};

