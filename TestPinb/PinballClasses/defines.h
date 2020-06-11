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
//#define LCD

// To Show DEBUG messages
//#define DEBUGINPUTS
#define DEBUGMESSAGES
//#define DEBUGMESSAGESLOOP
//#define DEBUGMESSAGESCREATION
//-----------------------

#define DATA_STRIP_LED 5

#define MAX_SIZE_DEBUG_MESSAGE 50
#define LAST_STAGE 5

#define MAX_NAME 15
#define MAX_LEDS 58
#define MAX_BALLS 3
#define MAX_PLAYERS 8
#define MAX_STAGES 1
#define MAX_MULTIPLY 6

#define TIME_COIL_ON 50

//Communication
#define COMM_INIT_THEME 0
#define COMM_TEST_SOUND 1
#define COMM_INIT_THEME_STAGE0 2
#define COMM_INIT_THEME_STAGE1 3
#define COMM_INIT_THEME_STAGE2 4
#define COMM_INIT_THEME_STAGE3 5
#define COMM_INIT_THEME_STAGE4 6
#define COMM_INIT_THEME_STAGE5 7

//Events
#define EVENT_NULL 0
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
#define EVENT_TEST_INPUTS_1BY1 213
#define EVENT_TEST_INPUTS_AUTO 214
#define EVENT_TEST_EXIT_MENU 215
#define EVENT_TEST_FINISH 215

//END - Events

//Inputs
#define INPUT_TEST_INIT 0 //<==Last
#define INPUT_PLAYFIELD_INIT 0
#define INPUT_SW_OUTBALL1 0 //conector 3C - pin 10
#define INPUT_SW_OUTBALL2 1 //conector 3C - pin 9
#define INPUT_SW_LAUNCHBALL 2 //conector 3C - pin 8
#define INPUT_SW_SLINGSHOT_RIGHT1 4 //conector 3C - pin 6 
#define INPUT_SW_SLINGSHOT_RIGHT2 6 //conector 3C - pin 4 
#define INPUT_SW_SLINGSHOT_LEFT1 8 //conector 3C - pin 1 
#define INPUT_SW_SLINGSHOT_LEFT2 7 //conector 3C - pin 2 
#define INPUT_SW_OUTLANE_RIGHT 9 //conector 3C - pin 20 
#define INPUT_SW_OUTLANE_LEFT 5 //conector 3C - pin 5
#define INPUT_SW_RETURNBALL_LEFT 3 //conector 3C - pin 7
#define INPUT_SW_RETURNBALL_RIGHT 10 //conector 3C - pin 19 
#define INPUT_SW_TARGET_RED1 13 //conector 3C - pin 16 
#define INPUT_SW_TARGET_GREEN1 11 //conector 3C - pin 18 
#define INPUT_SW_TARGET_YELLOW1 28 //conector 4D - pin 7 
#define INPUT_SW_TARGET_RED2 18 //conector 4D - pin 12 
#define INPUT_SW_TARGET_YELLOW2 26 //conector 4D - pin 13
#define INPUT_SW_TARGET_GREEN2 25 //conector 4D - pin 1 
#define INPUT_SW_DROPTARGET_51 34 //conector 5E - pin 1
#define INPUT_SW_DROPTARGET_52 37 //conector 5E - pin 2
#define INPUT_SW_DROPTARGET_53 41 //conector 5E - pin 3
#define INPUT_SW_DROPTARGET_54 36 //conector 5E - pin 4
#define INPUT_SW_DROPTARGET_55 33 //conector 5E - pin 11
#define INPUT_SW_DROPTARGET_31 38 //conector 5E - pin 12
#define INPUT_SW_DROPTARGET_32 39 //conector 5E - pin 13 
#define INPUT_SW_DROPTARGET_33 40 //conector 5E - pin 14
#define INPUT_SW_ROLLOVER_STAR_GREEN 30 //conector 4D - pin 16
#define INPUT_SW_ROLLOVER_STAR_RED1 21 //conector 4D - pin 14
#define INPUT_SW_ROLLOVER_STAR_RED2 22 //conector 4D - pin 11
#define INPUT_SW_ROLLOVER_RIGHT 17 //conector 4D - pin 2 
#define INPUT_SW_ROLLOVER_CENTER 20 //conector 4D - pin 4 
#define INPUT_SW_ROLLOVER_LEFT 15 //conector 4D - pin 5 
#define INPUT_SW_BUMPER_LEFT 24 //conector 4D - pin 8 
#define INPUT_SW_BUMPER_CENTER 27 //conector 4D - pin 9 
#define INPUT_SW_BUMPER_RIGHT 14 //conector 4D - pin 10 
#define INPUT_SW_RAMP_IN 42 //conector 5E - pin 15
#define INPUT_SW_RAMP_OUT1 35 //conector 5E - pin 16
#define INPUT_SW_RAMP_OUT2 43 //conector 5E - pin 6
#define INPUT_SW_SPINNER 12 //conector 3C - pin 17 
#define INPUT_SW_HOLE 19 //conector 4D - pin 6 
#define INPUT_SW_ACCBALL1 29 //conector 4D - pin 19
#define INPUT_SW_ACCBALL2 32 //conector 4D - pin 18 
#define INPUT_SW_ACCBALL3 23 //conector 4D - pin 17
#define INPUT_SW_ACCBALL4 31 //conector 4D - pin 15
#define INPUT_SW_ACCJUMP  16 //conector 4D - pin 20
#define INPUT_PLAYFIELD_FINISH 43 //<==Last
#define INPUT_TEST_FINISH 47 //<==Last

