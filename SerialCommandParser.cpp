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
	if (command.startsWith("set_tilt_pid_params")) {
		parseSetPidCommand();
	} else if (command.startsWith("motor_off")) {
		parseMotorOffCommand();
	} else if (command.startsWith("motor_on")) {
		parseMotorOnCommand();
	} else if (command.startsWith("set_motor_min")) {
		parseSetMotorMinCommand();
	} else if (command.startsWith("get_tilt_pid_params")) {
		parseGetTiltPidCommand();
	} else if (command.startsWith("get_motor_min")) {
		parseGetMotorMinCommand();
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

void SerialCommandParser::parseSetMotorMinCommand() {
	char* cmd = commandBuffer.getData();
	char* t;
	strtok_r(cmd, ";", &t);
	uint8_t motorMin = atoi(t);
	while (strtok_r(0, ";", &t));
	motorHandler->setThreshold(motorMin);
}

void SerialCommandParser::parseGetMotorMinCommand() {
	Serial.print("motor_min;");
	Serial.println(motorHandler->getThreshold());
}

void SerialCommandParser::parseGetTiltPidCommand() {
	Serial.print("tilt_pid_params;");
	char buf[LOG_FLOAT_BUF_SIZE];
	dtostrf(balanceControl->getP(), LOG_FLOAT_WIDTH, LOG_FLOAT_PREC, buf);
	Serial.print(buf);
	Serial.print(";");
	dtostrf(balanceControl->getI(), LOG_FLOAT_WIDTH, LOG_FLOAT_PREC, buf);
	Serial.print(buf);
	Serial.print(";");
	dtostrf(balanceControl->getD(), LOG_FLOAT_WIDTH, LOG_FLOAT_PREC, buf);
	Serial.println(buf);
}
