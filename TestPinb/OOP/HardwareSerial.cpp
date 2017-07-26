/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "HardwareSerial.h"
#include "Utils.h"

/*---------------------------------------------------------------------*/
HardwareSerial::HardwareSerial(int xlog)
/*---------------------------------------------------------------------*/
{
	m_XInit = xlog;
	int x = m_XInit;
	int y = 1;
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
void HardwareSerial::println(const char *szLog)
/*---------------------------------------------------------------------*/
{
	int x = m_XInit;
	int y = 1;
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