//Outputs Low Energy
#define OUTPUT_LOW_INIT 0 //output in 5V
#define OUTPUT_MOTOR_SR 8
#define OUTPUT_LED_RAMP 9
#define OUTPUT_MOTOR_RX 10
#define OUTPUT_LED_BUMPER_LEFT 11
#define OUTPUT_LED_BUMPER_CENTER 12
#define OUTPUT_LED_BUMPER_RIGHT 13
#define OUTPUT_FLIPPER_ON_5V 14
#define OUTPUT_LOW_7 15
#define OUTPUT_SR_HEADLIGHT 0 //output in 12V
#define OUTPUT_RX_HEADLIGHT 1
#define OUTPUT_RAMP_LOCK_ON 2
#define OUTPUT_RAMP_LOCK_OFF 3
#define OUTPUT_LOW_12 4
#define OUTPUT_LOW_13 5
#define OUTPUT_LOW_14 6
#define OUTPUT_LOW_15 7
#define OUTPUT_LOW_FINISH 15

//Outputs high energy
#define OUTPUT_COINS_INIT 0
#define OUTPUT_HOLE_48V 0 //0
#define OUTPUT_OUTBALL2_48V 1
#define OUTPUT_BUMPER_LEFT_48V 2
#define OUTPUT_SLINGSHOTLEFT_48V 3
#define OUTPUT_SLINGSHOTRIGHT_48V 4
#define OUTPUT_ACCBALL_48V 5
#define OUTPUT_BUMPER_RIGHT_48V 6
#define OUTPUT_DROPTARGET3_48V 7
#define OUTPUT_OUTBALL1_48V 8 // 8
#define OUTPUT_DROPTARGET5_48V 9
#define OUTPUT_BUMPER_CENTER_48V 10
#define OUTPUT_RETURNBALL_48V 11
#define OUTPUT_COINS_FINISH 11

//LEDS (STRIP)
#define LED_FIRST 0
#define LED_LAUNCHBALL 0

#define LED_MULTIPLY_2X 1
#define LED_MULTIPLY_3X 2
#define LED_MULTIPLY_4X 3
#define LED_MULTIPLY_5X 4
#define LED_MULTIPLY_6X 5

#define LED_STAGE11 6
#define LED_STAGE12 7
#define LED_STAGE21 8
#define LED_STAGE22 9
#define LED_STAGE31 10
#define LED_STAGE32 11
#define LED_STAGE41 12
#define LED_STAGE42 13
#define LED_STAGE51 14
#define LED_STAGE52 15

#define LED_OUTLANE_LEFT 16
#define LED_OUTLANE_RIGHT 17
#define LED_RETURNBALL_LEFT 18
#define LED_RETURNBALL_RIGHT 19

#define LED_TARGET_RED1 20
#define LED_TARGET_GREEN1 21

