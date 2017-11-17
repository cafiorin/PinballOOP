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
#include "OOP\Input.h"

int ikeyCount = 0;
char szKey[80];
int Ard = 0;


void PrintReadKey()
{
	int x = 70;
	int y = 20;
	clrbox(x, y, x + 18, y + 2, BLACK);

	setcolor(WHITE);
	box(x, y, x + 18, y + 2, y + 7, y + 7, "");
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
		else if (ch == 13) // ENTER
		{
			int sw = atoi(szKey);
			ikeyCount = 0;
			szKey[ikeyCount] = 0;
			PrintReadKey();
			return sw;
		}
		else if (ch == 127 || ch == 8) //BACKSPACE
		{
			if (ikeyCount > 0)
			{
				ikeyCount--;
				szKey[ikeyCount] = 0;
			}
		}

		PrintReadKey();
		printf("%s  ", szKey);
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
	inputs->println("Start Button - 00");
	inputs->println("Menu  Button - 01");
	inputs->println("Up Button    - 02");
	inputs->println("Down Button  - 03");
	
	inputs->println("OUTBALL1     - 04");
	inputs->println("OUTBALL2     - 05");
	inputs->println("LAUNCHBALL   - 06");
	inputs->println("SLINGSHOT_LEFT1 - 07");
	inputs->println("SLINGSHOT_LEFT2 - 08");
	inputs->println("SLINGSHOT_RIGHT1- 09");
	inputs->println("SLINGSHOT_RIGHT2- 10");
	inputs->println("OUTLANE_LEFT    - 11");
	inputs->println("OUTLANE_RIGHT   - 12");
	inputs->println("RETURNBALL_LEFT - 13");
	inputs->println("RETURNBALL_RIGHT- 14");


	PrintReadKey();

	int ch = 0;
	do
	{
		ch = ReadKey();
		if (ch != -2 && ch != -1)
		{
			Input *input = pPinballMaster->GetInput(ch);
			if (input != NULL)
			{
				bool value = input->GetInput();
				input->SetInput(!value);

				gotoxy(72 + 10 + ikeyCount, 21);
			}
		}
		
		pPinballMaster->Loop(0);
		pPinballSlave->Loop(0);

	} while (ch != -2);

	delete  pPinballMaster;
	delete  pPinballSlave;

    return 0;
}

