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
//#include "LedControl.h"

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

	Multiplex *GetMultiplex() { return m_Multiplex; }
	Input *GetInput(uint8_t channel)
	{
		if(channel < MAX_INPUTCHANNELS) return m_Inputs[channel];
		return NULL;
	}

	Output *GetOutput(uint8_t channel)
	{
		if (channel < MAX_OUTPUTCHANNELS) return m_Outputs[channel];
		return NULL;
	}

	void AddPinballObject(PinballObject *Pinballobj);
	void RemovePinballObject(PinballObject *Pinballobj);
	void AddPinballInput(Input *input);
	void AddPinballOutput(Output *output);

	void clearDisplay(uint8_t line=0);
	void printText(char *text1, char *text2, char font);

	bool NotifyEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);
	bool Init(StatusPinball status);
	bool Loop(uint8_t value);
	void PlaySongToInput(uint8_t portNumber);
	virtual void DataReceived(char c);

	#ifdef ARDUINOLIB
	PinballMaster *m_PinballMaster;
	#endif

	void StartGame(uint8_t Players);

	uint8_t m_nPlayers;
	void ShowChooseNumberOfPlayers();
	uint8_t m_nSecondsTimerToShowPlayers;
	uint8_t m_playerPlaying;
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

	uint8_t GetBallsByPlayer() { return m_nBallByPlayer; }
	void playSongWait(char song[]);

//Events
private :
	void CreateObjects();
	bool EventStartButton(PinballObject *sender);
	bool EventEnterButton(PinballObject *sender);
	bool EventMenuButton(PinballObject *sender);
	bool TimerIsOver(PinballObject *sender);
	bool PlayfieldEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);
	bool EventUpDownButton(PinballObject *sender,bool upButton);
	bool SetupTest(uint8_t event);
	uint8_t  m_nBallByPlayer;
	void SetBallsByPlayer(uint8_t balls) { m_nBallByPlayer = balls; }

protected:
	Multiplex *m_Multiplex;
	Output *m_GI;

	Vector<PinballObject *> m_PinballObjs;
	Input *m_Inputs[MAX_INPUTCHANNELS];
	Output *m_Outputs[MAX_OUTPUTCHANNELS];
	Timer *m_TimerToShowPlayers;

	Menu *m_Menu;
	SelfTest *m_SelfTest;
	OutBall *m_OutBall;
	Output *m_TurnFlipperOn;
	KickoutHole *m_Hole;
	DropTarget *m_DropTarget3;
	DropTarget *m_DropTarget5;
	
	static uint8_t iCountObj;
};

#endif
