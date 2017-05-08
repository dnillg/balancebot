#ifndef ORIENTATION_H_
#define ORIENTATION_H_

#include "Arduino.h"
#include <Limits.h>

struct Orientation {
public:
	uint16_t pitch;
	uint16_t yaw;
	uint16_t roll;

	Orientation();
	int16_t getSignedPitch() const;
	int16_t getSignedRoll() const;
};

#endif /* ORIENTATION_H_ */
