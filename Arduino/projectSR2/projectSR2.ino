#include <Arduino.h>
#include <avr/pgmspace.h>
//#include <ht1632pinball.h>
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>
#include <PinballSlave.h>
#include <ctype.h>
#include <Wire.h>

#define ADDRESS_MASTER 4

SdFat sd;
SdFile myFile;
SFEMP3Shield MP3player;
PinballSlave m_pinball;

void setup()  
{
	Serial.begin(115200);
	Serial.print(F("Iniciando 2...")); 

	SetupWire();

	//SdCard.
	if (!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
	if (!sd.chdir("/")) sd.errorHalt("sd.chdir");
	
	//Mp3
	uint8_t result = MP3player.begin();
	if (result != 0)
	{
 		Serial.print(F("Error code: "));
		Serial.print(result);
		Serial.println(F(" when trying to start MP3 player"));
 	}
    
	//Pinball    
    m_pinball.Setup(&MP3player, &Serial);

    Serial.println(F("init ok"));
}

void loop()
{
  // Below is only needed if not interrupt driven. Safe to remove if not using.
	#if defined(USE_MP3_REFILL_MEANS) \
		&& ( (USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer) \
		||   (USE_MP3_REFILL_MEANS == USE_MP3_Polled)      )

		  Serial.println(F("teste loop"));
		  MP3player.available();
	#endif
  
  m_pinball.Loop(0);
}

void SetupWire()
{
	Wire.begin(ADDRESS_MASTER); // join I2C bus using this address
	Wire.onReceive(receiveMessage); // register event to handle requests
}

void receiveMessage(int howMany)
{
	m_pinball.receiveMessageFromAnotherArduino(howMany);
}
