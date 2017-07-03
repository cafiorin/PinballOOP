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

int main()
{
	HardwareSerial *serial = new HardwareSerial();
	Pinball *pPinballMaster = new Pinball("Master", serial, true);

	printf("==== Input === \n\n");
	PinballObject *pInput1 = new Input("input1", pPinballMaster,1);

	printf("\n\n==== Output === \n\n");
	Output *pOutput= new Output("output", pPinballMaster,2);

	printf("\n\n==== SlingShot, Bumper and KickoutHole === \n\n");
	SlingShot *pSling = new SlingShot("sling", pPinballMaster, 3, 4, 5);
	Bumper *pBumper = new Bumper("bumper", pPinballMaster, 6, 7);
	KickoutHole *pHole = new KickoutHole("hole", pPinballMaster, 8, 9);

	printf("\n\n==== Init === \n\n");
	pPinballMaster->Init();

	//Test output
	pOutput->TurnOnByTimer(500);

	printf("\n\n==== START LOOP use ESC to exit === \n\n");
	int ch = 0;

	do
	{
		if (_kbhit())
		{
			ch = _getch();
			printf("Key pressed : %c\n", ch);
		}
		else
		{
			ch = 0;
		}


		//printf("\n\n==== Loop === \n\n");
		pPinballMaster->Loop(ch - '0');
	} while (ch != 27);

	printf("\n\n==== Destruct === \n\n");
	delete  pPinballMaster;

    return 0;
}

