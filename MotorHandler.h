#ifndef MOTORHANDLER_H_
#define MOTORHANDLER_H_

#include "Arduino.h"

#include "Configuration.h"

class MotorHandler {
private:
	uint8_t threshold;
	double rangeMultiplier;
	uint8_t offsetLeft;
	uint8_t offsetRight;
	bool enabled;
public:
	MotorHandler(uint8_t threshold);
	MotorHandler(uint8_t threshold, uint8_t offsetLeft, uint8_t offsetRight);
	void setLeftSpeed(int16_t speed);
	void setRightSpeed(int16_t speed);
	void setSpeed(int16_t speed, uint8_t enablePin, uint8_t forwardPin, uint8_t backwardPin);
	void setEnabled(bool enabled);
	void setThreshold(uint8_t);
	uint8_t getThreshold();
	void setOffsetLeft(uint8_t offset);
	void setOffsetRight(uint8_t offset);
	uint8_t getOffsetLeft() const;
	uint8_t getOffsetRight() const;
private:
	void resetPins();
	inline int16_t getSpeedWithOffset(int16_t speed, uint8_t offset);
};

#endif
