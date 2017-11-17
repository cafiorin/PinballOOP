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
	virtual bool Loop(int value);
	bool SetCurrentPlayer(int indexPlayer);
	void DisplayScore();
	bool  NotifyEvent(PinballObject *sender, int event, int valueToSend);
	void LostBall();
	static int m_indexPlayerCurrent;

protected:
	int m_nBalls;
	int m_Score;
	bool m_ExtraBall;
	StageBase *m_Stage;
	StatusPlayer m_Status;
	PinballMaster *m_PinballMaster;
};

#endif
