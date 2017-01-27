#include "Shield.h"

#include <sstream>

Shield::Shield() : Protection(1, 15, "Shield")
{
	
}


Shield::~Shield()
{
}

std::string Shield::toString()
{
	std::stringstream ss;

	ss << "Shield:\n" << Protection::toString();

	return ss.str();
}