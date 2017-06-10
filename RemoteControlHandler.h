#ifndef REMOTECONTROLHANDLER_H_
#define REMOTECONTROLHANDLER_H_

#include "Arduino.h"
#include "SoftwareSerial.h"

#include "Configuration.h"
#include "AvrVector.h"
#include "SerialCommandParser.h"

class RemoteControlHandler {
private:
	AvrVector<char> commandBuffer;
	SoftwareSerial softSerial = SoftwareSerial(PIN_HC_06_RX, PIN_HC_06_TX);
	SerialCommandParser* serialCommandParser;
public:
	RemoteControlHandler(SerialCommandParser* serialCommandParser);
	void readCommands();

};

#endif
