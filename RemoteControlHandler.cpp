#include "RemoteControlHandler.h"

RemoteControlHandler::RemoteControlHandler(SerialCommandParser* serialCommandParser) {
	softSerial.begin(HC_06_DEFAULT_BAUDRATE);
	this->serialCommandParser = serialCommandParser;
}

void RemoteControlHandler::readCommands() {
	while (softSerial.available()) {
		char c = Serial.read();
		if (c == '\n') {
			commandBuffer.push_back('\0');
			serialCommandParser->parseCommand(commandBuffer.getData());
			commandBuffer = AvrVector<char>();
		} else {
			commandBuffer.push_back(c);
		}
	}
}
