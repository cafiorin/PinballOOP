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

//#define DEBUGMESSAGES
//#define DEBUGMESSAGESLOOP

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

#define EVENT_TEST_INIT 200
#define EVENT_TEST_LED_1BY1 201
#define EVENT_TEST_LED_AUTO 202
#define EVENT_TEST_COIN_1BY1 203
#define EVENT_TEST_COIN_AUTO 204
#define EVENT_TEST_SOUND_BOARD1 205
#define EVENT_TEST_SOUND_BOARD2 206
#define EVENT_TEST_SFX_ONOFF 207
#define EVENT_TEST_NBALLS3 208
#define EVENT_TEST_NBALLS4 209
#define EVENT_TEST_NBALLS5 210
#define EVENT_TEST_FINISH 211

//END - Events

//Inputs
#define INPUT_START_BUTTON 0
#define INPUT_MENU_BUTTON 1
#define INPUT_UP_BUTTON 2
#define INPUT_DOWN_BUTTON 3

#define INPUT_SW_OUTBALL1 4  
#define INPUT_SW_OUTBALL2 5
#define INPUT_SW_LAUNCHBALL 6 
#define INPUT_SW_SLINGSHOT_LEFT1 7 
#define INPUT_SW_SLINGSHOT_LEFT2 8 
#define INPUT_SW_SLINGSHOT_RIGHT1 9 
#define INPUT_SW_SLINGSHOT_RIGHT2 10 
#define INPUT_SW_OUTLANE_LEFT 11 
#define INPUT_SW_OUTLANE_RIGHT 12 
#define INPUT_SW_RETURNBALL_LEFT 13 
#define INPUT_SW_RETURNBALL_RIGHT 14 
#define INPUT_SW_TARGET_RED1 15 
#define INPUT_SW_TARGET_GREEN1 16 
#define INPUT_SW_TARGET_YELLOW1 17 
#define INPUT_SW_TARGET_RED2 18 
#define INPUT_SW_TARGET_GREEN2 19 
#define INPUT_SW_TARGET_YELLOW2 20
#define INPUT_SW_DROPTARGET_51 21 
#define INPUT_SW_DROPTARGET_52 22 
#define INPUT_SW_DROPTARGET_53 23 
#define INPUT_SW_DROPTARGET_54 24 
#define INPUT_SW_DROPTARGET_55 25 
#define INPUT_SW_DROPTARGET_31 26 
#define INPUT_SW_DROPTARGET_32 27 
#define INPUT_SW_DROPTARGET_33 28
#define INPUT_SW_ROLLOVER_STAR_GREEN 29
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
#define INPUT_SW_ACCBALL1 42
#define INPUT_SW_ACCBALL2 43
#define INPUT_SW_ACCBALL3 44
#define INPUT_SW_ACCBALL4 45

//Outputs high energy
#define OUTPUT_OUTBALL1_48V 16
#define OUTPUT_OUTBALL2_48V 17
#define OUTPUT_BUMPER_LEFT_48V 18
#define OUTPUT_BUMPER_CENTER_48V 19
#define OUTPUT_BUMPER_RIGHT_48V 20
#define OUTPUT_SLINGSHOTLEFT_48V 21
#define OUTPUT_SLINGSHOTRIGHT_48V 22
#define OUTPUT_HOLE_48V 23
#define OUTPUT_DROPTARGET3_48V 24
#define OUTPUT_DROPTARGET5_48V 25
#define OUTPUT_RETURNBALL_48V 26
#define OUTPUT_ACCBALL_48V 27

//Outputs Low Energy
#define OUTPUT_FLIPPER_ON_5V 0

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