#include "TrainingTarget.h"

#include <sstream>

int TrainingTarget::count = 0;

TrainingTarget::TrainingTarget() : Critter("TrainingTarget", 1)
{
	count++;
}

TrainingTarget::~TrainingTarget()
{
}

int TrainingTarget::getCount()
{
	return count;
}

std::string  TrainingTarget::soundHit()
{
	std::stringstream ss;

	ss << "Target " << count << " destroyed!";

	return ss.str();
}

std::string  TrainingTarget::battleCry()
{
	return "";
}

std::string TrainingTarget::toString()
{
	std::stringstream ss;

	ss << "Alien:\n" << Critter::toString() << std::endl;

	return ss.str();
}