/*
 * MotorHandler.cpp
 *
 *  Created on: 2017. máj. 8.
 *      Author: Reactorx2
 */

#include "MotorHandler.h"

MotorHandler::MotorHandler(uint8_t threshold) {
	this->threshold = threshold;

	digitalWrite(PIN_HB_LEFT_FORWARD, LOW);
	digitalWrite(PIN_HB_LEFT_BACKWARD, LOW);
	digitalWrite(PIN_HB_RIGHT_BACKWARD, LOW);
	digitalWrite(PIN_HB_RIGHT_FORWARD, LOW);
	digitalWrite(PIN_HB_LEFT_ENABLE, LOW);
	digitalWrite(PIN_HB_RIGHT_ENABLE, LOW);
}

void MotorHandler::setLeftSpeed(int16_t speed) {
	setSpeed(speed, PIN_HB_LEFT_ENABLE, PIN_HB_LEFT_FORWARD,
	PIN_HB_LEFT_BACKWARD);
}

void MotorHandler::setRightSpeed(int16_t speed) {
	setSpeed(speed, PIN_HB_RIGHT_ENABLE, PIN_HB_RIGHT_FORWARD,
	PIN_HB_RIGHT_BACKWARD);
}

void MotorHandler::setSpeed(int16_t speed, uint8_t enablePin,
		uint8_t forwardPin, uint8_t backwardPin) {
	bool forward = speed >= 0;
	uint8_t uspeed = forward ? (uint8_t) speed : (uint8_t) (-1 * speed);

	digitalWrite(forwardPin, LOW);
	digitalWrite(backwardPin, LOW);

	if (uspeed >= threshold) {
		digitalWrite(forwardPin, forward ? HIGH : LOW);
		digitalWrite(backwardPin, !forward ? HIGH : LOW);
		analogWrite(enablePin, uspeed);
	}
}

