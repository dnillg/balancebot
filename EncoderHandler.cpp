#include "EncoderHandler.h"

EncoderHandler::EncoderHandler(OrientationHandler* orientationHandler) {
	this->orientationHandler = orientationHandler;
}

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
	speed = tmpSpeedTicks;
	tmpSpeedTicks = 0;
	printDistance();
}

void EncoderHandler::handleTicks() {
//	Orientation orientation = orientationHandler->getOrientation();
//	int16_t deltaRollTicks = (int16_t)(OrientationHandler::toDegree((double)orientation.roll - lastRollValue) / 360.0) * ENCODER_ROUND_TICKS * 2;
//	lastRollValue = orientation.roll;
	int8_t leftTicks = leftWheelState.getTicks();
	int8_t rightTicks = rightWheelState.getTicks();
	int16_t deltaDistance = leftTicks + rightTicks;
	distance += deltaDistance;
	tmpSpeedTicks += deltaDistance;
	rotation += leftTicks - rightTicks;
	leftWheelState.reset();
	rightWheelState.reset();
}
