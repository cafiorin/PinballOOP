/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef defines_h
#define defines_h

#define TIME_COIL_ON 20

#define DEBUGMESSAGES
//#define DEBUGMESSAGESLOOP

#define DOS
//#define ARDUINO

#ifdef ARDUINO
#include "Arduino.h"
#endif //ARDUINO

#ifdef DOS
#include "..\stdafx.h"
#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <conio.h>
#include <iostream>
#include <Windows.h>

using namespace std;

#endif // DOS

#endif