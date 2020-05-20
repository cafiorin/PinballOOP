#ifndef PinballMachine__INCLUDED_
#define PinballMachine__INCLUDED_

#include "Observer.h"

enum StatusPinballMachine
{
	initializing,
	menusetup,
	menutest,
	attractmode,
	getplayers,
	playingmode,
	waitingmessages
};


class MultiplexInputs;
class LatchOutputs;
class Door;
class Playfield;
class LedControl;
class HardwareSerial;
class Menu;
class NewTimer;

class PinballMachine : public Observer
{
public :
	PinballMachine(HardwareSerial* serial);
	virtual ~PinballMachine();

	void playSong(char song[], bool priority = true);
	void ChangeVolume(bool plus, byte delta = 5);
	void PlaySongToInput(byte);
	void clearDisplay(byte = 0);
	void printText(char*, char*, char);

	void EnableSFX(bool enable) { m_enableSfx = enable; }
	bool IsEnabledSFX() { return m_enableSfx; }
	bool IsPlaying() { return m_Status == StatusPinballMachine::playingmode; }

	LedControl* GetLedControl() { return m_LedControl; }
	MultiplexInputs* GetMuxInputs() { return m_muxInputs; }
	LatchOutputs* GetOutputsLowVoltage() { return m_LatchOutputLowVoltage; }
	LatchOutputs* GetOutputsHighVoltage() { return m_LatchOutputHighVoltage; }
	Door* GetDoor() { return m_Door; }

protected:
	void onNotifySubject(EventType event, byte value);
	void ButtonPressed(byte value);

private :
	void CreateObjects();
	MultiplexInputs* m_muxInputs;
	LatchOutputs* m_LatchOutputLowVoltage;
	LatchOutputs* m_LatchOutputHighVoltage;
	LedControl* m_LedControl;
	HardwareSerial* m_Serial;
	Menu* m_Menu;

	Playfield* m_Playfield;
	Door* m_Door;

	void InitVars();
	StatusPinballMachine m_Status;
	byte m_nBallByPlayer = MAX_BALLS;
	bool m_enableSfx = true;
	void SetBallsByPlayer(byte balls) { m_nBallByPlayer = balls; }
	NewTimer* m_TimerToShowPlayers;
	byte m_nPlayers;
	void ShowChooseNumberOfPlayers();
	byte m_nSecondsTimerToShowPlayers;
	byte m_playerPlaying;
	void TimerIsOver();
	void StartGame(byte Players);

	void EventStartButton();
	void EventMenuButton();
	void EventEnterButton();
	void EventUpDownButton(bool upButton);
	void SetupTest(byte event);


public:
	void Initialize();
	void Loop();

	//Display
	//Som
	
	//Display debug e buttons debug
	//Serial output debug

	//PinballGame
	//Players


};

#endif
