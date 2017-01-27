#pragma once

#include "Gear.h"
#include <string>


class ChainedList
{
private:
	/*
	*	Datenstruktur fuer die verkettete Liste.
	*/
	struct element {
		Gear *gear;
		element * next;
	};

	element* list;


public:
	ChainedList();
	~ChainedList();
	
	/*
	*	Haengt ein Element am Anfang der Liste an.
	*/
	void attach(Gear &zahl);

	Gear* getElement(int n);

	Gear* removeLast();

	int length();
	std::string toString();
};

