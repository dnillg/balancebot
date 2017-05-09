#ifndef ENCODERHANDLER_H_
#define ENCODERHANDLER_H_

#include "Arduino.h"

#include "EncoderWheelState.h"

class EncoderHandler {

private:
	EncoderWheelState leftWheelState;
	EncoderWheelState rightWheelState;

public:
	void updateLeftWheel(uint8_t a, uint8_t b);
	void updateRightWheel(uint8_t a, uint8_t b);
	int16_t getDistance();
	int16_t getLeftDistance();
	int16_t getRightDistance();
	void reset();
};

#endif
