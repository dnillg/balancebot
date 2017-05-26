#ifndef ORIENTATION_H_
#define ORIENTATION_H_

#include "Arduino.h"
#include <Limits.h>

struct Orientation {
public:
	int16_t pitch;
	uint16_t yaw;
	int16_t roll;

	Orientation();
};

#endif
