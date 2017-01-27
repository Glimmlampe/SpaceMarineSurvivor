#pragma once
#include "Critter.h"
#include "ChainedList.h"

class SpaceMarine :
	public Critter
{
private: 
	ChainedList wornGear;
	std::string roundText;

public:
	SpaceMarine(std::string name);
	~SpaceMarine();

	bool checkGear();
	void pickupGear(Gear* gear);
	void removeWeapon();
	std::string printGear();

	void addLine(std::string line);
	void addLineN(std::string line);

	void revive();

	/* Returns:
	*	0 - still fighting
	*	1 - alien died
	*	2 - Space marine died
	*/
	int fight(Critter &foe);

	std::string soundHit();
	std::string battleCry();

	std::string getRoundText();

	std::string toString();
};

