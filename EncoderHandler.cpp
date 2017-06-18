#include "EncoderHandler.h"

void EncoderHandler::updateLeftWheel(uint8_t a, uint8_t b) {
	leftWheelState.update(a, b);
}

void EncoderHandler::updateRightWheel(uint8_t a, uint8_t b) {
	rightWheelState.update(a, b);
}

const int32_t& EncoderHandler::getDistance() {
	return distance;
}

const int16_t& EncoderHandler::getSpeed() {
	return speed;
}

void EncoderHandler::reset() {
	leftWheelState.reset();
	rightWheelState.reset();
	distance = 0;
	rotation = 0;
}

void EncoderHandler::calculateSpeed() {
	speed = tmpSpeed;
	tmpSpeed = 0;
}

void EncoderHandler::handleTicks() {
	int8_t leftTicks = leftWheelState.getTicks();
	int8_t rightTicks = rightWheelState.getTicks();
	int16_t deltaDistance = leftTicks + rightTicks;
	distance += deltaDistance;
	tmpSpeed += deltaDistance;
	rotation += leftTicks - rightTicks;
	leftWheelState.reset();
	rightWheelState.reset();
}
