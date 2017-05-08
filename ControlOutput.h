#ifndef CONTROLOUTPUT_H_
#define CONTROLOUTPUT_H_

#include "Arduino.h"

struct ControlOutput {
public:
	int16_t left;
	int16_t right;

	ControlOutput(int16_t left, int16_t right);
};

#endif
