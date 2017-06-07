// TestPinb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "OOP\Pinball.h"
#include "OOP\PinballObject.h"
#include "OOP\HardwareSerial.h"
#include "OOP\Input.h"
#include "OOP\Output.h"

int main()
{
	HardwareSerial *serial = new HardwareSerial();
	Pinball *pPinballMaster = new Pinball("Master", serial, true);

	//PinballObject *pObj1 = new PinballObject("t1", pPinballMaster);
	//PinballObject *pObj2 = new PinballObject("t2", pPinballMaster);
	//PinballObject *pObj3 = new PinballObject("t3", pPinballMaster);
	printf("==== Input === \n\n");
	PinballObject *pInput = new Input("i0", pPinballMaster,1);

	printf("\n\n==== Output === \n\n");
	PinballObject *pOutput= new Output("i1", pPinballMaster,2);

	printf("\n\n==== Init === \n\n");
	pPinballMaster->Init();

	printf("\n\n==== Loop === \n\n");
	pPinballMaster->Loop();

	printf("\n\n==== Destruct === \n\n");
	delete  pPinballMaster;

	getchar();
    return 0;
}

