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

//Inputs
#define I1 1
#define I2 2
#define I3 3
#define I3ALT 39
#define I4 4
#define I4ALT 38
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

//OutPut COIN
#define O0 13
#define O1 1
#define O2 2
#define O3 3
#define O4 4
#define O5 5
#define O6 6
#define O7 7
#define O8 8
#define O9 9
#define O10 10
#define O11 11
#define O12 12




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