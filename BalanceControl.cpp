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
//	Serial.write("Roll: ");
//	Serial.print(orientation.getSignedRoll());
//	Serial.write("    ");
	tiltPidInput = orientation.getSignedRoll();
	tiltPid->Compute();
//	Serial.write("OUTPUT: ");
//	Serial.print(tiltPidOutput);
//	Serial.write("\n");
	return ControlOutput(-tiltPidOutput, -tiltPidOutput);
}

