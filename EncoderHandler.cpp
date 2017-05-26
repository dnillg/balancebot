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

int16_t EncoderHandler::getLeftDistance() {
	return leftWheelState.getTicks();
}

int16_t EncoderHandler::getRightDistance() {
	return -rightWheelState.getTicks();
}

void EncoderHandler::reset() {
	leftWheelState = EncoderWheelState();
	rightWheelState = EncoderWheelState();
}
