/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Utils.h"

#pragma execution_character_set("utf-8") 

byte ToByte(bool b[8])
{
	byte c = 0;
	for (int i = 0; i < 8; ++i)
		if (b[i])
			c |= 1 << i;
	return c;
}


void myStrcpy(char *str1, const char *str2)
{
	uint8_t bufsize = sizeof(str1);
	uint8_t len = (int) strlen(str2);
	if (len < bufsize)
	{
		strcpy(str1, str2);
	}
	else
	{
		strncpy(str1, str2, bufsize);
		str1[bufsize - 1] = 0;
	}

}

#ifdef ARDUINOLIB
unsigned long Millis()
{
	return millis();
}

#endif

#ifdef DOS

void pinMode(uint8_t port, uint8_t io) {}
void digitalWrite(uint8_t port, uint8_t value) {}
uint8_t digitalRead(uint8_t port) { return LOW; }

clock_t Millis()
{
	return clock();
}

long timediff(clock_t t2, clock_t t1) 
{
	long elapsed;
	elapsed = (long) ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
	return elapsed;
}

void gotoxy(uint8_t x, uint8_t y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void getCursorXY(uint8_t &x, uint8_t &y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	{
		x = csbi.dwCursorPosition.X;
		y = csbi.dwCursorPosition.Y;
	}
}

void setcolor(WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return;
}

void clrscr()
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
	return;
}

void box(unsigned x, unsigned y, unsigned sx, unsigned sy, unsigned char col, unsigned char col2, char text_[])
{
	unsigned i, j, m;
	{

		m = (sx - x);                       //differential
		j = m / 8;                          //adjust
		j = j - 1;                          //more adjustment
		gotoxy(x, y); cprintf("*"); //   ┌       //Top left corner of box
		gotoxy(sx, y); cprintf("*"); //  ┐       //Top right corner of box
		gotoxy(x, sy); cprintf("*"); //  └       //Bottom left corner of box
		gotoxy(sx, sy); cprintf("*"); // ┘       //Bottom right corner of box

		for (i = x + 1; i<sx; i++)
		{
			gotoxy(i, y); cprintf("-");     // Top horizontol line
			gotoxy(i, sy); cprintf("-");    // Bottom Horizontal line
		}

		for (i = y + 1; i<sy; i++)
		{
			gotoxy(x, i); cprintf("|");     //Left Vertical line
			gotoxy(sx, i); cprintf("|");    //Right Vertical Line
		}

		gotoxy(x + j, y); cprintf(text_); //put Title
		gotoxy(1, 24);
	}
}

void clrbox(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char bkcol)
{
	uint8_t x, y;
	setcolor(bkcol);                       //Set to color bkcol

	for (y = y1; y<y2; y++)                    //Fill Y Region Loop
	{
		for (x = x1; x<x2; x++)               //Fill X region Loop
		{
			gotoxy(x, y); cprintf(" ");       //Draw Solid space
		}
	}
}

void putbox(unsigned x, unsigned y, unsigned sx, unsigned sy,unsigned char col, unsigned char col2, unsigned char bkcol, char text_[])
{
	clrbox(x, y, sx, sy, bkcol);
	box(x, y, sx, sy, col, col2, text_);
}

void txtPlot(unsigned char x, unsigned char y, unsigned char Color)
{
	setcolor(Color);
	gotoxy(x, y); cprintf(".");
}

void delay(long milliseconds)
{
	clock_t ticks1, ticks2;
	long tic1 = 0, tic2 = 0, tick = 0;

	ticks1 = clock();
	while (tick<milliseconds)
	{
		ticks2 = clock();
		tic1 = ticks2 / CLOCKS_PER_SEC - ticks1;
		tic2 = ticks1 / CLOCKS_PER_SEC;
		tick = ticks2 - ticks1;
	}
	ticks2 = clock();
}

#endif

