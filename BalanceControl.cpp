/*
 * BalanceControl.cpp
 *
 *  Created on: 2017. máj. 8.
 *      Author: Reactorx2
 */

#include "BalanceControl.h"

BalanceControl::BalanceControl(OrientationHandler* orientationHandler,
		EncoderHandler* encoderHandler) {
	this->orientationHandler = orientationHandler;
	this->encoderHandler = encoderHandler;
	this->tiltPid = new PID(&tiltPidInput, &tiltPidOutput, &tiltPidSetPoint,
			TILT_PID_P, TILT_PID_I, TILT_PID_D, DIRECT);
	tiltPid->SetMode(AUTOMATIC);
	tiltPid->SetOutputLimits(-255, 255);
}

ControlOutput BalanceControl::getControlValue() {
	Orientation orientation = orientationHandler->getOrientation();
	tiltPidInput = orientation.roll;
	tiltPid->Compute();
	return ControlOutput(-tiltPidOutput, -tiltPidOutput);
}

void BalanceControl::resetPid(double p, double i, double d) {
	this->tiltPid = new PID(&tiltPidInput, &tiltPidOutput, &tiltPidSetPoint,
			p, i, d, DIRECT);
}

