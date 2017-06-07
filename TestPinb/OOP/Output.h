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

#if !defined(EA_A5DC726B_BD74_4c6c_8409_19F521E789F5__INCLUDED_)
#define EA_A5DC726B_BD74_4c6c_8409_19F521E789F5__INCLUDED_

#include "defines.h"
#include "Port.h"

class Output : public Port
{
public:
	Output(Pinball *pinball, const char *szName, int portNumber);
	virtual ~Output();
	bool IsTurnOn(){return m_turnOn;}
	void TurnOn();
	void TurnOff();


protected:
	virtual bool Init();
	bool m_turnOn;
};
#endif // !defined(EA_A5DC726B_BD74_4c6c_8409_19F521E789F5__INCLUDED_)
