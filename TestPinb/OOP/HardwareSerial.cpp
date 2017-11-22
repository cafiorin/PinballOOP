/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "HardwareSerial.h"

#ifdef DOS

#include "Utils.h"

/*---------------------------------------------------------------------*/
HardwareSerial::HardwareSerial(int xlog, int ylog)
/*---------------------------------------------------------------------*/
{
	m_XInit = xlog;
	m_YInit = ylog;
	int x = m_XInit;
	int y = m_YInit;
	setcolor(WHITE);
	clrbox(x, y, x + 52, y + MAX_STRINGS + 1, BLACK);
	m_line = -1;
}

/*---------------------------------------------------------------------*/
HardwareSerial::~HardwareSerial()
/*---------------------------------------------------------------------*/
{
}

/*---------------------------------------------------------------------*/
void HardwareSerial::printbox(int width,int height,char *szTitle)
/*---------------------------------------------------------------------*/
{
	int x = m_XInit;
	int y = m_YInit;
	setcolor(WHITE);
	box(x, y, x + width, y + height + 1, y + 6, y + 6, szTitle);

	m_line=0;
}


/*---------------------------------------------------------------------*/
void HardwareSerial::printone(const char *szLog)
/*---------------------------------------------------------------------*/
{
	int x = m_XInit;
	int y = m_YInit;
	setcolor(WHITE);

	m_line++;
	gotoxy(x + 2, y + m_line);
	printf("%-10s", szLog);
}


/*---------------------------------------------------------------------*/
void HardwareSerial::println(const char *szLog)
/*---------------------------------------------------------------------*/
{
	int x = m_XInit;
	int y = m_YInit;
	setcolor(WHITE);
	box(x, y, x + 52, y + MAX_STRINGS + 1, y + 6, y + 6, "Logger");

	m_line++;
	if (m_line >= MAX_STRINGS)
	{
		m_line = MAX_STRINGS-1;
		for (int i = 1; i < MAX_STRINGS; i++)
		{
			strcpy(m_strings[i-1], m_strings[i]);
			gotoxy(x + 2, y + 1 + i-1);
			printf("%-50s",m_strings[i-1]);
		}
	}

	strcpy(m_strings[m_line], szLog);
	gotoxy(x + 2, y + 1 + m_line);
	printf("%-50s",m_strings[m_line]);
}

/*---------------------------------------------------------------------*/
void HardwareSerial::jumpline()
/*---------------------------------------------------------------------*/
{
	m_line++;
	if (m_line >= MAX_STRINGS)
	{
		m_line = MAX_STRINGS - 1;
	}
}


#endif
