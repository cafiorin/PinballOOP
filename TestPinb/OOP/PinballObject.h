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


#ifndef PinballObject_h
#define PinballObject_h

#include "defines.h"

class Pinball;

class PinballObject
{
public:
	PinballObject(const char *szName, Pinball *pinball);
	virtual ~PinballObject();
	char *getName() { return m_szName; }
	bool IsEnabled() { return m_enabled; }
	void LogMessage(const char *szMessage);
	void Debug(const char *szMessage);

//virtual methods	
	virtual bool Init();
	virtual bool Loop();

private:
	char m_szName[10];
	bool m_enabled;
	Pinball *m_pinball;
};

#endif
