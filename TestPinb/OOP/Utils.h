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

#ifdef ARDUINOLIB
long Millis();
#endif

#ifdef DOS
#define BLACK	0
#define BLUE	1
#define GREEN	2
#define CYAN	3
#define RED	4
#define MAGENTA	5
#define BROWN	6
#define LIGHTGRAY	7
#define DARKGRAY	8
#define LIGHTBLUE	9
#define LIGHTGREEN	10
#define LIGHTCYAN	11
#define LIGHTRED	12
#define LIGHTMAGENTA	13
#define YELLOW	14
#define WHITE	15

#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1

clock_t Millis();
long timediff(clock_t t2, clock_t t1);
void gotoxy(int x, int y);
void getCursorXY(int &x, int&y);
void setcolor(WORD color);
void clrscr();
void box(unsigned x, unsigned y, unsigned sx, unsigned sy, unsigned char col, unsigned char col2, char text_[]);
void clrbox(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char bkcol);
void putbox(unsigned x, unsigned y, unsigned sx, unsigned sy, unsigned char col, unsigned char col2, unsigned char bkcol, char text_[]);
void txtPlot(unsigned char x, unsigned char y, unsigned char Color);
void delay(unsigned int milliseconds);

void pinMode(int port, int io);
void digitalWrite(int port, int value);
int digitalRead(int port);
#endif

#endif