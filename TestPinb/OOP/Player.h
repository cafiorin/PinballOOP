#ifndef Player__INCLUDED_
#define Player__INCLUDED_

#include "defines.h"
#include "StageBase.h"

enum StatusPlayer 
{
	playing,
	waiting,
	gameover
};

class Player
{
public:
	Player();
	virtual ~Player();
	void Init(StageBase *stage);

protected:
	int m_nBalls;
	int m_Score;
	bool m_ExtraBall;
	StageBase *m_Stage;
	StatusPlayer m_Status;
};

#endif
