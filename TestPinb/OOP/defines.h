/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef defines_h
#define defines_h

//-----------------------
#define DOS
//#define ARDUINOLIB

// To DEBUGMESSAGES
#define DEBUGMESSAGES
//#define DEBUGMESSAGESLOOP
//#define DEBUGMESSAGESCREATION
//-----------------------

#define ADDRESS_MASTER 4
#define ADDRESS_SLAVE  5
#define INIT_THEME 0
#define DATA_STRIP_LED 5

#define MAX_SIZE_DEBUG_MESSAGE 120
#define MAX_NAME 25
#define MAX_LEDS 66
#define MAX_BALLS 3
#define MAX_PLAYERS 8
#define MAX_STAGES 1
#define MAX_MULTIPLY 6

#define TIME_COIL_ON 20

//Events
#define EVENT_EDGEPOSITIVE 1
#define EVENT_EDGENEGATIVE 2
#define EVENT_DROPTARGETDOWN 3
#define EVENT_TIMEISOVER 4
#define EVENT_LOST_BALL 5

#define EVENT_TEST_INIT 201
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
#define EVENT_TEST_OUTPUTS_1BY1 211 
#define EVENT_TEST_OUTPUTS_AUTO 212 
#define EVENT_TEST_EXIT_MENU 213
#define EVENT_TEST_FINISH 213

//END - Events

//Inputs
#define INPUT_MENU_BUTTON 0
#define INPUT_UP_BUTTON 1
#define INPUT_DOWN_BUTTON 2
#define INPUT_START_BUTTON 3

#define INPUT_PLAYFIELD_INIT 4
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
#define INPUT_SW_ROLLOVER_STAR_RED1 30
#define INPUT_SW_ROLLOVER_STAR_RED2 31
#define INPUT_SW_ROLLOVER_LEFT 32
#define INPUT_SW_ROLLOVER_CENTER 33
#define INPUT_SW_ROLLOVER_RIGHT 34
#define INPUT_SW_BUMPER_LEFT 35
#define INPUT_SW_BUMPER_CENTER 36
#define INPUT_SW_BUMPER_RIGHT 37
#define INPUT_SW_TARGET_HIGHER 38
#define INPUT_SW_RAMP_IN 39
#define INPUT_SW_RAMP_OUT1 40
#define INPUT_SW_RAMP_OUT2 41
#define INPUT_SW_SPINNER 42
#define INPUT_SW_HOLE 43
#define INPUT_SW_ACCBALL1 44
#define INPUT_SW_ACCBALL2 45
#define INPUT_SW_ACCBALL3 46
#define INPUT_SW_ACCBALL4 47
#define INPUT_PLAYFIELD_FINISH 47 //<==Last

//Outputs Low Energy
#define OUTPUT_LOW_INIT 0
#define OUTPUT_FLIPPER_ON_5V 0
#define OUTPUT_LOW_1 1
#define OUTPUT_LOW_2 2
#define OUTPUT_LOW_3 3
#define OUTPUT_LOW_4 4
#define OUTPUT_LOW_5 5
#define OUTPUT_LOW_6 6
#define OUTPUT_LOW_7 7
#define OUTPUT_LOW_8 8 //12V
#define OUTPUT_LOW_9 9
#define OUTPUT_LOW_10 10
#define OUTPUT_LOW_11 11
#define OUTPUT_LOW_12 12
#define OUTPUT_LOW_13 13
#define OUTPUT_LOW_14 14
#define OUTPUT_LOW_15 15
#define OUTPUT_LOW_FINISH 15

//Outputs high energy
#define OUTPUT_COINS_INIT 16
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
#define OUTPUT_COINS_FINISH 27

//LEDS
#define LED_MULTIPLY_2X 27
#define LED_MULTIPLY_3X 28
#define LED_MULTIPLY_4X 29
#define LED_MULTIPLY_5X 30
#define LED_MULTIPLY_6X 31
#define LED_ROLLOVER_CENTER 32
#define LED_ROLLOVER_LEFT 33
#define LED_ROLLOVER_RIGHT 34
#define LED_STAGE11 35
#define LED_STAGE12 36
#define LED_STAGE21 37
#define LED_STAGE22 38
#define LED_STAGE31 39
#define LED_STAGE32 40
#define LED_STAGE41 41
#define LED_STAGE42 42
#define LED_STAGE51 43
#define LED_STAGE52 44

#define LED_HOLE_CIRCLE1 45
#define LED_HOLE_CIRCLE2 46
#define LED_HOLE_ARROW11 47
#define LED_HOLE_ARROW12 48

//POINTS - SCORE
#define SCORE_DEFAULT 1
#define SCORE_ALL_TARGETS 100
#define SCORE_DROPTARGETDOWN 50
#define SCORE_TARGET_STAGE 1000

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
