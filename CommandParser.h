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
	CommandParser(T* serial, BalanceControl* balanceControl, MotorHandler* motorHandler, DisplayHandler* displayHandler);
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

template<class T>
CommandParser<T>::CommandParser(T* serial, BalanceControl* balanceControl, MotorHandler* motorHandler, DisplayHandler* displayHandler) {
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
void CommandParser<T>::parseCommand(char* cmdChr) {
	String command = cmdChr;
	if (command.startsWith("set_tilt_pid_params")) {
		parseSetPidCommand(cmdChr);
	} else if (command.startsWith("motor_off")) {
		parseMotorOffCommand();
	} else if (command.startsWith("motor_on")) {
		parseMotorOnCommand();
	} else if (command.startsWith("get_tilt_pid_params")) {
		parseGetTiltPidCommand();
	} else if (command.startsWith("set_motor_min")) {
			parseSetMotorMinCommand(cmdChr);
	} else if (command.startsWith("get_motor_min")) {
		parseGetMotorMinCommand();
	} else if (command.startsWith("set_setpoints")) {
		parseSetSetPointsCommand(cmdChr);
	} else if (command.startsWith("get_setpoints")) {
		parseGetSetPointsCommand();
	} else if (command.startsWith("set_motor_offsets")) {
		parseSetMotorOffsetsCommand(cmdChr);
	} else if (command.startsWith("get_motor_offsets")) {
		parseGetMotorOffsetsCommand();
	}
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
void CommandParser<T>::parseSetPidCommand(char* cmd) {
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
	motorHandler->setEnabled(true);
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
	dtostrf(balanceControl->getP(), LOG_FLOAT_WIDTH, LOG_FLOAT_PREC, buf);
	serial->print(buf);
	serial->print(";");
	dtostrf(balanceControl->getI(), LOG_FLOAT_WIDTH, LOG_FLOAT_PREC, buf);
	serial->print(buf);
	serial->print(";");
	dtostrf(balanceControl->getD(), LOG_FLOAT_WIDTH, LOG_FLOAT_PREC, buf);
	serial->println(buf);
}

#endif
