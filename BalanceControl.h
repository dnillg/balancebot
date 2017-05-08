#ifndef BALANCECONTROL_H_
#define BALANCECONTROL_H_

#include <PID_v1.h>

#include "OrientationHandler.h"
#include "EncoderHandler.h"
#include "ControlOutput.h"

class BalanceControl {
private:
	double const TILT_PID_AMP = 2;
	double const TILT_PID_P = 0.4 * TILT_PID_AMP;
	double const TILT_PID_I = 10 * TILT_PID_AMP;
	double const TILT_PID_D = -0.3 * TILT_PID_AMP;

	OrientationHandler* orientationHandler;
	EncoderHandler* encoderHandler;
	double tiltPidInput = 0;
	double tiltPidOutput = -1;
	double tiltPidSetPoint = 60;
	PID* tiltPid;
public:
	BalanceControl(OrientationHandler* orientationHandler, EncoderHandler* encoderHandler);
	ControlOutput getControlValue();
};

#endif
