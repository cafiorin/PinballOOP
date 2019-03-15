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
class InputArduino;

class PinballMaster : public Pinball
{
public:
#ifdef ARDUINOLIB
	PinballMaster();
	void Setup(SFEMP3Shield *MP3player, HardwareSerial *serial);
#endif

#ifdef DOS
	PinballMaster(HardwareSerial *serial);
#endif

	virtual ~PinballMaster();
	void InitVars();

	void clearDisplay(uint8_t line=0);
	void printText(char *text1, char *text2, char font);

	bool NotifyEvent(Object *sender, uint8_t event, uint8_t value);
	bool Init(StatusPinball status);
	bool Loop(uint8_t value);
	void PlaySongToInput(uint8_t portNumber);
	virtual void DataReceived(char c);

	void StartGame(uint8_t Players);

	uint8_t m_nPlayers;
	void ShowChooseNumberOfPlayers();
	uint8_t m_nSecondsTimerToShowPlayers;
	uint8_t m_playerPlaying;
	void GetNewBall();
	void PlayerLostBall();
	void NextPlayer();

	Menu *GetMenu() { return m_Menu; }
	OutBall *GetOutBall() { return m_OutBall; }
	Output *GetTurnFlipperOn() { return m_TurnFlipperOn; }
	KickoutHole *GetKickoutHole() { return m_Hole; }
	DropTarget *GetDropTarget3() { return m_DropTarget3; }
	DropTarget *GetDropTarget5() { return m_DropTarget5; }

	uint8_t GetBallsByPlayer() { return m_nBallByPlayer; }
	
	InputArduino *m_StartButton; 
	InputArduino *m_MenuButton; 
	InputArduino *m_UpButton; 
	InputArduino *m_DownButton; 
	InputArduino *m_EnterButton;

//Events
private :
	uint8_t  m_nBallByPlayer;

	void SetBallsByPlayer(uint8_t balls) { m_nBallByPlayer = balls; }
	void CreateObjects();
	bool EventStartButton(Object *sender);
	bool EventEnterButton(Object *sender);
	bool EventMenuButton(Object *sender);
	bool TimerIsOver(Object *sender);
	bool PlayfieldEvent(Object *sender, uint8_t event, uint8_t value);
	bool EventUpDownButton(Object *sender,bool upButton);
	bool SetupTest(uint8_t event);

protected:
	Timer *m_TimerToShowPlayers;

	Menu *m_Menu;
	OutBall *m_OutBall;
	Output *m_TurnFlipperOn;
	KickoutHole *m_Hole;
	DropTarget *m_DropTarget3;
	DropTarget *m_DropTarget5;
	
	Output *m_MotorSR;
	Output *m_MotorRX;
	Output *m_LedRamp;
	Output *m_HEADLIGHT_SR;
	Output *m_HEADLIGHT_RX;
	Output *m_LockRampOn;
	Output *m_LockRampOff;

	static uint8_t iCountObj;
};

#endif
