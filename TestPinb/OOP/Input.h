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

#if !defined(EA_493584A8_374D_4c41_813B_7DEB885806F1__INCLUDED_)
#define EA_493584A8_374D_4c41_813B_7DEB885806F1__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Port.h"

class Input : public Port
{

public:
	Input(Pinball *pinball, const char *szName, int portNumber);
	virtual ~Input();
	bool CheckPort();
	bool CheckEdgePositive();
	void SetDebounceDelay(long debounce){m_debounceDelay = debounce;}

protected:
	virtual bool Init();

private:
	bool m_lastState;
	long m_lastDebounceTime;  // the last time the output pin was toggled
	long m_debounceDelay;    // the debounce time; increase if the output flickers
	bool m_startReading;

};
#endif // !defined(EA_493584A8_374D_4c41_813B_7DEB885806F1__INCLUDED_)
