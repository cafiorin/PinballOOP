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
HardwareSerial::HardwareSerial(uint8_t xlog, uint8_t ylog)
/*---------------------------------------------------------------------*/
{
	m_XInit = xlog;
	m_YInit = ylog;
	uint8_t x = m_XInit;
	uint8_t y = m_YInit;
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
void HardwareSerial::printbox(uint8_t width,uint8_t height,char *szTitle)
/*---------------------------------------------------------------------*/
{
	uint8_t x = m_XInit;
	uint8_t y = m_YInit;
	setcolor(WHITE);
	box(x, y, x + width, y + height + 1, y + 6, y + 6, szTitle);

	m_line=0;
}


/*---------------------------------------------------------------------*/
void HardwareSerial::printone(const char *szLog)
/*---------------------------------------------------------------------*/
{
	uint8_t x = m_XInit;
	uint8_t y = m_YInit;
	setcolor(WHITE);

	m_line++;
	gotoxy(x + 2, y + m_line);
	printf("%-10s", szLog);
}

/*---------------------------------------------------------------------*/
void HardwareSerial::print(const char *szLog)
/*---------------------------------------------------------------------*/
{
	setcolor(WHITE);

	strcat(m_strings[m_line], szLog);
	gotoxy(m_XInit + 2, m_YInit + 1 + m_line);
	printf("%-50s", m_strings[m_line]);
}

/*---------------------------------------------------------------------*/
void HardwareSerial::print(char *szLog)
/*---------------------------------------------------------------------*/
{
	setcolor(WHITE);

	strcat(m_strings[m_line], szLog);
	gotoxy(m_XInit + 2, m_YInit + 1 + m_line);
	printf("%-50s", m_strings[m_line]);
}

/*---------------------------------------------------------------------*/
void HardwareSerial::print(int value)
/*---------------------------------------------------------------------*/
{
	char sz[10];
	sprintf(sz,"%d", value);
	print(sz);
}

/*---------------------------------------------------------------------*/
void HardwareSerial::println(const char *szLog)
/*---------------------------------------------------------------------*/
{
	if (strlen(szLog) == 0)
		return;

	uint8_t x = m_XInit;
	uint8_t y = m_YInit;
	setcolor(WHITE);
	box(x, y, x + 52, y + MAX_STRINGS + 1, y + 6, y + 6, "Logger");

	m_line++;
	if (m_line >= MAX_STRINGS)
	{
		m_line = MAX_STRINGS-1;
		for (uint8_t i = 1; i < MAX_STRINGS; i++)
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
