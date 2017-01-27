#pragma once
#include "Protection.h"
class Shield :
	public Protection
{
public:
	Shield();
	~Shield();

	std::string toString();
};

