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
	bool firstPrint = true;
	bool Leds[NUM_LEDS];

	HardwareSerial *serial = new HardwareSerial();
	PinballMaster *pPinballMaster = new PinballMaster("Master", serial);

	HardwareSerial *serial2 = new HardwareSerial(100);
	PinballSlave *pPinballSlave = new PinballSlave("Slave", serial2);

	HardwareSerial *ledPrint = new HardwareSerial(100, 1);

	pPinballSlave->SetPinballMaster(pPinballMaster);

	HardwareSerial *inputs = new HardwareSerial(1, 30);
	inputs->println("Menu/Up/Down   - 0,1,2");
	inputs->println("=>Start Button - 3");
	inputs->println("OUTBALL1/2     - 4,5");
	inputs->println("LAUNCHBALL     - 6");
	inputs->println("SLINGSHOT L1/L2- 7,8");
	inputs->println("SLINGSHOT R1/R2- 9,10");
	inputs->println("OUTLANE_L/R    - 11,12");
	inputs->println("RETURNBALL_L/R - 13,14");
	inputs->println("TARGET_RED1    - 15");
	inputs->println("TARGET_GREEN1  - 16");
	inputs->println("TARGET_YELLOW1 - 17");
	inputs->println("TARGET_RED2    - 18");
	inputs->println("TARGET_GREEN2  - 19");
	inputs->println("TARGET_YELLOW2 - 20");
	inputs->println("DTARGET_51-55  - 21-25");
	inputs->println("DTARGET_31-33  - 26-28");
	inputs->println("STAR G R1/R2   - 29,30,31");
	inputs->println("=> ROVER_L/C/R - 32,33,34");
	inputs->println("BUMPER_L/C/R   - 35,36,37");
	inputs->println("TARGET_HIGHER  - 38");
	inputs->println("RAMP_IN        - 39");
	inputs->println("RAMP_OUT1,2    - 40,41");
	inputs->println("SPINNER        - 42");
	inputs->println("HOLE           - 43");
	inputs->println("ACCBALL1       - 44-47");

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

		pPinballSlave->Loop(0);

	} while (ch != -2);

	delete  pPinballMaster;
	delete  pPinballSlave;
	delete ledPrint;
    return 0;
}
