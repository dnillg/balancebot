#ifndef SERIALCOMMANDPARSER_H_
#define SERIALCOMMANDPARSER_H_

#include "Arduino.h"
#include "String.h"

#include "AvrVector.h"
#include "BalanceControl.h"
#include "MotorHandler.h"
#include "DisplayHandler.h"

class SerialCommandParser {
private:
	AvrVector<char> commandBuffer;
	BalanceControl* balanceControl;
	MotorHandler* motorHandler;
	DisplayHandler* displayHandler;
public:
	SerialCommandParser(BalanceControl* balanceControl, MotorHandler* motorHandler, DisplayHandler* displayHandler);
	void handleCommands();
private:
	void resetPid(char* params);
	void parseCommand();
	void parseSetPidCommand();
	void parseMotorOffCommand();
	void parseMotorOnCommand();
	void parseMotorMinCommand();
};

#endif
