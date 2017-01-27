#include "Tools.h"
#include <Windows.h>
#include <time.h>

int rollD100()
{
	Sleep(100);
	srand(time(NULL));
	return rand()%100+1;
}

int rollD12()
{
	Sleep(100);
	srand(time(NULL));
	return rand() % 12 + 1;
}