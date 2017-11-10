/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef defines_h
#define defines_h

//-----------------------
//#define DOS
#define ARDUINOLIB
//-----------------------

#define ADDRESS_MASTER 4
#define ADDRESS_SLAVE  5
#define INIT_THEME 0

#define MAX_BALLS 3
#define MAX_PLAYERS 8

#define TIME_COIL_ON 20

//Events
#define EVENT_EDGEPOSITIVE 1
#define EVENT_EDGENEGATIVE 2
#define EVENT_DROPTARGETDOWN 3
#define EVENT_TIMEISOVER 4

#define DEBUGMESSAGES
//#define DEBUGMESSAGESLOOP

//Inputs
#define INPUT_START_BUTTON 0
#define INPUT_MENU_BUTTON 1


#define I0 0
#define I1 1
#define I2 2
#define I3 3
#define I4 4
#define I5 5
#define I6 6
#define I7 7
#define I8 8
#define I9 9
#define I10 10
#define I11 11
#define I12 12
#define I13 13
#define I14 14
#define I15 15
#define I16 16
#define I17 17
#define I18 18
#define I19 19
#define I20 20
#define I21 21
#define I22 22
#define I23 23
#define I24 24
#define I25 25
#define I26 26
#define I27 27
#define I28 28
#define I29 29
#define I30 30
#define I31 31
#define I32 32
#define I33 33
#define I34 34
#define I35 35
#define I36 36
#define I37 37
#define I38 38
#define I39 39
#define I40 40
#define I41 41

#define Out0 0
#define Out1 1
#define Out2 2
#define Out3 3
#define Out4 4
#define Out5 5
#define Out6 6
#define Out7 7
#define Out8 8
#define Out9 9
#define Out10 10
#define Out11 11
#define Out12 12


#ifdef ARDUINOLIB
#include "Arduino.h"
#pragma GCC diagnostic ignored "-Wwrite-strings"
#define DEBOUNCEREAD 5
#endif //ARDUINOLIB

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
#define DEBOUNCEREAD 0

#endif // DOS

#endif