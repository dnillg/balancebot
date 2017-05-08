/*
 * EncoderHandler.cpp
 *
 *  Created on: 2017. m�j. 8.
 *      Author: Reactorx2
 */

#include "EncoderHandler.h"

void EncoderHandler::updateLeftWheel(uint8_t a, uint8_t b) {
	leftWheelState.update(a, b);
}

void EncoderHandler::updateRightWheel(uint8_t a, uint8_t b) {
	rightWheelState.update(a, b);
}

int16_t EncoderHandler::getDistance() {
	return (leftWheelState.getTicks() - rightWheelState.getTicks()) / 2;
}