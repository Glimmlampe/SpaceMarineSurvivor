#include "SpaceMarine.h"

#include <iostream>
#include <sstream>
#include <time.h>

#include "Alien.h"
#include "TrainingTarget.h"
#include "Shield.h"

using std::cout;
using std::endl;

SpaceMarine::SpaceMarine(std::string name) : Critter(name, 100)
{
}

SpaceMarine::~SpaceMarine()
{
}

bool SpaceMarine::checkGear()
{
	int count = 0;
	for (int i = 0; i < wornGear.length(); i++)
	{
		Gear* g = wornGear.getElement(i);
		count += g->getAttachmentPoints();
	}

	if (count <= 2)
		return true;
	else
	{
		//std::cout << "Too heavy!" << std::endl;
		return false;
	}
}

void SpaceMarine::pickupGear(Gear* gear)
{
	wornGear.attach(*gear);
	if (gear->getName() == "Shield")
	{
		Gear* g = wornGear.getElement(0);
		Protection* p = static_cast<Protection*>(g);
		applyDamage(-1 * p->getBonusHP());
	}
	while (!checkGear())
	{
		//std::cout << "Dropping gear!" << std::endl;
		if (wornGear.getElement(0)->getName() == "Shield")
		{
			Gear* g = wornGear.getElement(0);
			Protection* p = static_cast<Protection*>(g);
			applyDamage(p->getBonusHP());
		}
		wornGear.removeLast();
	}
}

void SpaceMarine::removeWeapon()
{
	wornGear.removeLast();
}

void SpaceMarine::addLine(std::string line)
{
	std::stringstream ss;

	ss << roundText << line;
	roundText = ss.str();
}

void SpaceMarine::addLineN(std::string line)
{
	std::stringstream ss;

	ss << roundText << line << endl;
	roundText = ss.str();
}

void SpaceMarine::revive()
{
	setHP(MAX_HP);
}

int SpaceMarine::fight(Critter &foe)
{
	Alien* a = dynamic_cast<Alien*>(&foe);

	roundText = "";
	// fire space marine ranged weapons, if any
	for (int i = 0; i < wornGear.length() && foe.getHP() > 0; i++)
	{
		Gear* g = wornGear.getElement(i);
		Weapon* w = dynamic_cast<Weapon*>(g);

		if (w != NULL)
		{
			if (w->isRanged() && !w->isUsedThisRound())
			{
				addLine(w->shootingSound());
				addLine(w->hittingSound());
				if (w->hasHit())
				{
					int dmg = w->calcDamage();
					foe.applyDamage(dmg);
					std::stringstream ss;
					ss << endl << foe.getName() << ": " << foe.soundHit() << " (Hit for: " << dmg << " HP)";
					addLineN(ss.str());
				}
				else
					addLineN(" Missed!");
				w->useWeapon();
			}
		}
	}
	// alien spits
	if (foe.getHP() > 0 && a != NULL)
	{
		addLine(a->getSpit().shootingSound());
		addLine(a->getSpit().hittingSound());
		if (a->getSpit().hasHit())
		{
			int dmg = a->getSpit().calcDamage();
			this->applyDamage(dmg);
			std::stringstream ss;
			ss << endl << this->getName() << ": " << this->soundHit() << "(Hit for: " << dmg << " HP)" << endl;
			addLine(ss.str());
		}
		else
			addLineN(" Missed!");
	}
	if (foe.getHP() > 0 && this->getHP() > 0)
	{
		// attack space marine melee weapons, if any
		for (int i = 0; i < wornGear.length() && foe.getHP() > 0; i++)
		{
			Gear* g = wornGear.getElement(i);
			Weapon* w = dynamic_cast<Weapon*>(g);

			if (w != NULL)
			{
				if (!w->isRanged() && !w->isUsedThisRound())
				{
					addLine(w->shootingSound());
					if (w->hasHit())
					{
						addLine(w->hittingSound());
						int dmg = w->calcDamage();
						foe.applyDamage(dmg);
						std::stringstream ss;
						ss << endl << foe.getName() << ": " << foe.soundHit() << " (Hit for: " << dmg << " HP)" << endl;
						addLineN(ss.str());
					}
					else
						addLineN(" Missed!");
					w->useWeapon();
				}
			}
		}
	}
	if (foe.getHP() > 0 && this->getHP() > 0 && a != NULL)
	{
		// attack alien claws
		addLine(a->getClawFang().shootingSound());
		if (a->getClawFang().hasHit())
		{
			addLine(a->getClawFang().hittingSound());
			int dmg = a->getClawFang().calcDamage();
			this->applyDamage(dmg);
			std::stringstream ss;
			ss << endl << this->getName() << ": " << this->soundHit() << "(Hit for: " << dmg << " HP)" << endl;
			addLine(ss.str());
		}
		else
			addLineN(" Missed!");
	}

	// reset all weapons
	for (int i = 0; i < wornGear.length(); i++)
	{
		Gear* g = wornGear.getElement(i);
		Weapon* w = dynamic_cast<Weapon*>(g);

		if (w != NULL)
		{
			w->resetRound();
		}
	}

	if (this->getHP() <= 0)
		return 2;			
	else if (foe.getHP() <= 0)
		return 1;
	else
		return 0;
}

std::string  SpaceMarine::soundHit()
{
	std::string cry;
	srand(time(NULL));
	switch (rand() % 3)
	{
	case 0:
		cry = "DIE ALIEN SCUMM!";
		break;
	case 1:
		cry = "AAAARGGGH!";
		break;
	case 2:
		cry = "I don't have time to bleed!";
		break;
	}
	return cry;
}

std::string  SpaceMarine::battleCry()
{
	std::string call;
	srand(time(NULL));
	switch (rand() % 3)
	{
	case 0:
		call = "DIE ALIEN SCUMM!";
		break;
	case 1:
		call = "WAAAAAAAHHHH!";
		break;
	case 2:
		call = "DIE DIE DIE";
		break;
	}
	return call;
}

std::string SpaceMarine::getRoundText()
{
	return roundText;
}

std::string SpaceMarine::printGear()
{
	std::string rt = wornGear.toString();
	if (rt == "\n")
		return "Unarmed";
	else
		return  rt;
}

std::string SpaceMarine::toString()
{
	std::stringstream ss;
	std::string returnString;

	ss << "Space Marine:\n" << Critter::toString() << "\nWorn gear: " << wornGear.toString();

	returnString = ss.str();
	return returnString;
}