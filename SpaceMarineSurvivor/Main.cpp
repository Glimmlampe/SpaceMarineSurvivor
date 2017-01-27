#include <iostream>
#include <sstream>
#include <Windows.h>
#include <time.h>

#include "Missions.h"

#include "Critter.h"
#include "Alien.h"
#include "SpaceMarine.h"
#include "TrainingTarget.h"

#include "GUI.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void main()
{
	GUI* gui = GUI::instance();
	std::stringstream ss;

	TrainingTarget* a = new TrainingTarget();
	SpaceMarine* sm = new SpaceMarine("");

	gui->setLocation("Intro");
	gui->setSpaceMarine(sm);
	gui->setCritter(a);

	gui->paint();

	gui->printToConsole("Welcome to Space Marine Survivor\n", gui->darkYellow, true);
	gui->printToConsole("Whats your name Soldier?\n", gui->darkYellow, false);

	string name;
	name = gui->input();
	sm = new SpaceMarine(name.erase(name.size()-1));

	gui->setSpaceMarine(sm);
	gui->paint();

	int choice = 0;
	bool run = true;
	
	while (run)
	{
		gui->printToConsole("Do you want to go to:\n1 - Training\n2 - Mission\n3 - Story mode\n0 - End Game\n", gui->darkYellow, true);
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
			run = false;
			break;
		case 1:
			shootingRange(sm);			
			break;
		case 2:
			lastStand(sm);
			break;
		case 3:
			storyMode(sm);
			break;
		default:
			;
		}
		gui->setLocation("Intro");
		sm->revive();
		gui->paint();
	}
}