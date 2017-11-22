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

void printLeds(PinballMaster *pPinballMaster, HardwareSerial *ledPrint)
{
	ledPrint->printbox(30, (NUM_LEDS/2)+2, "Led");
	ledPrint->m_YInit = 1;
	ledPrint->m_XInit = 100;

	int i = 0;
	for (; i < NUM_LEDS/2; i++)
	{
		char szMsg[30];
		sprintf(szMsg, "L%d=>%d", i, (pPinballMaster->m_LedControl->IsTurn(i) ? 1 : 0));
		ledPrint->printone(szMsg);
	}

	ledPrint->ResetLine();
	ledPrint->m_YInit = 1;
	ledPrint->m_XInit = 115;

	for (; i < NUM_LEDS; i++)
	{
		char szMsg[30];
		sprintf(szMsg, "L%d=>%d", i, (pPinballMaster->m_LedControl->IsTurn(i)?1:0));
		ledPrint->printone(szMsg);
	}
}


int main()
{
	bool firstPrint = true;
	bool Leds[NUM_LEDS];

	HardwareSerial *serial = new HardwareSerial();
	PinballMaster *pPinballMaster = new PinballMaster("Master", serial);

	HardwareSerial *serial2 = new HardwareSerial(100);
	PinballSlave *pPinballSlave = new PinballSlave("Slave", serial2);

	HardwareSerial *ledPrint = new HardwareSerial(100, 1);

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

	for (int i = 0; i < NUM_LEDS; i++)
	{
		Leds[i] = pPinballMaster->m_LedControl->IsTurn(i);
	}

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
		
		if (firstPrint)
		{
			printLeds(pPinballMaster, ledPrint);
			firstPrint = false;
		}
		else
		{
			for (int i = 0; i < NUM_LEDS; i++)
			{
				if (Leds[i] != pPinballMaster->m_LedControl->IsTurn(i))
				{
					printLeds(pPinballMaster, ledPrint);
					break;
				}
			}
		}

		pPinballMaster->Loop(0);
		pPinballSlave->Loop(0);

	} while (ch != -2);

	delete  pPinballMaster;
	delete  pPinballSlave;
	delete ledPrint;
    return 0;
}
