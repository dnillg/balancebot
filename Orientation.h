#ifndef ORIENTATION_H_
#define ORIENTATION_H_

#include "Arduino.h"

struct Orientation {
public:
	uint16_t pitch;
	uint16_t yaw;
	uint16_t roll;

	Orientation();
	Orientation(uint16_t pitch, uint16_t yawn, uint16_t roll);
};

#endif /* ORIENTATION_H_ */
