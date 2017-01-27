#include "GUI.h"

#include <iostream>
#include <sstream>
#include <math.h>
#include <conio.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

GUI* GUI::_instance = 0;

GUI::GUI()
{
	consoleLineMarker = 0;
	round = 0;

	int ganzVorne = 2;
	int ganzHinten = BREITE - 3;

	outerBorderA = new Point(0, 0);
	outerBorderB = new Point(BREITE - 1, HOEHE - 1);

	smallHeadA = new Point(ganzVorne, 2);
	smallHeadB = new Point(10, 8);
	bigHeadA = new Point(smallHeadB->getX() + 2, smallHeadA->getY());
	bigHeadB = new Point(ganzHinten, smallHeadB->getY());

	textAreaA = new Point(ganzVorne, 10);
	textAreaB = new Point(BREITE / 2 - 2, HOEHE - 17);
	viewerA = new Point(textAreaB->getX(), textAreaA->getY());
	viewerB = new Point(ganzHinten, textAreaB->getY());
	inputA = new Point(textAreaA->getX(), textAreaB->getY());
	inputB = new Point(viewerB->getX(), HOEHE - 13);

	statusFirstA = new Point(ganzVorne, HOEHE - 11);
	statusFirstB = new Point(ganzHinten / 2, HOEHE - 3);
	statusSecondA = new Point(statusFirstB->getX(), statusFirstA->getY());
	statusSecondB = new Point(ganzHinten, statusFirstB->getY());
}


GUI::~GUI()
{
}

void GUI::gotoXY(short x, short y)
{
	COORD position = { x, y };

	SetConsoleCursorPosition(hStdout, position);
}

void GUI::paintDoubleLineRectangle(Point a, Point b, int color)
{
	SetConsoleTextAttribute(hStdout, color);

	// first line
	gotoXY(a.getX(), a.getY());
	cout << char(201);
	for (int i = a.getX() + 1; i <= b.getX() - 1; i++)
	{
		gotoXY(i, a.getY());
		cout << char(205);
	}
	gotoXY(b.getX(), a.getY());
	cout << char(187);

	// sides
	for (int i = a.getY() + 1; i < b.getY(); i++)
	{
		gotoXY(a.getX(), i);
		cout << char(186);
		gotoXY(b.getX(), i);
		cout << char(186);
	}

	// lower line
	gotoXY(a.getX(), b.getY());
	cout << char(200);
	for (int i = a.getX() + 1; i <= b.getX() - 1; i++)
	{
		gotoXY(i, b.getY());
		cout << char(205);
	}
	gotoXY(b.getX(), b.getY());
	cout << char(188);
}

void GUI::paintRectangle(Point a, Point b, char ascii, int color)
{
	SetConsoleTextAttribute(hStdout, color);

	for (int i = a.getX(); i <= b.getX(); i++)
	{
		gotoXY(i, a.getY());
		cout << char(ascii);
	}

	for (int i = a.getY() + 1; i < b.getY(); i++)
	{
		gotoXY(a.getX(), i);
		cout << char(ascii);
		gotoXY(b.getX(), i);
		cout << char(ascii);
	}

	for (int i = a.getX(); i <= b.getX(); i++)
	{
		gotoXY(i, b.getY());
		cout << char(ascii);
	}
}

void GUI::paintFilledCircle(Point p, int r, char ascii, int color)
{
	SetConsoleTextAttribute(hStdout, color);

	for (int y = -r; y < r + 1; y++)
	{
		int half_row_width = sqrt(r*r - y*y);
		for (int x = -half_row_width - 1; x < half_row_width; x++)
		{
			gotoXY(p.getX() + x, p.getY() + y);
			cout << char(ascii);
		}
	}
}

void GUI::setSpaceMarine(SpaceMarine* sm)
{
	this->spacemarine = sm;
}

Critter* GUI::getCritter()
{
	return critter;
}

void GUI::setCritter(Critter* c)
{
	this->critter = c;
}

