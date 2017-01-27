#include "Protection.h"
#include <sstream>


Protection::Protection(int attachmentPoints, int bonusHP, std::string name) : Gear(attachmentPoints, name)
{
	this->bonusHP = bonusHP;
}


Protection::~Protection()
{
}


int Protection::getBonusHP()
{
	return bonusHP;
}

std::string Protection::toString()
{
	std::stringstream ss;

	ss << "Protective gear:\nBonus HP: " << bonusHP;

	return ss.str();
}