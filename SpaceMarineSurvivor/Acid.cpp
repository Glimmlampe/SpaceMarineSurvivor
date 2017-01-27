#include "Acid.h"

#include <sstream>

Acid::Acid() : DamageType(50, 1, 1)
{
}


Acid::~Acid()
{
}

std::string Acid::toString()
{
	std::stringstream ss;

	ss << "Acid:\n" << DamageType::toString();
	
	return ss.str();
}