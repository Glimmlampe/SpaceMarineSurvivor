#pragma once
#include <string>

class Critter
{
private:
	int hp;
	std::string name;
protected:
	void setHP(int hp);
	void setName(std::string name);
public:
	const int MAX_HP;

	Critter(std::string name, int hp);
	~Critter();

	std::string getName();
	int getHP();

	virtual std::string soundHit() = 0;
	virtual std::string battleCry() = 0;

	void applyDamage(int hp);

	std::string toString();
};

