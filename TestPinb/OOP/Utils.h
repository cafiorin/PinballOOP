/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef utils__INCLUDED_
#define utils__INCLUDED_


#include "defines.h"

void myStrcpy(char *str1, const char *str2);

#ifdef ARDUINO
long Millis();
#endif

#ifdef DOS
clock_t Millis();
long timediff(clock_t t2, clock_t t1);
#endif
#endif