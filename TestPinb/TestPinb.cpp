/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */


// TestPinb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "OOP\Pinball.h"
#include "OOP\PinballObject.h"
#include "OOP\HardwareSerial.h"
#include "OOP\Input.h"
#include "OOP\Output.h"
#include "OOP\SlingShot.h"
#include "OOP\Bumper.h"
#include "OOP\KickoutHole.h"
#include "OOP\Utils.h"

void InitObjectsToPinballMaster(Pinball *pPinball)
{
	PinballObject *pInput1 = new Input("input1", pPinball, 1);

	Output *pOutput = new Output("output", pPinball, 2);

	SlingShot *pSling = new SlingShot("sling", pPinball, 3, 4, 5);
	Bumper *pBumper = new Bumper("bumper", pPinball, 6, 7);
	KickoutHole *pHole = new KickoutHole("hole", pPinball, 8, 9);

	pOutput->TurnOnByTimer(500);
}

void InitObjectsToPinballSlave(Pinball *pPinball)
{
	SlingShot *pSling = new SlingShot("sling2", pPinball, 1, 2, 3);
}

int ikeyCount = 0;
char szKey[80];
int Ard = 0;


void PrintReadKey()
{
	int x = 70;
	int y = 20;
	clrbox(x, y, x + 15, y + 2, BLACK);

	setcolor(WHITE);
	box(x, y, x + 15, y + 2, y + 7, y + 7, "Key");
	gotoxy(x + 2, y + 1);
	printf("Read Key :");
}

int ReadKey()
{
	if (_kbhit())
	{
		char  ch = _getch();
		if (ch >= '0' && ch <= '9')
		{
			szKey[ikeyCount] = ch;
			ikeyCount++;
			szKey[ikeyCount] = 0;
		}
		else if (ch == 27)
		{
			return -2;
		}
		else if (ch == 13)
		{
			int sw = atoi(szKey);
			ikeyCount = 0;
			szKey[ikeyCount] = 0;
			PrintReadKey();
			return sw;
		}

		PrintReadKey();
		printf("%s", szKey);

	}

	return -1;
}

int main()
{
	HardwareSerial *serial = new HardwareSerial();
	Pinball *pPinballMaster = new Pinball("Master", serial, true);
	InitObjectsToPinballMaster(pPinballMaster);

	HardwareSerial *serial2 = new HardwareSerial(100);
	Pinball *pPinballSlave = new Pinball("Slave", serial2);
	InitObjectsToPinballSlave(pPinballSlave);

	pPinballMaster->Init();
	pPinballSlave->Init();

	PrintReadKey();

	int ch = 0;
	do
	{
		ch = ReadKey();
		if (ch != -2 && ch != -1)
		{
			if (ch > 200)
			{
				pPinballSlave->Loop(ch-200);
			}
			else
			{
				pPinballMaster->Loop(ch);
			}

			gotoxy(72 + 10 + ikeyCount, 21);
		}
		else
		{
			pPinballMaster->Loop(0);
			pPinballSlave->Loop(0);
		}

	} while (ch != -2);

	delete  pPinballMaster;
	delete  pPinballSlave;

    return 0;
}

