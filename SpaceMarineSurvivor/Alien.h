#pragma once
#include "Critter.h"
#include "Spit.h"
#include "ClawFang.h"

#include <string>

//TODO AlienTypes als Enum
class Alien :
	public Critter
{
private:
	static int count;
	Spit spit;
	ClawFang clawFang;

public:
	Alien();
	~Alien();

	int getCount();

	Spit getSpit();
	ClawFang getClawFang();

	std::string soundHit();
	std::string battleCry();

	std::string toString();
};

