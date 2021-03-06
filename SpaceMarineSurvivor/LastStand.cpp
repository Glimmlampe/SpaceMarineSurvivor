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

#include "GUI.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void lastStand(SpaceMarine* sm)
{
	GUI* gui = GUI::instance();

	Alien* a = new Alien();
	std::stringstream ss;

	gui->round = 0;

	gui->setLocation("Barricaded Room");
	gui->setCritter(a);
	gui->paint();

	ss << "The aliens swarm the base. You barricaded the Room and get ready to make your last stand." << endl;

	gui->printToConsole(ss.str(), gui->darkYellow, true);

	int choice = 0;
	bool run = true;
	ss.str("");
	ss << "Pick up your weapons:\n0 - Remove last weapon\n1 - Sword\n2 - Shield\n3 - Pistol\n4 - Blaster\n5 - Shotgun\n6 - LaserRifle\nAny other key - finished\n";
	gui->printToConsole(ss.str(), gui->darkYellow, false);

	while (run)
	{
		try
		{
			choice = std::stoi(gui->input());
		}
		catch (std::invalid_argument&) //or catch(...) to catch all exceptions
		{
			choice = 99;
		}

		switch (choice)
		{
		case 0:
			gui->printToConsole("Dropping gun!\n", gui->darkYellow, true);
			gui->printToConsole(ss.str(), gui->darkYellow, false);
			Sleep(250);
			sm->removeWeapon();
			break;
		case 1:
			sm->pickupGear(new Sword());
			gui->printToConsole(ss.str(), gui->darkYellow, true);
			break;
		case 2:
			sm->pickupGear(new Shield());
			gui->printToConsole(ss.str(), gui->darkYellow, true);
			break;
		case 3:
			sm->pickupGear(new Pistol());
			gui->printToConsole(ss.str(), gui->darkYellow, true);
			break;
		case 4:
			sm->pickupGear(new Blaster());
			gui->printToConsole(ss.str(), gui->darkYellow, true);
			break;
		case 5:
			sm->pickupGear(new Shotgun());
			gui->printToConsole(ss.str(), gui->darkYellow, true);
			break;
		case 6:
			sm->pickupGear(new LaserRifle());
			gui->printToConsole(ss.str(), gui->darkYellow, true);
			break;
		default:
			gui->printToConsole("Done!\n", gui->darkYellow, true);
			Sleep(250);
			run = false;
			break;
		}
		gui->paint();
	}
	ss.str("");
	gui->printToConsole("Good choice... Now get ready... they are coming!\n", gui->darkYellow, false);
	Sleep(1000);

	int result = 9999;
	gui->clearTextArea();
	while (sm->getHP() > 0 && result != 2)
	{
		result = sm->fight(*gui->getCritter());
		if (result == 1)
		{
			gui->setCritter(new Alien());
		}

		gui->printToConsole(sm->getRoundText(), gui->lightTurquoise, false);
		Sleep(500);
		gui->round++;
		gui->paint();
	}

	ss << "You died!\nYou survived " << gui->round << " rounds and you took " << a->getCount() << " aliens with you!" << endl << "Press any key to continue..." << endl;
	gui->printToConsole(ss.str(), gui->darkYellow, true);
	ss.str("");

	sm->removeWeapon();
	sm->removeWeapon();
	sm->removeWeapon();
	gui->paintStatusBar();

	gui->waitForKey();
}