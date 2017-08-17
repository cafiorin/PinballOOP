/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "PinballSlave.h"
#include "PinballObject.h"
#include "Pinball.h"
#include "HardwareSerial.h"
#include "Vector.h"
#include "Utils.h"

#include "Input.h"

PinballSlave *m_PinballSlave = NULL;


/*---------------------------------------------------------------------*/
#ifdef ARDUINO
PinballSlave::PinballSlave(const char *szName, SFEMP3Shield *MP3player, HardwareSerial *serial, bool master = false) : Pinball(szName, serial, true)
#endif

#ifdef DOS
PinballSlave::PinballSlave(const char *szName, HardwareSerial *serial) : Pinball(szName, serial, true)
#endif
/*---------------------------------------------------------------------*/
{
#ifdef DEBUGMESSAGES
	LogMessage("PinballSlave Constructor");
#endif

	m_PinballSlave = this;

	Input *pInputDropTarget31 = new Input("DT31", this, I17);
	Input *pInputDropTarget32 = new Input("DT32", this, I18);
	Input *pInputDropTarget33 = new Input("DT33", this, I19);

	Input *pInputRampIn = new Input("RampIn", this, I34);
	Input *pInputRampOut1 = new Input("RampO1", this, I35);
	Input *pInputRampOut2 = new Input("RampO2", this, I36);

	Input *pInputStartButton = new Input("SB", this, I38);
	Input *pInputMenu = new Input("BM", this, I39);
	Input *pInputVolumePlus = new Input("VP", this, I40);
	Input *pInputVolumeMinus = new Input("VM", this, I41);

}

/*---------------------------------------------------------------------*/
PinballSlave::~PinballSlave()
/*---------------------------------------------------------------------*/
{
#ifdef DEBUGMESSAGES
	LogMessage("PinballSlave Destructor");
#endif
}

