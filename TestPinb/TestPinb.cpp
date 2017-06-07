// TestPinb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "OOP\PinballArduino.h"
#include "OOP\PinballObject.h"
#include "OOP\HardwareSerial.h"

int main()
{
	HardwareSerial *serial = new HardwareSerial();
	PinballArduino *pPinballMaster = new PinballArduino("Master", serial, true);

	PinballObject *pObj1 = new PinballObject("t1", pPinballMaster);
	PinballObject *pObj2 = new PinballObject("t2", pPinballMaster);
	PinballObject *pObj3 = new PinballObject("t3", pPinballMaster);

	pPinballMaster->Init();
	pPinballMaster->Loop();

	getchar();
    return 0;
}

