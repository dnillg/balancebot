#ifndef COMMANDPARSER_H_
#define COMMANDPARSER_H_

#include "Arduino.h"
#include "String.h"

#include "Configuration.h"
#include "AvrVector.h"
#include "BalanceControl.h"
#include "MotorHandler.h"
#include "DisplayHandler.h"

template<class T>
class CommandParser {
private:
	T* serial;
	AvrVector<char> commandBuffer;
	BalanceControl* balanceControl;
	MotorHandler* motorHandler;
	DisplayHandler* displayHandler;
public:
	CommandParser(T* serial, BalanceControl* balanceControl,
			MotorHandler* motorHandler, DisplayHandler* displayHandler);
	void readNativeSerialCommands();
	void parseCommand(char* command);
private:
	bool isCommandType(const char* cmdChar, const char* refCmdChar,
			bool dataType);
	void parseGetTiltPidCommand();
	void parseSetTiltPidCommand(char* cmd);
	void parseGetDistPidCommand();
	void parseSetDistPidCommand(char* cmd);
	void parseMotorOffCommand();
	void parseMotorOnCommand();
	void parseSetMotorMinCommand(char* cmd);
	void parseGetMotorMinCommand();
	void parseSetMotorOffsetsCommand(char* cmd);
	void parseSetSetPointsCommand(char* cmd);
	void parseGetSetPointsCommand();
	void parseGetMotorOffsetsCommand();
	void parseControlCommand(char* cmdChr);
};

template<class T>
CommandParser<T>::CommandParser(T* serial, BalanceControl* balanceControl,
		MotorHandler* motorHandler, DisplayHandler* displayHandler) {
	this->serial = serial;
	this->balanceControl = balanceControl;
	this->motorHandler = motorHandler;
	this->displayHandler = displayHandler;
}

template<class T>
void CommandParser<T>::readNativeSerialCommands() {
	while (serial->available() > 0) {
		char c = serial->read();
		if (c == '\n') {
			commandBuffer.push_back('\0');
			parseCommand(commandBuffer.getData());
			commandBuffer = AvrVector<char>();
		} else {
			commandBuffer.push_back(c);
		}
	}
}

template<class T>
bool CommandParser<T>::isCommandType(const char* cmdChar,
		const char* refCmdChar, bool dataType) {
	size_t lenpre = strlen(refCmdChar);
	size_t lenstr = strlen(cmdChar);
	if (dataType) {
		return lenstr < (lenpre + 1) ?
				false :
				strncmp(refCmdChar, cmdChar, lenpre) == 0
						&& cmdChar[lenpre] == ';';
	} else {
		return lenstr < lenpre ?
		false :
									strncmp(refCmdChar, cmdChar, lenpre) == 0;
	}
}

template<class T>
void CommandParser<T>::parseCommand(char* cmdChr) {
	if (isCommandType(cmdChr, "c", true)) {
		parseControlCommand(cmdChr);
	} else if (isCommandType(cmdChr, "set_tilt_pid_params", true)) {
		parseSetTiltPidCommand(cmdChr);
	} else if (isCommandType(cmdChr, "get_tilt_pid_params", false)) {
		parseGetTiltPidCommand();
	} else if (isCommandType(cmdChr, "set_dist_pid_params", true)) {
		parseSetDistPidCommand(cmdChr);
	} else if (isCommandType(cmdChr, "get_dist_pid_params", false)) {
		parseGetDistPidCommand();
	} else if (isCommandType(cmdChr, "motor_off", false)) {
		parseMotorOffCommand();
	} else if (isCommandType(cmdChr, "motor_on", false)) {
		parseMotorOnCommand();
	} else if (isCommandType(cmdChr, "set_motor_min", true)) {
		parseSetMotorMinCommand(cmdChr);
	} else if (isCommandType(cmdChr, "get_motor_min", false)) {
		parseGetMotorMinCommand();
	} else if (isCommandType(cmdChr, "set_setpoints", true)) {
		parseSetSetPointsCommand(cmdChr);
	} else if (isCommandType(cmdChr, "get_setpoints", false)) {
		parseGetSetPointsCommand();
	} else if (isCommandType(cmdChr, "set_motor_offsets", true)) {
		parseSetMotorOffsetsCommand(cmdChr);
	} else if (isCommandType(cmdChr, "get_motor_offsets", false)) {
		parseGetMotorOffsetsCommand();
	} else {

	}
}

