#ifndef MOTORHANDLER_H_
#define MOTORHANDLER_H_

#include "Arduino.h"

#include "BalanceBotPins.h"

class MotorHandler {
private:
	uint8_t threshold;
	double rangeMultiplier;
	uint8_t offsetLeft;
	uint8_t offsetRight;
public:
	MotorHandler(uint8_t threshold);
	MotorHandler(uint8_t threshold, uint8_t offsetLeft, uint8_t offsetRight);
	void setLeftSpeed(int16_t speed);
	void setRightSpeed(int16_t speed);
	void setSpeed(int16_t speed, uint8_t enablePin, uint8_t forwardPin, uint8_t backwardPin);
private:
	void resetPins();
};

#endif
