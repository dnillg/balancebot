#ifndef FREQUENCYREGULATOR_H_
#define FREQUENCYREGULATOR_H_

#include <Math.h>
#include "Arduino.h"

#include "Configuration.h"

class FrequencyRegulator {
private:
	uint8_t frq;
	uint8_t millisPerTick;
	unsigned long lastMillis = 0;

	uint8_t lastEffectiveFrq = 0;
	uint8_t currentEffectiveFrq = 0;
	unsigned long lastEffectiveCalcMillis = 0;
public:
	FrequencyRegulator(uint8_t frq);
	void waitTick();
	uint8_t getEffectiveFrequency();
	void addTimedJob(uint8_t periodMillis, void (*userFunc)(void));
	inline void printEffectiveFrequency() {
#if LOG_EFF_FRQ
		Serial.print("frq;");
		Serial.println(lastEffectiveFrq);
#endif
	}
private:
	void calculateEffectiveFrq(unsigned long nextTickMillis);
	void setFrequency(uint8_t frq);
};

#endif
