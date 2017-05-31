#ifndef SERIALCOMMANDPARSER_H_
#define SERIALCOMMANDPARSER_H_

#include "Arduino.h"
#include "String.h"

#include "Configuration.h"
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
	void parseSetMotorMinCommand();
	void parseGetTiltPidCommand();
	void parseGetMotorMinCommand();
	void parseSetMotorOffsetsCommand();
	void parseSetSetPointsCommand();
	void parseGetSetPointsCommand();
	void parseGetMotorOffsetsCommand();
};

#endif
