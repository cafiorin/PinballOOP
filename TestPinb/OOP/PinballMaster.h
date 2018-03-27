/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PinballMaster__INCLUDED_
#define PinballMaster__INCLUDED_

#ifdef ARDUINOLIB
#include <SFEMP3Shield.h>
#include <Wire.h>
#endif // ARDUINOLIB

#include "defines.h"
#include "Vector.h"
#include "Pinball.h"
#include "LedControl.h"

class PinballObject;
class HardwareSerial;
class Menu;
class Multiplex;
class Timer;
class SelfTest;
class StageBase;
class Player;
class OutBall;
class Output;
class KickoutHole;
class DropTarget;

class PinballMaster : public Pinball
{
public:
#ifdef ARDUINOLIB
	PinballMaster();
	void Setup(SFEMP3Shield *MP3player, HardwareSerial *serial);
#endif

#ifdef DOS
	PinballMaster(const char *szName, HardwareSerial *serial);
#endif

	virtual ~PinballMaster();
	
	LedControl *GetLedControl() {return m_LedControl;}
	Multiplex *GetMultiplex() { return m_Multiplex; }
	Input *GetInput(int channel) 
	{ 
		if(channel < MAX_INPUTCHANNELS) return m_Inputs[channel]; 
		return NULL;
	}

	Output *GetOutput(int channel) 
	{ 
		if (channel < MAX_OUTPUTCHANNELS) return m_Outputs[channel];
		return NULL;
	}

	void AddPinballObject(PinballObject *Pinballobj);
	void RemovePinballObject(PinballObject *Pinballobj);
	void AddPinballInput(Input *input);
	void AddPinballOutput(Output *output);

	void clearDisplay(int line=0);
	void printText(char *text1, char *text2, char font);

	bool NotifyEvent(PinballObject *sender, int event, int valueToSend);
	bool Init(StatusPinball status);
	bool Loop(int value);
	void PlaySongToInput(int portNumber);
	virtual void DataReceived(char c);

	#ifdef ARDUINOLIB
	PinballMaster *m_PinballMaster;
	#endif

	void StartGame(int Players);

	int m_nPlayers;
	void ShowChooseNumberOfPlayers();
	int m_nSecondsTimerToShowPlayers;
	int m_playerPlaying;
	void GetNewBall();
	void PlayerLostBall();
	void NextPlayer();
	bool IsPlaying() { return m_Status == StatusPinball::playingmode; }
	void CreateStages();

	Menu *GetMenu() { return m_Menu; }
	SelfTest *GetSelfTest() { return m_SelfTest; }
	OutBall *GetOutBall() { return m_OutBall; }
	Output *GetTurnFlipperOn() { return m_TurnFlipperOn; }
	KickoutHole *GetKickoutHole() { return m_Hole; }
	DropTarget *GetDropTarget3() { return m_DropTarget3; }
	DropTarget *GetDropTarget5() { return m_DropTarget5; }

	StageBase *GetStage(int number) 
	{ 
		if (number < MAX_STAGES) return m_Stages[number];
		return NULL;
	}
	int GetBallsByPlayer() { return m_nBallByPlayer; }
	void playSongWait(char song[]);

//Events
private :
	void CreateObjects();
	bool EventStartButton(PinballObject *sender);
	bool EventEnterButton(PinballObject *sender);
	bool EventMenuButton(PinballObject *sender);
	bool TimerIsOver(PinballObject *sender);
	bool PlayfieldEvent(PinballObject *sender, int event, int valueToSend);
	bool EventUpDownButton(PinballObject *sender,bool upButton);
	bool SetupTest(int event);
	int m_nBallByPlayer;
	void SetBallsByPlayer(int balls) { m_nBallByPlayer = balls; }

protected:
	Multiplex *m_Multiplex;
	LedControl *m_LedControl;
	Output *m_GI;

	Vector<PinballObject *> m_PinballObjs;
	Input *m_Inputs[MAX_INPUTCHANNELS];
	Output *m_Outputs[MAX_OUTPUTCHANNELS];
	StageBase *m_Stages[MAX_STAGES];
	Player *m_Players[MAX_PLAYERS];
	Timer *m_TimerToShowPlayers;

	Menu *m_Menu;
	SelfTest *m_SelfTest;
	OutBall *m_OutBall;
	Output *m_TurnFlipperOn;
	KickoutHole *m_Hole;
	DropTarget *m_DropTarget3;
	DropTarget *m_DropTarget5;


	static int iCountObj;
};

#endif
