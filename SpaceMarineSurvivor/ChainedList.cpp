#include "ChainedList.h"

#include <iostream>
#include <sstream>

ChainedList::ChainedList()
{
}


ChainedList::~ChainedList()
{
}

void ChainedList::attach(Gear &gear)
{
	element* tmp = new element;
	tmp->gear = &gear;
	tmp->next = list;
	list = tmp;
}

Gear* ChainedList::getElement(int n)
{
	element* tmp = list;
	if (tmp != NULL)
	{	
		for (int i = 0; tmp != NULL && i != n; i++)
			tmp = tmp->next;
		return tmp->gear;
	}
	return NULL;
}

Gear* ChainedList::removeLast()
{
	element* tmp = list;
	if (list != NULL)
	{
		list = list->next;
		return tmp->gear;
	}
	return NULL;
}

/*
* return: length of list, -1 if list = NULL
*/
int ChainedList::length()
{
	element* tmp = list;

	int count = 0;
	if (tmp == NULL)
	{
		count = -1;
	}
	else
	{
		while (tmp != NULL)
		{
			count++;
			tmp = tmp->next;
		}
	}

	return count;
}

std::string ChainedList::toString()
{
	element * hilfszeiger = list;
	std::stringstream ss;
	std::string returnString;
	while (hilfszeiger != NULL)
	{
		ss << hilfszeiger->gear->toString() << "/";
		hilfszeiger = hilfszeiger->next;
	}
	ss << std::endl;
	returnString = ss.str();

	return returnString;
}

