#ifndef ENCODERHANDLER_H_
#define ENCODERHANDLER_H_

#include "Arduino.h"

#include "Configuration.h"
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
	inline void printDistance() {
#if LOG_ENCODER
//		Serial.print("ecl;");
//		Serial.println(getLeftDistance());
//		Serial.print("ecr;");
//		Serial.println(getRightDistance());
		Serial.print("ecd;");
		Serial.println(getDistance());
#endif
	}
};

#endif
