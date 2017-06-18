#ifndef ENCODERSTATE_H_
#define ENCODERSTATE_H_

#include "Arduino.h"

class EncoderState {
private:
	int8_t ticks;
	uint8_t lastA;
	bool inverted;
public:
	EncoderState(bool inverted);
	int16_t getTicks();
	void update(uint8_t a, uint8_t b);
	void reset();
};

#endif
