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
	void readNativeSerialCommands();
	void parseCommand(char* command);
private:
	void parseSetPidCommand(char* cmd);
	void parseMotorOffCommand();
	void parseMotorOnCommand();
	void parseSetMotorMinCommand(char* cmd);
	void parseGetTiltPidCommand();
	void parseGetMotorMinCommand();
	void parseSetMotorOffsetsCommand(char* cmd);
	void parseSetSetPointsCommand(char* cmd);
	void parseGetSetPointsCommand();
	void parseGetMotorOffsetsCommand();
};

#endif
