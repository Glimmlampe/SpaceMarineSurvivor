#include "Missions.h"

#include <iostream>
#include <sstream>
#include <Windows.h>
#include <time.h>

#include "Sword.h"
#include "Pistol.h"
#include "Shotgun.h"
#include "Blaster.h"
#include "LaserRifle.h"
#include "Shield.h"

#include "Spit.h"
#include "ClawFang.h"

#include "Critter.h"
#include "Alien.h"
#include "SpaceMarine.h"
#include "TrainingTarget.h"
#include "Room.h"


#include "GUI.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void storyMode(SpaceMarine* sm)
{
	GUI* gui = GUI::instance();
	Room* actRoom = createLevel();
	Room startRoom = *actRoom;
	std::stringstream ss;
	bool end = false;
	int choice;
	

	gui->round = 0;
	
	//TODO Weapon pickup
	sm->pickupGear(new Shotgun());

	while (!end && sm->getHP() > 0)
	{
		actRoom->setActPos(true);
		actRoom->visit();
		gui->setLocation(actRoom->getName());
		gui->paint();

		gui->clearViewer();
		gui->paintMap(&startRoom, 0, 0);
		gui->resetMap(&startRoom);

		// if theres a monster in the room -> fight!
		if (actRoom->getGuard() != NULL)
		{
			gui->printToConsole("A fierce alien leaps at you... RAISE YOUR WEAPONS!\n", gui->darkYellow, true);
			Sleep(250);
			int result = 0;
			while (sm->getHP() > 0 && result == 0)
			{
				result = sm->fight(*actRoom->getGuard());

				gui->printToConsole(sm->getRoundText(), gui->lightTurquoise, false);
				Sleep(500);
				gui->round++;
				gui->paint();

				if (result == 2)
					end = true;
				if (result == 1)
				{
					actRoom->getGuard()->~Critter();
					actRoom->setGuard(NULL);
				}
			}
		}

		// if there is a weapon lying around, ask if to pick up
		if (actRoom->lootToString().length() > 1)
		{
			ss << "There are weapons lieing around... do you want to pickup one?\n" << actRoom->lootToString();
			gui->printToConsole(ss.str(), gui->darkYellow, true);
			Sleep(250);
		}

		ss << actRoom->getDescription() << endl;

		if (actRoom->isExit())
		{
			end = true;
			gui->printToConsole(ss.str(), gui->darkYellow, true);
		}
		else
		{
			if (actRoom->getNorth() != NULL)
				ss << "1 - Take the door to the north!" << endl;
			if (actRoom->getEast() != NULL)
				ss << "2 - Take the door to the east!" << endl;
			if (actRoom->getSouth() != NULL)
				ss << "3 - Take the door to the south!" << endl;
			if (actRoom->getWest() != NULL)
				ss << "4 - Take the door to the west!" << endl;

			gui->printToConsole(ss.str(), gui->darkYellow, true);
			ss.str("");

			choice = std::stoi(gui->input());

			switch (choice)
			{
			case 1:
				if (actRoom->getNorth() != NULL)
					actRoom = actRoom->getNorth();
				break;
			case 2:
				if (actRoom->getEast() != NULL)
					actRoom = actRoom->getEast();
				break;
			case 3:
				if (actRoom->getSouth() != NULL)
					actRoom = actRoom->getSouth();
				break;
			case 4:
				if (actRoom->getWest() != NULL)
					actRoom = actRoom->getWest();
				break;
			default:
				break;
			}
		}
	}

	if (sm->getHP()<0)
		gui->printToConsole("You died horribly... The END!\n", gui->darkRed, true);
	else
		gui->printToConsole("You managed to escape...barely! The END!\n", gui->darkGreen, true);

	gui->waitForKey();





/*	gui->clearViewer();
	gui->paintMap(start, 0, 0);
	gui->resetMap(start);
		gui->waitForKey();


	gui->clearViewer();
	gui->paintMap(start, 0, 0);
	gui->resetMap(start);
		gui->waitForKey();*/
}
