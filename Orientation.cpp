/*
 * Orientation.cpp
 *
 *  Created on: 2017. máj. 7.
 *      Author: Reactorx2
 */

#include "Orientation.h"

Orientation::Orientation() {
	this->pitch = 0;
	this->yaw = 0;
	this->roll = 0;
}

Orientation::Orientation(uint16_t pitch, uint16_t yawn, uint16_t roll) {
	this->pitch = pitch;
	this->yaw = yawn;
	this->roll = roll;
}

