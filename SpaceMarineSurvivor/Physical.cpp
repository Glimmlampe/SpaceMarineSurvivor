#include "Physical.h"

#include <sstream>

Physical::Physical(int toHitBonus) : DamageType(65 + toHitBonus, 2, 4)
{
}


Physical::~Physical()
{
}

std::string Physical::toString()
{
	std::stringstream ss;

	ss << "Physical:\n" << DamageType::toString();

	return ss.str();
}