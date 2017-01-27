#include "Room.h"


Room::Room(std::string name, std::string description) : north(NULL), east(NULL), south(NULL), west(NULL)
{
	this->exit = false;
	this->printed = false;
	this->visited = false;
	this->actualPosition = false;

	this->name = name;
	this->description = description;

	distNorth = 0;
	distEast = 0;
	distSouth = 0;
	distWest = 0;
}


Room::~Room()
{
}

std::string Room::getName()
{
	return name;
}
std::string Room::getDescription()
{
	return description;
}

void Room::setGuard(Critter* c)
{
	guard = c;
}
Critter* Room::getGuard()
{
	return guard;
}

Gear* Room::pickupWeapon(int id)
{
	return loot.getElement(id);
}
void Room::dropWeapon(Gear* w)
{
	loot.attach(*w);
}
std::string Room::lootToString()
{
	return loot.toString();
}

void Room::setPrinted()
{
	printed = true;
}

void Room::resetPrinted()
{
	printed = false;
}
bool Room::isPrinted()
{
	return printed;
}

bool Room::isVisited()
{
	return visited;
}
void Room::visit()
{
	visited = true;
}

void Room::setExit()
{
	exit = true;
}

bool Room::isExit()
{
	return exit;
}

bool Room::isActPos()
{
	return actualPosition;
}
void Room::setActPos(bool x)
{
	actualPosition = x;
}

void Room::setNorth(Room* r, int d)
{
	north = r;
	distNorth = d;
	if (r->getSouth()==NULL)
		r->setSouth(this, d);
}
Room* Room::getNorth()
{
	return north;
}
int Room::getDistNorth()
{
	return distNorth;
}
void Room::setEast(Room* r, int d)
{
	east = r;
	distEast = d;
	if (r->getWest() == NULL)
		r->setWest(this, d);
}
Room* Room::getEast()
{
	return east;
}
int Room::getDistEast()
{
	return distEast;
}
void Room::setSouth(Room* r, int d)
{
	south = r;
	distSouth = d;
	if (r->getNorth() == NULL)
		r->setNorth(this, d);
}
Room* Room::getSouth()
{
	return south;
}
int Room::getDistSouth()
{
	return distSouth;
}
void Room::setWest(Room* r, int d)
{
	west = r;
	distWest = d;
	if (r->getEast() == NULL)
		r->setEast(this, d);
}
Room* Room::getWest()
{
	return west;
}
int Room::getDistWest()
{
	return distWest;
}

