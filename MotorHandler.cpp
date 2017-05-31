#include "MotorHandler.h"

MotorHandler::MotorHandler(uint8_t threshold, uint8_t offsetLeft,
		uint8_t offsetRight) {
	resetPins();
	this->enabled = true;
	this->threshold = threshold;
	this->rangeMultiplier = ((double) (UINT8_MAX - threshold)) / UINT8_MAX;
	this->offsetLeft = offsetLeft;
	this->offsetRight = offsetRight;
}

void MotorHandler::resetPins() {
	digitalWrite(PIN_HB_LEFT_FORWARD, LOW);
	digitalWrite(PIN_HB_LEFT_BACKWARD, LOW);
	digitalWrite(PIN_HB_RIGHT_BACKWARD, LOW);
	digitalWrite(PIN_HB_RIGHT_FORWARD, LOW);
	digitalWrite(PIN_HB_LEFT_ENABLE, LOW);
	digitalWrite(PIN_HB_RIGHT_ENABLE, LOW);
}

uint8_t MotorHandler::getOffsetLeft() const {
	return offsetLeft;
}

uint8_t MotorHandler::getOffsetRight() const {
	return offsetRight;
}

int16_t MotorHandler::getSpeedWithOffset(int16_t speed, uint8_t offset) {
	if (speed > 0) {
		speed = speed + offset;
	} else if (speed < 0) {
		speed = speed - offset;
	}
	return speed;
}

void MotorHandler::setLeftSpeed(int16_t speed) {
	speed = getSpeedWithOffset(speed, offsetLeft);
	setSpeed(speed, PIN_HB_LEFT_ENABLE, PIN_HB_LEFT_FORWARD,
	PIN_HB_LEFT_BACKWARD);
}

void MotorHandler::setRightSpeed(int16_t speed) {
	if (speed > 0) {
		speed = speed + offsetRight;
	} else if (speed < 0) {
		speed = speed - offsetRight;
	}
	setSpeed(speed, PIN_HB_RIGHT_ENABLE, PIN_HB_RIGHT_FORWARD,
	PIN_HB_RIGHT_BACKWARD);
}

void MotorHandler::setSpeed(int16_t speed, uint8_t enablePin,
		uint8_t forwardPin, uint8_t backwardPin) {
	if (!enabled) {
		speed = 0;
	}

	if (speed > UINT8_MAX) {
		speed = UINT8_MAX;
	} else if (speed < -UINT8_MAX) {
		speed = -UINT8_MAX;
	}

	bool forward = speed >= 0;
	uint8_t uspeed = forward ? (uint8_t) speed : (uint8_t) (-1 * speed);

	digitalWrite(forwardPin, LOW);
	digitalWrite(backwardPin, LOW);

	if (uspeed != 0) {
		uspeed = threshold + (uint8_t) (uspeed * rangeMultiplier);
		digitalWrite(forwardPin, forward ? HIGH : LOW);
		digitalWrite(backwardPin, !forward ? HIGH : LOW);
		analogWrite(enablePin, uspeed);
	} else {
		analogWrite(enablePin, 0);
		digitalWrite(forwardPin, LOW);
		digitalWrite(backwardPin, LOW);
	}
}

void MotorHandler::setEnabled(bool enabled) {
	this->enabled = enabled;
	if (!enabled) {
		setLeftSpeed(0);
		setRightSpeed(0);
	}
}

void MotorHandler::setThreshold(uint8_t threshold) {
	this->threshold = threshold;
}

uint8_t MotorHandler::getThreshold() {
	return threshold;
}

void MotorHandler::setOffsetLeft(uint8_t offset) {
	offsetLeft = offset;
}

void MotorHandler::setOffsetRight(uint8_t offset) {
	offsetRight = offset;
}
