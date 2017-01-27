#include "Energy.h"

#include <sstream>

Energy::Energy(int toHitBonus) : DamageType(75 + toHitBonus, 1, 6)
{
}


Energy::~Energy()
{
}

std::string Energy::toString()
{
	std::stringstream ss;

	ss << "Energy:\n" << DamageType::toString();

	return ss.str();
}