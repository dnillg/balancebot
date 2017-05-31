#include "BalanceControl.h"

BalanceControl::BalanceControl(OrientationHandler* orientationHandler,
		EncoderHandler* encoderHandler) {
	this->orientationHandler = orientationHandler;
	this->encoderHandler = encoderHandler;
	resetTiltPid(TILT_PID_P, TILT_PID_I, TILT_PID_D);
}

ControlOutput BalanceControl::getControlValue() {
	Orientation orientation = orientationHandler->getOrientation();
//	if (abs(orientation.roll - tiltPidData.input) > 100) {
//		orientation = orientationHandler->getOrientation();
//	}

	tiltPidData.input = orientation.roll;
	tiltPid->Compute();
	printIO();
	return ControlOutput(tiltPidData.output, tiltPidData.output);
}

void BalanceControl::resetTiltPid(const double& p, const double& i, const double& d) {
	if (tiltPid != NULL) {
		delete this->tiltPid;
	}
	this->tiltPid = new PID(&tiltPidData.input, &tiltPidData.output,
			&tiltPidData.setPoint, p, i, d, REVERSE);
	tiltPid->SetMode(AUTOMATIC);
	tiltPid->SetOutputLimits(-UINT8_MAX, UINT8_MAX);
	tiltPid->SetSampleTime((int)round(1000.0/NOMINAL_FRQ));
}

void BalanceControl::resetDistPid(const double& p, const double& i, const double& d) {
	if (distPid != NULL) {
		delete this->distPid;
	}
	this->distPid = new PID(&tiltPidData.input, &tiltPidData.output,
				&tiltPidData.setPoint, p, i, d, REVERSE);
	distPid->SetMode(AUTOMATIC);
	distPid->SetOutputLimits(-DIST_PID_MAX_TILT_OFFSET, DIST_PID_MAX_TILT_OFFSET);
	distPid->SetSampleTime((int)round(1000.0/NOMINAL_FRQ));
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

int16_t BalanceControl::getBalanceSetPoint() const {
	return balanceSetPoint;
}

void BalanceControl::setBalanceSetPoint(int16_t balanceSetPoint) {
	this->balanceSetPoint = balanceSetPoint;
}

int16_t BalanceControl::getDirectionSetPoint() const {
	return directionSetPoint;
}

void BalanceControl::setDirectionSetPoint(int16_t directionSetPoint) {
	this->directionSetPoint = directionSetPoint;
}
