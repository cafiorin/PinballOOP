/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef Player__INCLUDED_
#define Player__INCLUDED_

#include "defines.h"
#include "StageBase.h"
#include "PinballObject.h"

enum StatusPlayer 
{
	playing,
	waiting,
	gameover
};

class PinballMaster;

class Player : public PinballObject
{
public:
	Player(PinballMaster *pinball);
	virtual ~Player();
	virtual bool Init(StatusPinball status);

	static uint8_t m_indexPlayerCurrent;

	bool SetCurrentPlayer(uint8_t indexPlayer);
	void DisplayScore();
	bool  NotifyEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);
	void LostBall();

	bool SetNextMultiply();
	uint8_t GetMultiply() { return m_Multiply; }

	bool SetExtraBall();
	bool GetExtraBall() { return m_ExtraBall; }
	void SetNextStage();

	StatusPlayer GetStatus(){ return m_Status; }

protected:
	uint8_t m_nBalls;
	uint8_t m_Score;
	uint8_t m_Multiply;
	bool m_ExtraBall;
	StageBase *m_Stage;
	StatusPlayer m_Status;
};

#endif
