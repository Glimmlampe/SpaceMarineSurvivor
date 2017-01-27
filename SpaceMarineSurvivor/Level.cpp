#include "Room.h"

#include "Alien.h"
#include "Weapon.h"

#include "Shotgun.h"

Room* createLevel()
{
	Room* start;

	start = new Room("A", "Room A");

	Room* b = new Room("B", "Room B");
	b->setGuard(new Alien());
	b->dropWeapon(new Shotgun());
	start->setSouth(b, 1);
		
	Room* c = new Room("C", "Room C");
	start->setWest(c, 1);

	Room* d = new Room("D", "Room D");
	start->setEast(d, 2);

	Room* e = new Room("E", "Room E");
	start->setNorth(e, 1);

	Room* f = new Room("F", "Room F");
	f->setGuard(new Alien());
	f->setExit();
	e->setWest(f, 2);

	Room* g = new Room("G", "Room G");
	e->setNorth(g, 1);

	return start;
}