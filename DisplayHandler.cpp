#include "DisplayHandler.h"

DisplayHandler::DisplayHandler(BalanceControl* balanceControl,
		FrequencyRegulator* frequencyRegulator) {
	this->balanceControl = balanceControl;
	this->frequencyRegulator = frequencyRegulator;
	initLcd();
	printName();
}

void DisplayHandler::initLcd() {
	lcd = new LiquidCrystal_I2C(I2C_ADDR_DISP_16_2, 2, 1, 0, 4, 5, 6, 7, 3,
			POSITIVE);
	lcd->begin(16, 2);
	lcd->setBacklight(200);
	uint8_t backslash[8] = { 0b00000, 0b10000, 0b01000, 0b00100, 0b00010,
			0b00001, 0b00000, 0b00000 };
	lcd->createChar(0, backslash);
}

void DisplayHandler::printName() {
	lcd->setCursor(9, 1);
	lcd->print("Cyclops");
}

void DisplayHandler::printFrequency(const uint8_t& frq) {
	char lineBuf[8];
	sprintf(lineBuf, "%dHz ", frq);
	lcd->setCursor(0, 1);
	lcd->print(lineBuf);
}

void DisplayHandler::printParams(const double& p, const double& i, const double& d) {
	char lineBuf[17];
	StringUtils::initDisplayBuffer(lineBuf, 17);
	StringUtils::printDouble(lineBuf, p, 1, 2);
	StringUtils::printDouble(lineBuf + 5, i, 1, 3);
	StringUtils::printDouble(lineBuf + 11, d, 1, 3);
	lcd->setCursor(0, 0);
	lcd->print(lineBuf);
}

void DisplayHandler::printStatusChar() {
	lcd->setCursor(7, 2);
	lcd->print(statusChars[statusCharIndex++]);
	if(statusCharIndex == 8) {
		statusCharIndex = 0;
	}
}

const char DisplayHandler::statusChars[8] = {0, '|', '/', '-', 0, '|', '/', '-'};
