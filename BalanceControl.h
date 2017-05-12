#ifndef BALANCECONTROL_H_
#define BALANCECONTROL_H_

#include <PID_v1.h>

#include "OrientationHandler.h"
#include "EncoderHandler.h"
#include "ControlOutput.h"

class BalanceControl {
private:
	double const TILT_PID_AMP = 1;
	double const TILT_PID_P = 0.7025 * TILT_PID_AMP;
	double const TILT_PID_I = 0.0*TILT_PID_P*2 * TILT_PID_AMP;
	double const TILT_PID_D = TILT_PID_P/12 * TILT_PID_AMP;

	OrientationHandler* orientationHandler;
	EncoderHandler* encoderHandler;
	double tiltPidInput = 0;
	double tiltPidOutput = -1;
	double tiltPidSetPoint = 0;
	PID* tiltPid;

	long lastMillis = -1;
public:
	BalanceControl(OrientationHandler* orientationHandler, EncoderHandler* encoderHandler);
	ControlOutput getControlValue();
	void resetPid(double p, double i, double d);
};

#endif
