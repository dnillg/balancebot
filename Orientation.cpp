#include "Orientation.h"

Orientation::Orientation() {
	this->pitch = 0;
	this->yaw = 0;
	this->roll = 0;
}

int16_t Orientation::getSignedPitch() const {
	if(pitch <= INT16_MAX) {
		return (int16_t) pitch;
	} else {
		return (int16_t) - (UINT16_MAX - pitch);
	}
}

int16_t Orientation::getSignedRoll() const {
	if(roll <= INT16_MAX) {
		return (int16_t) roll;
	} else {
		return (int16_t) - (UINT16_MAX - roll);
	}
}

