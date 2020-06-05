
#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
#include <PinballMachine.h>
#include <LiquidCrystal_I2C.h>

DFRobotDFPlayerMini DFPlayerMain;
DFRobotDFPlayerMini DFPlayerSFX;
LiquidCrystal_I2C lcd(0x27,16,2);  

PinballMachine m_pinball;


void setup()  
{
	Serial.begin(115200);
	Serial.println(F(" -< R E S E T >- "));
	Serial.println(F("########################")); 
	Serial.println(F("Iniciando...")); 
	Serial.println(F("########################")); 

	//Init external objects
	Serial1.begin(9600);
	Serial2.begin(9600);
    
	if (!DFPlayerMain.begin(Serial1)) 
	{  
		Serial.println(F("DFPlayerMain: Unable to begin:"));
		Serial.println(F("1.Please recheck the connection!"));
		Serial.println(F("2.Please insert the SD card!"));
	}
	
	if (!DFPlayerSFX.begin(Serial2)) 
	{  
		Serial.println(F("DFPlayerSFX: Unable to begin:"));
		Serial.println(F("1.Please recheck the connection!"));
		Serial.println(F("2.Please insert the SD card!"));
	}

	lcd.init();                      
	lcd.backlight();
	
	//Pinball    
    m_pinball.Setup(&DFPlayerMain, &DFPlayerSFX , &Serial, &lcd);
    Serial.println(F("End setup"));
}

void loop()
{
  m_pinball.Loop();
}
