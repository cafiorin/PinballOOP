/*
*      This program is free software; you can redistribute it and/or modify
*      it under the terms of the GNU General Public License as published by
*      the Free Software Foundation; either version 2 of the License, or
*      (at your option) any later version.
*
*      This program is distributed in the hope that it will be useful,
*      but WITHOUT ANY WARRANTY; without even the implied warranty of
*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*      GNU General Public License for more details.
*
*      You should have received a copy of the GNU General Public License
*      along with this program; if not, write to the Free Software
*      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
*      MA 02110-1301, USA.
*/

/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "Utils.h"

void myStrcpy(char *str1, const char *str2)
{
	int bufsize = sizeof(str1);
	int len = (int) strlen(str2);
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

long Millis()
{
	#ifdef ARDUINO
	return millis();
	#endif
	
	#ifdef DOS
	return (long) time(NULL);
	#endif

}