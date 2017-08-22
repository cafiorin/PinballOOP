/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */


// TestPinb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "OOP\PinballMaster.h"
#include "OOP\PinballSlave.h"
#include "OOP\HardwareSerial.h"
#include "OOP\Utils.h"

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
	PinballMaster *pPinballMaster = new PinballMaster("Master", serial);

	HardwareSerial *serial2 = new HardwareSerial(100);
	PinballSlave *pPinballSlave = new PinballSlave("Slave", serial2);

	pPinballSlave->SetPinballMaster(pPinballMaster);

	HardwareSerial *inputs = new HardwareSerial(1, 30);
	inputs->println("Start Button - 238");
	inputs->println("Menu  Button - 239");
	inputs->println("Up Button    - 240");
	inputs->println("Down Button  - 241");

	inputs->println("DT31    - 217");
	inputs->println("DT32    - 218");
	inputs->println("DT33    - 219");
	inputs->println("RampIn  - 234");
	inputs->println("RampOut1- 235");
	inputs->println("RampOut2- 236");
	
	inputs->println("Inputs - 01 - 37");

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

