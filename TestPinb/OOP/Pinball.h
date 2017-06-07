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


#ifndef Pinball_h
#define Pinball_h

#include "defines.h"
#include "Vector.h"

class PinballObject;
class HardwareSerial;

class Pinball
{
public:
	Pinball(const char *szName, HardwareSerial *serial, bool master=false);
	char *getName() { return m_szName; }
	bool IsMaster() { return m_master; }
	void LogMessage(const char *szMessage);
	void AddPinballObject(PinballObject *Pinballobj);
	void Init();
	void Loop();

private:
	char m_szName[10];
	bool m_master;
	HardwareSerial *m_serial;
	Vector<PinballObject *> m_PinballObjs;
};

#endif
