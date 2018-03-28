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
	StageBase(PinballMaster *pinball, uint8_t number);
	virtual ~StageBase();
	uint8_t GetNumber() { return m_number; }
	void SetCurrentPlayer(Player *player);

	virtual void RestartPlayer();
	virtual uint8_t PlayfieldEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);
	
	void SetMultiply();
	bool CheckRolloversMultiply();
	void TurnOffRolloversMultiply();
	void SetLedStage();


protected:
	PinballMaster *m_PinballMaster;
	uint8_t m_number;
	Player *m_currentPlayer;
	SequencerLeds *m_LedsLoop;
};

#endif
