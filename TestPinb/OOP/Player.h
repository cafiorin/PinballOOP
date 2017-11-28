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
	virtual bool Init();

	static int m_indexPlayerCurrent;

	bool SetCurrentPlayer(int indexPlayer);
	void DisplayScore();
	bool  NotifyEvent(PinballObject *sender, int event, int valueToSend);
	void LostBall();

	bool SetNextMultiply();
	int GetMultiply() { return m_Multiply; }

	bool SetExtraBall();
	bool GetExtraBall() { return m_ExtraBall; }

	void SetNextStage();

	StatusPlayer GetStatus(){ return m_Status; }

protected:
	int m_nBalls;
	int m_Score;
	int m_Multiply;
	bool m_ExtraBall;
	StageBase *m_Stage;
	StatusPlayer m_Status;
};

#endif
