#ifndef PinballMachine__INCLUDED_
#define PinballMachine__INCLUDED_

#include "Observer.h"
#include "StatusPinballMachine.h"

#ifdef ARDUINOLIB
#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal_I2C.h>
#endif

class MultiplexInputs;
class LatchOutputs;
class Door;
class Playfield;
class LedControl;
class HardwareSerial;
class Menu;
class NewTimer;
class Logger;

class PinballMachine : public Observer
{
public :
	PinballMachine();
	virtual ~PinballMachine();
	void Initialize();
	void Loop();

	#ifdef ARDUINOLIB
	void Setup(DFRobotDFPlayerMini* DFPlayerMain, DFRobotDFPlayerMini* DFPlayerSFX, HardwareSerial* serial, LiquidCrystal_I2C* lcd);
	#endif // ARDUINOLIB
	
	#ifdef DOS
	void Setup(HardwareSerial* serial);
	#endif

	static void playSong(int number, bool SFX=false);
	static void ChangeVolume(bool plus);
	static void PlaySongToInput(byte);
	static void clearDisplay(byte = 0);
	static void printText(char*, char*, char);

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
	Logger* m_Logger;

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
	void ChangeStatus(StatusPinballMachine status);

#ifdef ARDUINOLIB
	static DFRobotDFPlayerMini* m_playerMain;
	static DFRobotDFPlayerMini* m_playerSFX;
	static LiquidCrystal_I2C* m_lcd;
#endif // ARDUINOLIB


	//TODO: PinballGame
	//TODO: Players
};

#endif
