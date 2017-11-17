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
	
	Menu *m_Menu;
	SelfTest *m_SelfTest;

	Multiplex *m_Multiplex;
	LedControl *m_LedControl;
	LedControl *GetLedControl() {return m_LedControl;}
	void clearDisplay(int line);
	void printText(char *text1, char *text2, char font);

	virtual bool NotifyEvent(PinballObject *sender, int event, int valueToSend);
	virtual bool Init();
	virtual bool Loop(int value);
	virtual void DataReceived(char c);

	#ifdef ARDUINOLIB
	PinballMaster *m_PinballMaster;
	#endif

	void StartGame(int Players);

	int m_nPlayers;
	void ShowChooseNumberOfPlayers();
	Timer *m_TimerToShowPlayers;
	int m_nSecondsTimerToShowPlayers;
	Player *m_Players[MAX_PLAYERS];
	int m_playerPlaying;

	void CreateStages();
	int m_TotalStages;
	StageBase *m_Stages[MAX_STAGES];
	StageBase *GetStage(int number) { return m_Stages[number]; }

//Events
private :
	void CreateObjects();
	bool EventStartButton(PinballObject *sender);
	bool EventMenuButton(PinballObject *sender);
	bool TimerIsOver(PinballObject *sender);
	bool PlayfieldEvent(PinballObject *sender, int event, int valueToSend);
	bool EventUpDownButton(PinballObject *sender,bool upButton);
	bool SetupTest(int event);
};

#endif
