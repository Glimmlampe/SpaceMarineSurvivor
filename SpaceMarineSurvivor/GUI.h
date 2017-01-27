#pragma once
#include <string>
#include <Windows.h>

#include "Critter.h"
#include "SpaceMarine.h"
#include "Alien.h"
#include "TrainingTarget.h"
#include "Room.h"

#include "Point.h"

class GUI
{
private:
	GUI();
	GUI(const GUI&);
	static GUI* _instance;

	const int BREITE = 150;
	const int HOEHE = 50;

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	Point* outerBorderA;
	Point* outerBorderB;

	Point* smallHeadA;
	Point* smallHeadB;
	Point* bigHeadA;
	Point* bigHeadB;

	Point* textAreaA;
	Point* textAreaB;
	Point* viewerA;
	Point* viewerB;
	Point* inputA;
	Point* inputB;

	Point* statusFirstA;
	Point* statusFirstB;
	Point* statusSecondA;
	Point* statusSecondB;

	int consoleLineMarker;

	std::string location;

	SpaceMarine* spacemarine;
	Critter* critter;

	/*
	*	Springt an die durch die Parameter definierte Position in der Windows Konsole
	*
	*	Param1:	X-Position
	*	Param2:	Y-Position
	*/
	void gotoXY(short x, short y);
		
	// Forms
	/*	Point a - upper left 
	*	Point b - lower right
	*	char ascii - symbol for the frame
	*	int color - color of the frame, see enum Color
	*/
	void paintRectangle(Point a, Point b, char ascii, int color);
	void paintDoubleLineRectangle(Point a, Point b, int color);
	void paintFilledCircle(Point p, int r, char ascii, int color);

	void paintOuterFrame();
	void paintHeadLine();
	void paintMainFrame();
	void paintInputFrame();

	void clearArea(Point a, Point b);

	void paintToView(int x, int y, char ascii, int color);

	void paintTargetPicture();
	void paintAlien();

	class CGuard
	{
	public:
		~CGuard()
		{
			if (NULL != GUI::_instance)
			{
				delete GUI::_instance;
				GUI::_instance = NULL;
			}
		}
	};

public:
	static GUI* instance()
	{
		static CGuard g;   // Speicherbereinigung
		if (!_instance)
			_instance = new GUI();
		return _instance;
	}

	/*
	bit 0 - foreground blue
	bit 1 - foreground green
	bit 2 - foreground red
	bit 3 - foreground intensity

	bit 4 - background blue
	bit 5 - background green
	bit 6 - background red
	bit 7 - background intensity */
	enum Color
	{
		black=0x00, darkBlue = 0x01, darkGreen = 0x02, darkTurquoise = 0x03,
		darkRed = 0x04, darkPink=0x05, darkYellow=0x06, grey=0x07, darkGrey=0x08,
		lightBlue = 0x09, lightGreen = 0x0A, lightTurquoise = 0x0B, lightRed = 0x0C,
		lightPink=0x0D,	lightYellow=0x0E, white=0x0F
	};

	long round;

	~GUI();
	
	void clearViewer();
	void clearTextArea();
	void printToConsole(std::string text, int color, bool clear);

	std::string input();
	void waitForKey();

	void setSpaceMarine(SpaceMarine* sm);
	Critter* getCritter();
	void setCritter(Critter* c);
	void setLocation(std::string location);

	void writeToViewer(char ascii, int x, int y);

	Room* resetMap(Room* r);
	Room* paintMap(Room* r, int x, int y);

	void paintStatusBar();
	void paint();
};

