/*
 * SerialCommandParser.cpp
 *
 *  Created on: 2017. máj. 14.
 *      Author: Reactorx2
 */

#include "SerialCommandParser.h"

SerialCommandParser::SerialCommandParser(BalanceControl* balanceControl,
		MotorHandler* motorHandler, DisplayHandler* displayHandler) {
	this->balanceControl = balanceControl;
	this->motorHandler = motorHandler;
	this->displayHandler = displayHandler;
}

void SerialCommandParser::handleCommands() {

	while (Serial.available() > 0) {
		char c = Serial.read();
		if (c == '\n') {
			commandBuffer.push_back('\0');
			parseCommand();
			commandBuffer = AvrVector<char>();
		} else {
			commandBuffer.push_back(c);
		}
	}
}

void SerialCommandParser::parseCommand() {
	String command = commandBuffer.getData();
	if (command.startsWith("set_pid")) {
		parseSetPidCommand();
	} else if (command.startsWith("motor_off")) {
		parseMotorOffCommand();
	} else if (command.startsWith("motor_on")) {
		parseMotorOnCommand();
	} else if (command.startsWith("set_motor_min")) {
		parseMotorMinCommand();
	}
}

void SerialCommandParser::parseMotorOnCommand() {
	motorHandler->setEnabled(true);
}

void SerialCommandParser::parseMotorOffCommand() {
	motorHandler->setEnabled(false);
}

void SerialCommandParser::parseSetPidCommand() {
	char* cmd = commandBuffer.getData();
	char* t;
	strtok_r(cmd, ";", &t);
	double p = atof(t);
	strtok_r(0, ";", &t);
	double i = atof(t);
	strtok_r(0, ";", &t);
	double d = atof(t);
	while (strtok_r(0, ";", &t));

	balanceControl->resetPid(p, i, d, balanceControl->getSetPoint());
	displayHandler->printParams(p, i, d);
	motorHandler->setEnabled(true);
}

void SerialCommandParser::parseMotorMinCommand() {
	char* cmd = commandBuffer.getData();
	char* t;
	strtok_r(cmd, ";", &t);
	uint8_t motorMin = atoi(t);
	while (strtok_r(0, ";", &t));
	motorHandler->setThreshold(motorMin);
}
