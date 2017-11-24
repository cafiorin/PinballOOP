/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef StageBase__INCLUDED_
#define StageBase__INCLUDED_

#include "defines.h"
#include "pinballobject.h"

class PinballMaster;
class Player;
class SequencerLeds;

class StageBase : public PinballObject
{
public:
	StageBase(PinballMaster *pinball, int number);
	virtual ~StageBase();
	int GetNumber() { return m_number; }
	void SetCurrentPlayer(Player *player);

	virtual void RestartPlayer();
	virtual int PlayfieldEvent(PinballObject *sender, int event, int valueToSend);
	
	void SetMultiply();
	bool CheckRolloversMultiply();
	void TurnOffRolloversMultiply();

protected:
	PinballMaster *m_PinballMaster;
	int m_number;
	Player *m_currentPlayer;
	SequencerLeds *m_LedsLoop;
};

#endif
