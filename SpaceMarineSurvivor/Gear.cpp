#include "Gear.h"
#include <sstream>

Gear::Gear(int attachmentPoints, std::string name)
{
	this->attachmentPoints = attachmentPoints;
	this->name = name;
}

int Gear::getAttachmentPoints()
{
	return attachmentPoints;
}

std::string Gear::getName()
{
	return name;
}

std::string Gear::toString()
{
	std::stringstream ss;

	ss << name;

	return ss.str();
}