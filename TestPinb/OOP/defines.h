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
#define INPUT_UP_BUTTON 2
#define INPUT_DOWN_BUTTON 3

#define INPUT_SW_OUTBALL1 4  
#define INPUT_SW_OUTBALL2 5
#define INPUT_SW_LAUNCHBALL 6 
#define INPUT_SW_SLINGSHOT_LEFT1 7 
#define INPUT_SW_SLINGSHOT_LEFT2 7 
#define INPUT_SW_SLINGSHOT_RIGHT1 8 
#define INPUT_SW_SLINGSHOT_RIGHT2 8 
#define INPUT_SW_OUTLANE_LEFT 9 
#define INPUT_SW_OUTLANE_RIGHT 10 
#define INPUT_SW_RETURNBALL_LEFT 11 
#define INPUT_SW_RETURNBALL_RIGHT 12 
#define INPUT_SW_TARGET_RED1 13 
#define INPUT_SW_TARGET_GREEN1 14 
#define INPUT_SW_TARGET_YELLOW1 15 
#define INPUT_SW_TARGET_RED2 16 
#define INPUT_SW_TARGET_GREEN2 17 
#define INPUT_SW_TARGET_YELLOW2 18
#define INPUT_SW_DROPTARGET_51 19 
#define INPUT_SW_DROPTARGET_52 20 
#define INPUT_SW_DROPTARGET_53 21 
#define INPUT_SW_DROPTARGET_54 22 
#define INPUT_SW_DROPTARGET_55 23 
#define INPUT_SW_DROPTARGET_31 24 
#define INPUT_SW_DROPTARGET_32 25 
#define INPUT_SW_DROPTARGET_33 26
#define INPUT_SW_ROLLOVER_STAR_GREEN 27
#define INPUT_SW_ROLLOVER_STAR_RED1 28
#define INPUT_SW_ROLLOVER_STAR_RED2 29
#define INPUT_SW_ROLLOVER_LEFT 30
#define INPUT_SW_ROLLOVER_CENTER 31
#define INPUT_SW_ROLLOVER_RIGHT 32
#define INPUT_SW_BUMPER_LEFT 33
#define INPUT_SW_BUMPER_CENTER 34
#define INPUT_SW_BUMPER_RIGHT 35
#define INPUT_SW_TARGET_HIGHER 36
#define INPUT_SW_RAMP_IN 37
#define INPUT_SW_RAMP_OUT1 38
#define INPUT_SW_RAMP_OUT2 39
#define INPUT_SW_SPINNER 40
#define INPUT_SW_HOLE 41

#define OUTPUT_

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