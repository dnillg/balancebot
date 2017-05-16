#ifndef DISPLAYHANDLER_H_
#define DISPLAYHANDLER_H_

#include "Arduino.h"
#include "new_liquid_crystal/LiquidCrystal_I2C.h"

#include "Configuration.h"
#include "FrequencyRegulator.h"
#include "BalanceControl.h"
#include "StringUtils.h"

class DisplayHandler {
private:
	static const char statusChars[8];
	uint8_t statusCharIndex = 0;
	BalanceControl* balanceControl;
	FrequencyRegulator* frequencyRegulator;
	LiquidCrystal_I2C* lcd;

	void initLcd();

public:
	DisplayHandler(BalanceControl* balanceControl, FrequencyRegulator* frequencyRegulator);
	void printFrequency(const uint8_t& frq);
	void printName();
	void printParams(const double& p, const double& i, const double& d);
	void printStatusChar();
};

#endif
