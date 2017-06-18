#ifndef CONTROLSTATE_H_
#define CONTROLSTATE_H_

#include "Arduino.h"

struct ControlState {
	int8_t speed = 0; //NEG: BACKWARD; POS: FORWARD
	int8_t rotation = 0; //NEG: LEFT; POS: RIGHT
};

#endif
