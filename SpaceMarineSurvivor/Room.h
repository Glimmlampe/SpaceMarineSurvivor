#pragma once

#include <string>

#include "ChainedList.h"

#include "Weapon.h"
#include "Critter.h"

class Room
{
private:
	Room* north;
	int distNorth;
	Room* east;
	int distEast;
	Room* south;
	int distSouth;
	Room* west;
	int distWest;

	Critter* guard;
	ChainedList loot;

	std::string name;
	std::string description;

	bool printed;
	bool visited;
	bool actualPosition;
	bool exit;

public:
	Room(std::string name, std::string description);
	~Room();

	std::string getName();
	std::string getDescription();

	void setGuard(Critter* c);
	Critter* getGuard();
	
	Gear* pickupWeapon(int id);
	void dropWeapon(Gear* g);
	std::string lootToString();


	void setPrinted();
	void resetPrinted();
	bool isPrinted();
	bool isVisited();
	void visit();

	void setExit();
	bool isExit();

	bool isActPos();
	void setActPos(bool x);	

	void setNorth(Room* r, int d);
	Room* getNorth();
	int getDistNorth();
	void setEast(Room* r, int d);
	Room* getEast();
	int getDistEast();
	void setSouth(Room* r, int d);
	Room* getSouth();
	int getDistSouth();
	void setWest(Room* r, int d);
	Room* getWest();
	int getDistWest();
};

