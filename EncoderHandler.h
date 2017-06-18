#ifndef ENCODERHANDLER_H_
#define ENCODERHANDLER_H_

#include "Arduino.h"

#include "Configuration.h"
#include "EncoderState.h"
#include "Logging.h"

class EncoderHandler {

private:
	EncoderState leftWheelState = EncoderState(false);
	EncoderState rightWheelState = EncoderState(true);
	int32_t distance = 0;
	int32_t rotation = 0; // +: left, -:right
	int16_t tmpSpeed = 0;
	int16_t speed = 0;
public:
	void updateLeftWheel(uint8_t a, uint8_t b);
	void updateRightWheel(uint8_t a, uint8_t b);
	const int32_t& getDistance();
	void reset();
	void handleTicks();
	void calculateSpeed();
	const int16_t& getSpeed();

	inline void printDistance() {
#if LOG_DISTANCE
		LOGGER.print("ecd;");
		LOGGER.println(getDistance());
#endif
	}
};

#endif
