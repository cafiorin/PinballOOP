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
#include "OOP\DropTarget.h"
#include "OOP\DropTargetWithRemoteInput.h"
#include "OOP\OutBall.h"
#include "OOP\Utils.h"

void InitObjectsToPinballMaster(Pinball *pPinball)
{
	Output *pTurnFlipperOn = new Output("TFO", pPinball, O0);

	OutBall *pOutBall = new OutBall("OB", pPinball, I1, O1, I2, O2);
	SlingShot *pSlingShotLeft = new SlingShot("SLL", pPinball, I3, I3ALT, O3);
	SlingShot *pSlingShotRight = new SlingShot("SLR", pPinball, I4, I4ALT, O4);

	Input *pInputOutLaneLeft = new Input("OLL", pPinball, I5);
	Input *pInputReturnBallLeft  = new Input("RBL", pPinball, I6);
	Input *pInputReturnBallRight = new Input("RBR", pPinball, I7);
	Input *pInputOutLaneRight = new Input("OLR", pPinball, I8);

	Input *pInputTargetGreen1 = new Input("TG1", pPinball, I9);
	Input *pInputTargetRed1   = new Input("TR1", pPinball, I10);

	DropTarget *pDropTarget5 = new DropTarget("DT5", pPinball, I11,I12,I13,I14,I15,O5);
	Input *pInputRolloverStarRed1 = new Input("RSR1", pPinball, I16);
	DropTargetWithRemoteInput *pDropTarget3 = new DropTargetWithRemoteInput("DT3", pPinball, I17, I18, I19, O6);

	Input *pInputTargetRed2    = new Input("TR2", pPinball, I20);
	Input *pInputTargetYellow2 = new Input("TY2", pPinball, I21);
	Input *pInputTargetGreen2  = new Input("TG2", pPinball, I22);

	Input *pInputTargetYellow1 = new Input("TY1", pPinball, I23);

	KickoutHole *pHole    = new KickoutHole("HOLE", pPinball, I24, O7);
	Bumper *pBumperLeft   = new Bumper("BL", pPinball, I25, O8);
	Bumper *pBumperCenter = new Bumper("BC", pPinball, I26, O9);
	Bumper *pBumperRight  = new Bumper("BR", pPinball, I27, O10);

	Input *pInputRolloverStarGreen = new Input("RSG", pPinball, I28);

	Input *pInputRolloverLeft   = new Input("RML", pPinball, I29);
	Input *pInputRolloverCenter = new Input("RMC", pPinball, I30);
	Input *pInputRolloverRight  = new Input("RMR", pPinball, I31);

	Input *pInputRolloverStarRed2 = new Input("RSR2", pPinball, I32);

	Input *pInputTargetHigher = new Input("TH", pPinball, I33);

	Input *pInputSpinner = new Input("Spin", pPinball, I37);
}

void InitObjectsToPinballSlave(Pinball *pPinball)
{
	Input *pInputDropTarget31 = new Input("DT31", pPinball, I17);
	Input *pInputDropTarget32 = new Input("DT32", pPinball, I18);
	Input *pInputDropTarget33 = new Input("DT33", pPinball, I19);

	Input *pInputRampIn = new Input("RampIn", pPinball, I34);
	Input *pInputRampOut1 = new Input("RampO1", pPinball, I35);
	Input *pInputRampOut2 = new Input("RampO2", pPinball, I36);

	Input *pInputStartButton = new Input("SB", pPinball, I38);
	Input *pInputMenu = new Input("BM", pPinball, I39);
	Input *pInputVolumePlus = new Input("VP", pPinball, I40);
	Input *pInputVolumeMinus = new Input("VM", pPinball, I41);
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

