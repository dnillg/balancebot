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
	resetPid(TILT_PID_P, TILT_PID_I, TILT_PID_D, TILT_PID_SETPOINT);
}

ControlOutput BalanceControl::getControlValue() {
	Orientation orientation = orientationHandler->getOrientation();
	tiltPidData.input = orientation.roll;
	if(orientation.roll > 200 || orientation.roll < -200) {
		//Serial.println(orientation.roll);
	}
	tiltPid->Compute();
	printIO();
	return ControlOutput(tiltPidData.output, tiltPidData.output);
}

void BalanceControl::resetPid(const double& p, const double& i, const double& d,
		const double& setPoint) {
	if(tiltPid != NULL) {
		delete this->tiltPid;
	}
	this->tiltPidData.setPoint = setPoint;
	this->tiltPid = new PID(&tiltPidData.input, &tiltPidData.output,
			&tiltPidData.setPoint, p, i, d, REVERSE);
	tiltPid->SetMode(AUTOMATIC);
		tiltPid->SetOutputLimits(-255, 255);
}

double BalanceControl::getP() const {
	return tiltPid->GetKp();
}

double BalanceControl::getI() const {
	return tiltPid->GetKi();
}

double BalanceControl::getD() const {
	return tiltPid->GetKd();
}

const double& BalanceControl::getSetPoint() const {
	return tiltPidData.setPoint;
}