void GUI::setLocation(std::string location)
{
	this->location = location;
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

void GUI::paintOuterFrame()
{
	paintDoubleLineRectangle(*outerBorderA, *outerBorderB, lightBlue);
	gotoXY(outerBorderA->getX() + 3, outerBorderA->getY());
	cout << " Space Marine Survival ";
}

void GUI::paintHeadLine()
{
	paintRectangle(*smallHeadA, *smallHeadB, 219, darkBlue);
	if (round % 2)
		SetConsoleTextAttribute(hStdout, lightRed);
	else
		SetConsoleTextAttribute(hStdout, lightYellow);
	gotoXY(smallHeadA->getX() + 1, smallHeadA->getY() + 3);
	cout << "!Alert!";

	clearArea(*bigHeadA, *bigHeadB);

	paintRectangle(*bigHeadA, *bigHeadB, 219, darkBlue);
	SetConsoleTextAttribute(hStdout, darkTurquoise);
	gotoXY(bigHeadA->getX() + 2, bigHeadA->getY() + 2);
	cout << "Round:\t\t" << round;
	gotoXY(bigHeadA->getX() + 2, bigHeadA->getY() + 4);
	cout << "Location:\t" << location;
}

void GUI::paintMainFrame()
{
	paintRectangle(*textAreaA, *textAreaB, 219, darkBlue);
	SetConsoleTextAttribute(hStdout, darkBlue);
	gotoXY(textAreaA->getX() + 3, textAreaA->getY());
	cout << " Text Area ";

	paintRectangle(*viewerA, *viewerB, 219, darkBlue);
	SetConsoleTextAttribute(hStdout, darkBlue);
	gotoXY(viewerA->getX() + 3, viewerA->getY());
	cout << " View ";

	Alien* a = dynamic_cast<Alien*>(critter);
	if (a != NULL)
		paintAlien();

	TrainingTarget* t = dynamic_cast<TrainingTarget*>(critter);
	if (t != NULL)
		paintTargetPicture();
}

void GUI::paintInputFrame()
{
	paintRectangle(*inputA, *inputB, 219, darkBlue);
	SetConsoleTextAttribute(hStdout, darkBlue);
	gotoXY(inputA->getX() + 3, inputA->getY());
	cout << " Input ";
}

void GUI::paintStatusBar()
{
	paintRectangle(*statusFirstA, *statusFirstB, 219, darkBlue);
	SetConsoleTextAttribute(hStdout, darkBlue);
	if (spacemarine->getHP() < spacemarine->MAX_HP / 3)
		SetConsoleTextAttribute(hStdout, lightRed);
	else if (spacemarine->getHP() < spacemarine->MAX_HP / 2)
		SetConsoleTextAttribute(hStdout, darkYellow);
	gotoXY(statusFirstA->getX() + 3, statusFirstA->getY());
	cout << " Status ";

	clearArea(*statusFirstA, *statusFirstB);

	paintRectangle(*statusSecondA, *statusSecondB, 219, darkBlue);
	SetConsoleTextAttribute(hStdout, darkBlue);
	if (critter->getHP() < critter->MAX_HP / 3)
		SetConsoleTextAttribute(hStdout, lightRed);
	else if (critter->getHP() < critter->MAX_HP / 2)
		SetConsoleTextAttribute(hStdout, darkYellow);
	gotoXY(statusSecondA->getX() + 3, statusSecondA->getY());
	cout << " Status ";

	clearArea(*statusSecondA, *statusSecondB);

	SetConsoleTextAttribute(hStdout, darkTurquoise);
	gotoXY(statusFirstA->getX() + 2, statusFirstA->getY() + 2);
	cout << "Name: ";
	gotoXY(statusFirstA->getX() + 14, statusFirstA->getY() + 2);
	cout << spacemarine->getName();
	if (spacemarine->getHP() < spacemarine->MAX_HP / 3)
		SetConsoleTextAttribute(hStdout, lightRed);
	else if (spacemarine->getHP() < spacemarine->MAX_HP / 2)
		SetConsoleTextAttribute(hStdout, darkYellow);
	gotoXY(statusFirstA->getX() + 2, statusFirstA->getY() + 4);
	cout << "HP: ";
	gotoXY(statusFirstA->getX() + 14, statusFirstA->getY() + 4);
	cout << spacemarine->getHP() << "/" << spacemarine->MAX_HP;
	SetConsoleTextAttribute(hStdout, darkTurquoise);
	gotoXY(statusFirstA->getX() + 2, statusFirstA->getY() + 6);
	cout << "Weapons: ";
	gotoXY(statusFirstA->getX() + 14, statusFirstA->getY() + 6);
	cout << spacemarine->printGear();

	SetConsoleTextAttribute(hStdout, darkTurquoise);
	gotoXY(statusSecondA->getX() + 2, statusSecondA->getY() + 2);
	cout << "Enemy: ";
	gotoXY(statusSecondA->getX() + 14, statusSecondA->getY() + 2);
	cout << critter->getName();
	if (critter->getHP() < critter->MAX_HP / 3)
		SetConsoleTextAttribute(hStdout, lightRed);
	else if (critter->getHP() < critter->MAX_HP / 2)
		SetConsoleTextAttribute(hStdout, darkYellow);
	gotoXY(statusSecondA->getX() + 2, statusSecondA->getY() + 4);
	cout << "HP: ";
	gotoXY(statusSecondA->getX() + 14, statusSecondA->getY() + 4);
	cout << critter->getHP() << "/" << critter->MAX_HP;
	gotoXY(statusSecondA->getX() + 2, statusSecondA->getY() + 6);

	/*Alien* a = dynamic_cast<Alien*>(critter);
	if (a != NULL)
	{
	cout << "Weapons: ";
	gotoXY(statusSecondA->getX() + 14, statusSecondA->getY() + 6);
	cout << critter->get;
	}*/
}

void GUI::clearArea(Point a, Point b)
{
	for (int x = a.getX() + 1; x < b.getX(); x++)
	{
		for (int y = a.getY() + 1; y < b.getY(); y++)
		{
			gotoXY(x, y);
			cout << " ";
		}
	}
}

void GUI::clearTextArea()
{
	consoleLineMarker = 0;
	clearArea(*textAreaA, *textAreaB);
}

void GUI::printToConsole(string text, int color, bool clear)
{
	SetConsoleTextAttribute(hStdout, color);

	if (clear)
		clearTextArea();

	string delimiter = "\n";

	string token = ".";
	for (; token != ""; consoleLineMarker++)
	{
		if (consoleLineMarker > textAreaB->getY() - textAreaA->getY() - 4)
			clearTextArea();
		token = "";
		token = text.substr(0, text.find(delimiter));
		text = text.substr(text.find(delimiter) + 1, text.length());
		gotoXY(textAreaA->getX() + 2, textAreaA->getY() + 2 + consoleLineMarker);
		cout << round << ": ";

		if (token.length() < (textAreaB->getX() - textAreaA->getX()))
			cout << token;
		else
		{
			for (int i = 0; i < token.length(); i++)
			{
				cout << token[i];
				int X = (textAreaB->getX() - textAreaA->getX()) - 7;
				if ((i % X) == 0 && i != 0)
					gotoXY(textAreaA->getX() + 5, textAreaA->getY() + 2 + ++consoleLineMarker);
			}
		}
		Sleep(250);
	}
}

string GUI::input()
{
	std::stringstream ss;
	SetConsoleTextAttribute(hStdout, white);

	string inputString;
	gotoXY(inputA->getX() + 2, inputA->getY() + 2);
	cin >> inputString;
	ss << inputString << endl;

	clearArea(*inputA, *inputB);

	return ss.str();
}

void GUI::waitForKey()
{
	string inputString;
	gotoXY(inputA->getX() + 2, inputA->getY() + 2);

	_getch();
}

void GUI::clearViewer()
{
	clearArea(*viewerA, *viewerB);
}

void GUI::writeToViewer(char ascii, int x, int y)
{
	SetConsoleTextAttribute(hStdout, lightGreen);

	int width = viewerB->getX() - viewerA->getX();
	int height = viewerB->getY() - viewerA->getY();

	int X = viewerA->getX() + width / 2 + x;
	int Y = viewerA->getY() + height / 2 + y;

	gotoXY(X, Y);
	cout << ascii;
}

Room* GUI::resetMap(Room* r)
{
	if (r == NULL)
		return NULL;

	r->resetPrinted();

	if (r->getNorth() != NULL && r->getNorth()->isPrinted())
		resetMap(r->getNorth());
	if (r->getEast() != NULL && r->getEast()->isPrinted())
		resetMap(r->getEast());
	if (r->getSouth() != NULL && r->getSouth()->isPrinted())
		resetMap(r->getSouth());
	if (r->getWest() != NULL && r->getWest()->isPrinted())
		resetMap(r->getWest());
}

Room* GUI::paintMap(Room* r, int x, int y)
{
	if (r == NULL)
		return NULL;

	r->setPrinted();
	if (r->isVisited())
	{
		writeToViewer(r->getName()[0], x, y);
		if (r->getNorth() != NULL)
			for (int i = 0; i < r->getDistNorth(); i++)
				writeToViewer(char(179), x, y - (i + 1));
		if (r->getEast() != NULL)
			for (int i = 0; i < r->getDistEast(); i++)
				writeToViewer(char(196), x + (i + 1), y);
		if (r->getSouth() != NULL)
			for (int i = 0; i < r->getDistSouth(); i++)
				writeToViewer(char(179), x, y + (i + 1));
		if (r->getWest() != NULL)
			for (int i = 0; i < r->getDistWest(); i++)
				writeToViewer(char(196), x - (i + 1), y);
	}

	if (r->getNorth()!= NULL && !r->getNorth()->isPrinted())
		paintMap(r->getNorth(), x, y - (1 + r->getDistNorth()));
	if (r->getEast() != NULL && !r->getEast()->isPrinted())
		paintMap(r->getEast(), x + (1 + r->getDistEast()), y);
	if (r->getSouth() != NULL && !r->getSouth()->isPrinted())
		paintMap(r->getSouth(), x, y + (1 + r->getDistSouth()));
	if (r->getWest() != NULL && !r->getWest()->isPrinted())
		paintMap(r->getWest(), x - (1 + r->getDistWest()), y);
}

void GUI::paint()
{
	paintOuterFrame();

	paintHeadLine();
	paintMainFrame();
	paintInputFrame();
	paintStatusBar();
}

void GUI::paintToView(int x, int y, char ascii, int color)
{
	int pX = viewerA->getX() + 1 + x;
	int pY = viewerA->getY() + 1 + y;

	SetConsoleTextAttribute(hStdout, color);
	if (pX < viewerB->getX() && pY < viewerB->getY())
	{
		gotoXY(pX, pY);
		cout << ascii;
	}
}

void GUI::paintTargetPicture()
{
	clearArea(*viewerA, *viewerB);
	Point* m = new Point((viewerB->getX() + viewerA->getX()) / 2, (viewerB->getY() + viewerA->getY()) / 2);
	int radius = (viewerB->getY() - viewerA->getY()) / 2 - 1;

	for (; radius > 3; radius--)
	{
		if (radius % 2)
			paintFilledCircle(*m, radius, 'o', darkRed);
		else
			paintFilledCircle(*m, radius, 'o', darkGrey);
	}

	paintFilledCircle(*m, radius - 2, 'o', lightYellow);
}

// max 72/21
void GUI::paintAlien()
{
	char oberstrich = 238;
	char untenAnf = ',';
	char komma = 127;
	char kreuz = 208;
	char B = 225;
	char P = 232;
	char PI = 146;
	char flamme = '&';
	char D = 209;
	char _7 = '7';

	int i = 0;

	clearArea(*viewerA, *viewerB);

	Color highLights;
	Color mainColor;

	if (critter->getName() == "Hatchling")
	{
		highLights = darkGreen;
		mainColor = lightGreen;
	}
	else if (critter->getName() == "Worker")
	{
		highLights = darkYellow;
		mainColor = lightYellow;
	}
	else if (critter->getName() == "Guard")
	{
		highLights = darkPink;
		mainColor = lightPink;
	}
	else if (critter->getName() == "Queen")
	{
		highLights = darkRed;
		mainColor = lightTurquoise;
	}

	/*01*/paintToView(25, ++i, P, highLights);
	/*02*/paintToView(23, ++i, komma, highLights); paintToView(24, i, kreuz, highLights);
	/*03*/paintToView(21, ++i, komma, highLights); paintToView(22, i, kreuz, highLights);
	/*04*/paintToView(19, ++i, komma, highLights); paintToView(20, i, P, highLights);
	/*05*/paintToView(17, ++i, komma, highLights); paintToView(18, i, flamme, highLights); paintToView(19, i, kreuz, highLights);
	/*06*/paintToView(15, ++i, komma, highLights); paintToView(16, i, D, highLights); paintToView(17, i, P, highLights);
	/*07*/paintToView(14, ++i, D, highLights); paintToView(15, i, flamme, highLights); paintToView(16, i, oberstrich, highLights);
	/*08*/paintToView(12, ++i, komma, highLights); paintToView(13, i, D, highLights); paintToView(14, i, flamme, highLights); paintToView(15, i, oberstrich, highLights);
	/*09*/paintToView(11, ++i, D, highLights); paintToView(12, i, flamme, highLights); paintToView(13, i, P, highLights);
	/*10*/paintToView(9, ++i, komma, highLights); paintToView(10, i, flamme, highLights); paintToView(11, i, flamme, highLights); paintToView(12, i, P, highLights);
	/*11*/paintToView(8, ++i, D, highLights); paintToView(9, i, flamme, mainColor); paintToView(10, i, flamme, mainColor); paintToView(11, i, flamme, mainColor); paintToView(12, i, kreuz, highLights);
	paintToView(20, i, untenAnf, highLights); paintToView(21, i, D, highLights); paintToView(22, i, flamme, highLights); paintToView(23, i, flamme, highLights); paintToView(24, i, P, highLights);
	/*12*/paintToView(7, ++i, D, highLights); paintToView(8, i, flamme, highLights); paintToView(9, i, flamme, mainColor); paintToView(10, i, flamme, mainColor); paintToView(11, i, flamme, mainColor);
	paintToView(12, i, B, highLights); paintToView(13, i, komma, highLights); paintToView(14, i, untenAnf, highLights); paintToView(15, i, untenAnf, highLights); paintToView(16, i, D, highLights);
	paintToView(17, i, flamme, highLights); paintToView(18, i, flamme, highLights); paintToView(19, i, flamme, highLights); paintToView(20, i, flamme, highLights); paintToView(21, i, flamme, highLights);
	paintToView(22, i, kreuz, highLights);
	/*13*/paintToView(5, ++i, komma, highLights); paintToView(6, i, flamme, highLights); paintToView(7, i, flamme, mainColor); paintToView(8, i, flamme, mainColor); paintToView(9, i, flamme, mainColor);
	paintToView(10, i, flamme, mainColor); paintToView(11, i, flamme, mainColor); paintToView(12, i, flamme, mainColor); paintToView(13, i, flamme, mainColor); paintToView(14, i, flamme, mainColor);
	paintToView(15, i, flamme, mainColor); paintToView(16, i, flamme, mainColor);	paintToView(17, i, flamme, mainColor);	paintToView(18, i, flamme, mainColor); paintToView(19, i, flamme, mainColor);
	paintToView(20, i, flamme, mainColor); paintToView(21, i, flamme, mainColor); paintToView(22, i, flamme, highLights); paintToView(23, i, B, highLights); paintToView(24, i, untenAnf, highLights);
	/*14*/paintToView(4, ++i, komma, highLights); paintToView(5, i, flamme, mainColor); paintToView(6, i, kreuz, mainColor); paintToView(7, i, kreuz, mainColor); paintToView(8, i, flamme, mainColor);
	paintToView(9, i, flamme, mainColor); paintToView(10, i, flamme, mainColor); paintToView(11, i, flamme, mainColor); paintToView(12, i, flamme, mainColor); paintToView(13, i, P, mainColor);
	paintToView(14, i, kreuz, mainColor); paintToView(15, i, kreuz, mainColor); paintToView(16, i, kreuz, mainColor); paintToView(17, i, kreuz, mainColor);	paintToView(18, i, kreuz, mainColor);
	paintToView(19, i, _7, mainColor); paintToView(20, i, flamme, mainColor); paintToView(21, i, flamme, mainColor); paintToView(22, i, flamme, mainColor);	paintToView(23, i, flamme, highLights);
	paintToView(24, i, flamme, highLights); paintToView(25, i, flamme, highLights); paintToView(26, i, flamme, highLights); paintToView(27, i, flamme, highLights);	paintToView(28, i, B, highLights);
	paintToView(29, i, 'R', highLights);
	/*15*/paintToView(3, ++i, komma, highLights); paintToView(4, i, flamme, mainColor); paintToView(5, i, char(47), lightRed); paintToView(6, i, char(238), lightRed); paintToView(7, i, flamme, mainColor);
	paintToView(8, i, flamme, mainColor); paintToView(9, i, flamme, mainColor); paintToView(10, i, flamme, mainColor); paintToView(11, i, kreuz, mainColor); paintToView(20, i, oberstrich, mainColor);
	paintToView(21, i, flamme, mainColor); paintToView(22, i, flamme, mainColor); paintToView(23, i, flamme, mainColor); paintToView(24, i, flamme, mainColor); paintToView(25, i, flamme, mainColor);
	paintToView(26, i, kreuz, highLights);
	/*16*/paintToView(3, ++i, char(245), highLights); paintToView(4, i, flamme, mainColor); paintToView(5, i, PI, mainColor); paintToView(6, i, flamme, mainColor); paintToView(7, i, flamme, mainColor);
	paintToView(8, i, flamme, mainColor); paintToView(9, i, kreuz, mainColor); paintToView(20, i, komma, mainColor); paintToView(21, i, flamme, mainColor); paintToView(22, i, flamme, mainColor);
	paintToView(23, i, flamme, mainColor); paintToView(24, i, flamme, mainColor); paintToView(25, i, flamme, mainColor); paintToView(26, i, B, mainColor); paintToView(27, i, PI, highLights);
	/*17*/paintToView(2, ++i, komma, highLights); paintToView(3, i, D, mainColor); paintToView(4, i, flamme, mainColor); paintToView(5, i, flamme, mainColor); paintToView(6, i, flamme, mainColor);
	paintToView(7, i, oberstrich, mainColor); paintToView(19, i, komma, mainColor); paintToView(20, i, flamme, mainColor); paintToView(21, i, flamme, mainColor); paintToView(22, i, flamme, mainColor);
	paintToView(23, i, flamme, mainColor); paintToView(24, i, flamme, mainColor); paintToView(25, i, flamme, mainColor); paintToView(26, i, flamme, mainColor);	paintToView(27, i, kreuz, highLights);
	paintToView(28, i, kreuz, highLights); paintToView(29, i, kreuz, highLights);
	/*18*/paintToView(1, ++i, komma, highLights); paintToView(2, i, D, mainColor); paintToView(3, i, flamme, mainColor); paintToView(4, i, flamme, mainColor); paintToView(5, i, P, mainColor);
	paintToView(6, i, oberstrich, mainColor); paintToView(18, i, komma, mainColor); paintToView(19, i, flamme, mainColor); paintToView(20, i, flamme, mainColor); paintToView(21, i, flamme, mainColor);
	paintToView(22, i, flamme, mainColor); paintToView(23, i, flamme, mainColor); paintToView(24, i, flamme, mainColor); paintToView(25, i, flamme, mainColor);	paintToView(26, i, P, mainColor);
	paintToView(27, i, B, highLights);
	/*19*/paintToView(1, ++i, flamme, highLights); paintToView(2, i, flamme, mainColor); paintToView(3, i, flamme, mainColor); paintToView(4, i, 'v', darkRed); paintToView(17, i, komma, mainColor);
	paintToView(18, i, flamme, mainColor); paintToView(19, i, flamme, mainColor); paintToView(20, i, flamme, mainColor); paintToView(21, i, flamme, mainColor); paintToView(22, i, flamme, mainColor);
	paintToView(23, i, flamme, mainColor); paintToView(24, i, flamme, mainColor); paintToView(25, i, flamme, mainColor); paintToView(26, i, kreuz, highLights); paintToView(27, i, kreuz, highLights);
	/*20*/paintToView(1, ++i, oberstrich, highLights); paintToView(2, i, flamme, mainColor); paintToView(3, i, 'v', darkRed); paintToView(16, i, komma, mainColor); paintToView(17, i, flamme, mainColor);
	paintToView(18, i, flamme, mainColor); paintToView(19, i, flamme, mainColor); paintToView(20, i, flamme, mainColor); paintToView(21, i, flamme, mainColor); paintToView(22, i, flamme, mainColor);
	paintToView(23, i, flamme, mainColor); paintToView(24, i, flamme, mainColor); paintToView(25, i, flamme, highLights);
}