template<class T>
void CommandParser<T>::parseControlCommand(char* cmd) {
	char* t;
	ControlState controlState;
	strtok_r(cmd, ";", &t);
	controlState.speed = atoi(t);
	strtok_r(0, ";", &t);
	controlState.rotation = atoi(t);
	strtok_r(0, ";", &t);
	balanceControl->setControlState(controlState);
}

template<class T>
void CommandParser<T>::parseSetMotorOffsetsCommand(char* cmd) {
	char* t;
	strtok_r(cmd, ";", &t);
	uint8_t offsetLeft = atoi(t);
	strtok_r(0, ";", &t);
	uint8_t offsetRight = atoi(t);
	strtok_r(0, ";", &t);
	motorHandler->setOffsetLeft(offsetLeft);
	motorHandler->setOffsetRight(offsetRight);
}

template<class T>
void CommandParser<T>::parseSetSetPointsCommand(char* cmd) {
	char* t;
	strtok_r(cmd, ";", &t);
	int16_t balance = atoi(t);
	strtok_r(0, ";", &t);
	int16_t direction = atoi(t);
	strtok_r(0, ";", &t);
	balanceControl->setBalanceSetPoint(balance);
	balanceControl->setDirectionSetPoint(direction);
}

template<class T>
void CommandParser<T>::parseGetSetPointsCommand() {
	serial->print("setpoints;");
	serial->print(balanceControl->getBalanceSetPoint());
	serial->print(";");
	serial->println(balanceControl->getDirectionSetPoint());
}

template<class T>
void CommandParser<T>::parseGetMotorOffsetsCommand() {
	serial->print("motor_offsets;");
	serial->print(motorHandler->getOffsetLeft());
	serial->print(";");
	serial->println(motorHandler->getOffsetRight());
}

template<class T>
void CommandParser<T>::parseMotorOnCommand() {
	motorHandler->setEnabled(true);
}

template<class T>
void CommandParser<T>::parseMotorOffCommand() {
	motorHandler->setEnabled(false);
}

template<class T>
void CommandParser<T>::parseSetTiltPidCommand(char* cmd) {
	char* t;
	strtok_r(cmd, ";", &t);
	double p = atof(t);
	strtok_r(0, ";", &t);
	double i = atof(t);
	strtok_r(0, ";", &t);
	double d = atof(t);
	strtok_r(0, ";", &t);

	balanceControl->resetTiltPid(p, i, d);
	displayHandler->printParams(p, i, d);
}

template<class T>
void CommandParser<T>::parseSetDistPidCommand(char* cmd) {
	char* t;
	strtok_r(cmd, ";", &t);
	double p = atof(t);
	strtok_r(0, ";", &t);
	double i = atof(t);
	strtok_r(0, ";", &t);
	double d = atof(t);
	strtok_r(0, ";", &t);

	balanceControl->resetDistPid(p, i, d);
}

template<class T>
void CommandParser<T>::parseSetMotorMinCommand(char* cmd) {
	char* t;
	strtok_r(cmd, ";", &t);
	uint8_t motorMin = atoi(t);
	strtok_r(0, ";", &t);
	motorHandler->setThreshold(motorMin);
}

template<class T>
void CommandParser<T>::parseGetMotorMinCommand() {
	serial->print("motor_min;");
	serial->println(motorHandler->getThreshold());
}

template<class T>
void CommandParser<T>::parseGetTiltPidCommand() {
	serial->print("tilt_pid_params;");
	char buf[LOG_FLOAT_BUF_SIZE];
	dtostrf(balanceControl->getTiltP(), LOG_FLOAT_WIDTH, LOG_FLOAT_PREC, buf);
	serial->print(buf);
	serial->print(";");
	dtostrf(balanceControl->getTiltI(), LOG_FLOAT_WIDTH, LOG_FLOAT_PREC, buf);
	serial->print(buf);
	serial->print(";");
	dtostrf(balanceControl->getTiltD(), LOG_FLOAT_WIDTH, LOG_FLOAT_PREC, buf);
	serial->println(buf);
}

template<class T>
void CommandParser<T>::parseGetDistPidCommand() {
	serial->print("dist_pid_params;");
	char buf[LOG_FLOAT_BUF_SIZE];
	dtostrf(balanceControl->getDistP(), LOG_FLOAT_WIDTH, LOG_FLOAT_PREC, buf);
	serial->print(buf);
	serial->print(";");
	dtostrf(balanceControl->getDistI(), LOG_FLOAT_WIDTH, LOG_FLOAT_PREC, buf);
	serial->print(buf);
	serial->print(";");
	dtostrf(balanceControl->getDistD(), LOG_FLOAT_WIDTH, LOG_FLOAT_PREC, buf);
	serial->println(buf);
}

#endif
