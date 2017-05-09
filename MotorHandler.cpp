/*
 * MotorHandler.cpp
 *
 *  Created on: 2017. máj. 8.
 *      Author: Reactorx2
 */

#include "MotorHandler.h"

MotorHandler::MotorHandler(uint8_t threshold) {
	resetPins();
	this->threshold = threshold;
	this->rangeMultiplier = (UINT8_MAX - threshold) / (double) UINT8_MAX;
}

MotorHandler::MotorHandler(uint8_t threshold, uint8_t offsetLeft,
		uint8_t offsetRight) {
	resetPins();
	this->threshold = threshold;
	this->rangeMultiplier = (UINT8_MAX - threshold) / (double) UINT8_MAX;
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

void MotorHandler::setLeftSpeed(int16_t speed) {
	if (speed != 0) {
		speed = speed + offsetLeft;
	}
	setSpeed(speed, PIN_HB_LEFT_ENABLE, PIN_HB_LEFT_FORWARD,
	PIN_HB_LEFT_BACKWARD);
}

void MotorHandler::setRightSpeed(int16_t speed) {
	if (speed != 0) {
		speed = speed + offsetRight;
	}
	setSpeed(speed, PIN_HB_RIGHT_ENABLE, PIN_HB_RIGHT_FORWARD,
	PIN_HB_RIGHT_BACKWARD);
}

void MotorHandler::setSpeed(int16_t speed, uint8_t enablePin,
		uint8_t forwardPin, uint8_t backwardPin) {
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
		analogWrite(enablePin, uspeed);
		digitalWrite(forwardPin, forward ? HIGH : LOW);
		digitalWrite(backwardPin, !forward ? HIGH : LOW);
	} else {
		analogWrite(enablePin, 0);
	}
}

