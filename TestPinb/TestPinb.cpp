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

int main()
{
	HardwareSerial *serial = new HardwareSerial();
	Pinball *pPinballMaster = new Pinball("Master", serial, true);

	//PinballObject *pObj1 = new PinballObject("t1", pPinballMaster);
	//PinballObject *pObj2 = new PinballObject("t2", pPinballMaster);
	//PinballObject *pObj3 = new PinballObject("t3", pPinballMaster);
	printf("==== Input === \n\n");
	PinballObject *pInput1 = new Input("input1", pPinballMaster,1);
	PinballObject *pInput2 = new Input("input2", pPinballMaster,2);
	//PinballObject *pInput3 = new Input("input3", pPinballMaster,3);

	printf("\n\n==== Output === \n\n");
	Output *pOutput= new Output("output", pPinballMaster,2);

	printf("\n\n==== SlingShot === \n\n");
	SlingShot *pSling = new SlingShot("sling", pPinballMaster, 3,4,5);


	printf("\n\n==== Init === \n\n");
	pPinballMaster->Init();

	//Test output
	pOutput->TurnOnByTimer(2000);

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

