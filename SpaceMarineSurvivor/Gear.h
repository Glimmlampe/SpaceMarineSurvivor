#pragma once

#include <string>

class Gear
{
private:
	int attachmentPoints;
	std::string name;

public:
	Gear(int attachmentPoints, std::string name);
	virtual ~Gear(){};

	int getAttachmentPoints();
	std::string getName();

	std::string toString();
};

