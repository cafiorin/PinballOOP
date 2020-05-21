/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// TestPinb.cpp : Defines the entry pobyte for the console application.
// use with #define DOS and comment define ARDUINOLIB

#include "stdafx.h"
#include "PinballClasses\\PinballMachine.h"
#include "PinballClasses\\HardwareSerial.h"
#include "PinballClasses\\Utils.h"
#include "PinballClasses\\BitInput.h"
#include "PinballClasses\\Button.h"
#include "PinballClasses\\LedControl.h"
#include "PinballClasses\\MultiplexInputs.h"
#include "PinballClasses\\Door.h"

byte ikeyCount = 0;
char szKey[80];
byte Ard = 0;


void PrintReadKey()
{
	byte x = 70;
	byte y = 20;
	clrbox(x, y, x + 18, y + 2, BLACK);

	setcolor(WHITE);
	box(x, y, x + 18, y + 2, y + 7, y + 7, "");
	gotoxy(x + 2, y + 1);
	printf("Read Key :");
}

void PrintTime(unsigned long time)
{
	byte x = 70;
	byte y = 40;
	clrbox(x, y, x + 18, y + 2, BLACK);

	setcolor(WHITE);
	box(x, y, x + 18, y + 2, y + 7, y + 7, "");
	gotoxy(x + 2, y + 1);
	printf("Time :%ld ms", time);
}


int ReadKey()
{
	if (_kbhit())
	{
		int  ch = _getch();
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
			byte sw = atoi(szKey);
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

void printLeds(PinballMachine *pPinballMaster, HardwareSerial *ledPrint)
{
	LedControl *pLedControl = pPinballMaster->GetLedControl();
	if (pLedControl != NULL)
	{
		ledPrint->printbox(30, (NUM_LEDS / 2) + 2, "Led");
		ledPrint->m_YInit = 1;
		ledPrint->m_XInit = 100;

		byte i = 0;
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

Button* GetInputArduino(PinballMachine *pPinballMaster, byte port)
{
	switch (port)
	{
	case INPUT_MENU_BUTTON:
		return pPinballMaster->GetDoor()->GetMenuButton();
		break;
	case INPUT_UP_BUTTON:
		return pPinballMaster->GetDoor()->GetUpButton();
		break;
	case INPUT_DOWN_BUTTON:
		return pPinballMaster->GetDoor()->GetDownButton();
		break;
	case INPUT_ENTER_BUTTON:
		return pPinballMaster->GetDoor()->GetEnterButton();
		break;
	case INPUT_START_BUTTON:
		return pPinballMaster->GetDoor()->GetStartButton();
		break;
	}

	return NULL;
}


byte main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	bool firstPrint = true;
	bool Leds[NUM_LEDS];

	HardwareSerial *serial = new HardwareSerial(0,0);
	PinballMachine *pPinballMaster = new PinballMachine(serial);
	HardwareSerial *ledPrint = new HardwareSerial(100, 1);

	HardwareSerial *inputs = new HardwareSerial(1, 30);
	inputs->println("Menu/Up/Down/Enter - 44,45,46,47");
	inputs->println("=>Start Button - 48");
	inputs->println("OUTBALL1/2     - 0,1");
	inputs->println("LAUNCHBALL     - 2");
	inputs->println("SLINGSHOT L1/L2- 4,6");
	inputs->println("SLINGSHOT R1/R2- 7,8");
	inputs->println("OUTLANE_L/R    - 5,9");
	inputs->println("RETURNBALL_L/R - 3,10");
	inputs->println("TARGET_RED1    - 13");
	inputs->println("TARGET_GREEN1  - 11");
	inputs->println("TARGET_YELLOW1 - 28");
	inputs->println("TARGET_RED2    - 18");
	inputs->println("TARGET_GREEN2  - 26");
	inputs->println("TARGET_YELLOW2 - 25");
	inputs->println("DTARGET_51-55  - 34,37,41,36,33");
	inputs->println("DTARGET_31-33  - 38,39,40");
	inputs->println("STAR G R1/R2   - 30,21,22");
	inputs->println("ROVER L/C/R    - 17,20,15");
	inputs->println("BUMPER_L/C/R   - 24,27,14");
	inputs->println("RAMP_IN        - 35");
	inputs->println("RAMP_OUT1,2    - 42,43");
	inputs->println("SPINNER        - 12");
	inputs->println("HOLE           - 19");
	inputs->println("ACCBALL1       - 29,32,23,31,16");

	if (pPinballMaster->GetLedControl() != NULL)
	{
		for (byte i = 0; i < NUM_LEDS; i++)
		{
			Leds[i] = pPinballMaster->GetLedControl()->IsTurn(i);
		}
	}

	PrintReadKey();

	int ch = 0;
	unsigned long lastTime = 0;
	do
	{
		ch = ReadKey();
		if (ch != -2 && ch != -1)
		{
			if (ch < INPUT_MENU_BUTTON)
			{
				BitInput *input = pPinballMaster->GetMuxInputs()->GetInput(ch);
				if (input != NULL)
				{
					bool value = input->GetInput();
					input->SetInput(!value);
					gotoxy(72 + 10 + ikeyCount, 21);
				}
			}
			else
			{
				Button* pButton = GetInputArduino(pPinballMaster, ch);
				if (pButton != NULL)
				{
					bool value = pButton->GetInput();
					pButton->SetState(true);
				}
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
				for (byte i = 0; i < NUM_LEDS; i++)
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

		unsigned long t1 = Millis();
		pPinballMaster->Loop();
		unsigned long t2 = Millis() - t1;
		if (lastTime < t2)
		{
			PrintTime(Millis() - t1);
			lastTime = t2;

			PrintReadKey();
		}

	} while (ch != -2);

	//CheckMemoryLeak();

	delete inputs;
	delete pPinballMaster;
	delete ledPrint;
	delete serial;
	return 0;
}
