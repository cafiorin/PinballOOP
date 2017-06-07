#ifndef defines_h
#define defines_h

#define DEBUGMESSAGES

#define DOS
//#define ARDUINO

#ifdef ARDUINO
#include "Arduino.h"
#endif //ARDUINO

#ifdef DOS
#include "..\stdafx.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#endif // DOS

#endif