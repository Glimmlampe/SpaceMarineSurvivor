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

void shootingRange(SpaceMarine* sm)
{
	GUI* gui = GUI::instance();
	TrainingTarget* a = new TrainingTarget();
	std::stringstream ss;

	gui->round = 0;

	gui->setLocation("Shooting range");
	gui->paint();

	ss << "Welcome to the training grounds " << sm->getName() << endl;

	gui->printToConsole(ss.str(), gui->darkYellow, true);

	
	
	int choice = 0;
	bool run = true;
	ss.str("");
	ss << "Choose your weapons:\n0 - Remove last weapon\n1 - Sword\n2 - Shield\n3 - Pistol\n4 - Blaster\n5 - Shotgun\n6 - LaserRifle\nAny other key - finished\n";
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
	gui->printToConsole("Good choice... Now get ready for basic weapon training!\n", gui->darkYellow, false);
	Sleep(500);
		
	int result = 9999;
	gui->clearTextArea();
	while (sm->getHP() > 0 && result != 2)
	{		
		result = sm->fight(*gui->getCritter());
		if (result == 1)
		{
			gui->setCritter(new TrainingTarget());
		}	

		gui->printToConsole(sm->getRoundText(), gui->lightTurquoise, false);
		Sleep(500);
		gui->round++;
		gui->paint();

		if (gui->round > 15)
			result = 2;
	}

	ss << "You finished training. In " << gui->round << " rounds, you hit " << a->getCount() << " training targets!" << endl << "Drop your weapons!" << endl << "Press any key to continue..." << endl;
	gui->printToConsole(ss.str(), gui->darkYellow, true);
	ss.str("");

	sm->removeWeapon();
	sm->removeWeapon();
	sm->removeWeapon();
	gui->paintStatusBar();

	gui->waitForKey();
}