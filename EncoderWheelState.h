#ifndef ENCODERWHEELSTATE_H_
#define ENCODERWHEELSTATE_H_

#include "Arduino.h"

class EncoderWheelState {
private:
	int32_t ticks;
	uint8_t lastA;
public:
	EncoderWheelState();
	int32_t getTicks();
	void update(uint8_t a, uint8_t b);
};

#endif