#define LED_SPINNER_B1 22
#define LED_SPINNER_B2 23
#define LED_SPINNER_A1 24
#define LED_SPINNER_A2 25

#define LED_RAMP_B1 26
#define LED_RAMP_B2 27
#define LED_RAMP_A1 28
#define LED_RAMP_A2 29

#define LED_DROPTARGET_51 30
#define LED_DROPTARGET_52 31
#define LED_DROPTARGET_53 32
#define LED_DROPTARGET_54 33
#define LED_DROPTARGET_55 34

#define LED_TARGET_GREEN2 35 //LED_DROPTARGET_32
#define LED_TARGET_YELLOW2 36 //LED_DROPTARGET_33
#define LED_TARGET_RED2 37 //LED_DROPTARGET_31

#define LED_LOOP_B1 38
#define LED_LOOP_B2 39
#define LED_LOOP_A1 40
#define LED_LOOP_A2 41

#define LED_HOLE_B1 42
#define LED_HOLE_B2 43
#define LED_HOLE_A1 44
#define LED_HOLE_A2 45

#define LED_TARGET_YELLOW1_B1 46
#define LED_TARGET_YELLOW1_B2 47
#define LED_TARGET_YELLOW1_A1 48
#define LED_TARGET_YELLOW1_A2 49

#define LED_ROLLOVER_LEFT 50
#define LED_ROLLOVER_CENTER 51
#define LED_ROLLOVER_RIGHT 52

#define LED_TARGET_HIGHER_B1 53
#define LED_TARGET_HIGHER_B2 54
#define LED_TARGET_HIGHER_B3 55
#define LED_TARGET_HIGHER_A1 56
#define LED_TARGET_HIGHER_A2 57
#define LED_LAST 57

//POINTS - SCORE
#define SCORE_DEFAULT 1
#define SCORE_ALL_TARGETS 100
#define SCORE_DROPTARGETDOWN 50
#define SCORE_TARGET_STAGE 1000

#ifdef ARDUINOLIB
#include "Arduino.h"
#pragma GCC diagnostic ignored "-Wwrite-strings"
#define DEBOUNCEREAD 5

#define INPUT_MENU_BUTTON A1
#define INPUT_UP_BUTTON A6
#define INPUT_DOWN_BUTTON A7
#define INPUT_ENTER_BUTTON A2

#define INPUT_MENU_BUTTON_DEBUG A8
#define INPUT_UP_BUTTON_DEBUG A9
#define INPUT_DOWN_BUTTON_DEBUG A10
#define INPUT_ENTER_BUTTON_DEBUG A11

#define INPUT_START_BUTTON A0

#define LatchOutputLowSER A4  //=> RCLK
#define LatchOutputLowSRCLK A5 //=>SR_CLK
#define LatchOutputLowRCLK A3 //=>SER

#define LatchOutputHighSER 32 //=> RCLK
#define LatchOutputHighSRCLK 30 //=>SR_CLK
#define LatchOutputHighRCLK 28 //=>SER

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
#define __FlashStringHelper char
#define F (const char *)
#define byte unsigned int
#define LOW 0
#define HIGH 1

#define INPUT_MENU_BUTTON 44
#define INPUT_UP_BUTTON 45
#define INPUT_DOWN_BUTTON 46
#define INPUT_ENTER_BUTTON 47
#define INPUT_START_BUTTON 48

#define INPUT_MENU_BUTTON_DEBUG 49
#define INPUT_UP_BUTTON_DEBUG 50
#define INPUT_DOWN_BUTTON_DEBUG 51
#define INPUT_ENTER_BUTTON_DEBUG 52
#define LatchOutputLowSER 53  //=> RCLK
#define LatchOutputLowSRCLK 54 //=>SR_CLK
#define LatchOutputLowRCLK 55 //=>SER

#define LatchOutputHighSER 56 //=> RCLK
#define LatchOutputHighSRCLK 57 //=>SR_CLK
#define LatchOutputHighRCLK 58 //=>SER


#define A3 100
#define A4 101
#define A5 102
#define A8 103
#define A9 104
#define A10 105
#define A11 106
#define A12 107
#define A13 108
#define A14 109
#define A15 110

#endif // DOS

#endif
