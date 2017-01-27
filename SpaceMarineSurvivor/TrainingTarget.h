#pragma once
#include "Critter.h"
class TrainingTarget :
	public Critter
{
private:
	static int count;

public:
	TrainingTarget();
	~TrainingTarget();

	int getCount();

	std::string soundHit();
	std::string battleCry();

	std::string toString();
};

