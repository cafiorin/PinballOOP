/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// TestPinb.cpp : Defines the entry pouint8_t for the console application.
// use with #define DOS and comment define ARDUINOLIB

#include "stdafx.h"
#include "OOP\PinballMaster.h"
#include "OOP\PinballSlave.h"
#include "OOP\HardwareSerial.h"
#include "OOP\Utils.h"
#include "OOP\Input.h"
#include "OOP\LedControl.h"

uint8_t ikeyCount = 0;
char szKey[80];
uint8_t Ard = 0;


void PrintReadKey()
{
	uint8_t x = 70;
	uint8_t y = 20;
	clrbox(x, y, x + 18, y + 2, BLACK);

	setcolor(WHITE);
	box(x, y, x + 18, y + 2, y + 7, y + 7, "");
	gotoxy(x + 2, y + 1);
	printf("Read Key :");
}

void PrintTime(long time)
{
	uint8_t x = 70;
	uint8_t y = 40;
	clrbox(x, y, x + 18, y + 2, BLACK);

	setcolor(WHITE);
	box(x, y, x + 18, y + 2, y + 7, y + 7, "");
	gotoxy(x + 2, y + 1);
	printf("Time :%ld ms", time);
}


uint8_t ReadKey()
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
			uint8_t sw = atoi(szKey);
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
	LedControl *pLedControl = pPinballMaster->GetLedControl();
	if (pLedControl != NULL)
	{
		ledPrint->printbox(30, (NUM_LEDS / 2) + 2, "Led");
		ledPrint->m_YInit = 1;
		ledPrint->m_XInit = 100;

		uint8_t i = 0;
		for (; i < NUM_LEDS / 2; i++)
		{
			char szMsg[30];
			sprintf(szMsg, "L%d=>%d", i, (pLedControl->IsTurn(i) ? 1 : 0));
			ledPrint->printone(szMsg);
		}

		ledPrint->ResetLine();
		ledPrint->m_YInit = 1;
		ledPrint->m_XInit = 115;

		for (; i < NUM_LEDS; i++)
		{
			char szMsg[30];
			sprintf(szMsg, "L%d=>%d", i, (pLedControl->IsTurn(i) ? 1 : 0));
			ledPrint->printone(szMsg);
		}
	}
}


uint8_t main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	bool firstPrint = true;
	bool Leds[NUM_LEDS];

	HardwareSerial *serial = new HardwareSerial(0,0);
	PinballMaster *pPinballMaster = new PinballMaster(serial);
	HardwareSerial *ledPrint = new HardwareSerial(100, 1);

	HardwareSerial *inputs = new HardwareSerial(1, 30);
	inputs->println("Menu/Up/Down/Enter - 0,1,2,3");
	inputs->println("=>Start Button - 4");
	inputs->println("OUTBALL1/2     - 5,6");
	inputs->println("LAUNCHBALL     - 7");
	inputs->println("SLINGSHOT L1/L2- 8,9");
	inputs->println("SLINGSHOT R1/R2- 10,11");
	inputs->println("OUTLANE_L/R    - 12,13");
	inputs->println("RETURNBALL_L/R - 14,15");
	inputs->println("TARGET_RED1    - 16");
	inputs->println("TARGET_GREEN1  - 17");
	inputs->println("TARGET_YELLOW1 - 18");
	inputs->println("TARGET_RED2    - 19");
	inputs->println("TARGET_GREEN2  - 20");
	inputs->println("TARGET_YELLOW2 - 21");
	inputs->println("DTARGET_51-55  - 22-26");
	inputs->println("DTARGET_31-33  - 27-29");
	inputs->println("STAR G R1/R2   - 30,31,32");
	inputs->println("=> ROVER_L/C/R - 33,34,35");
	inputs->println("BUMPER_L/C/R   - 36,37,38");
	inputs->println("TARGET_HIGHER  - 39");
	inputs->println("RAMP_IN        - 40");
	inputs->println("RAMP_OUT1,2    - 41,42");
	inputs->println("SPINNER        - 43");
	inputs->println("HOLE           - 44");
	inputs->println("ACCBALL1       - 45-48");

	if (pPinballMaster->GetLedControl() != NULL)
	{
		for (uint8_t i = 0; i < NUM_LEDS; i++)
		{
			Leds[i] = pPinballMaster->GetLedControl()->IsTurn(i);
		}
	}

	PrintReadKey();

	uint8_t ch = 0;
	long lastTime = 0;
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
			if (pPinballMaster->GetLedControl() != NULL)
			{
				bool someChange = false;
				for (uint8_t i = 0; i < NUM_LEDS; i++)
				{
					if (Leds[i] != pPinballMaster->GetLedControl()->IsTurn(i))
					{
						Leds[i] = pPinballMaster->GetLedControl()->IsTurn(i);
						someChange = true;
					}
				}
				if (someChange)
				{
					printLeds(pPinballMaster, ledPrint);
				}
			}
		}

		long t1 = Millis();
		pPinballMaster->Loop(0);
		long t2 = Millis() - t1;
		if (lastTime < t2)
		{
			PrintTime(Millis() - t1);
			lastTime = t2;

			PrintReadKey();
		}

	} while (ch != -2);

	//CheckMemoryLeak();

	//delete serial;
	delete inputs;
	delete pPinballMaster;
	delete ledPrint;
    return 0;
}
