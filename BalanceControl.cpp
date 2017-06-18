#include "BalanceControl.h"

BalanceControl::BalanceControl(OrientationHandler* orientationHandler,
		EncoderHandler* encoderHandler) {
	this->orientationHandler = orientationHandler;
	this->encoderHandler = encoderHandler;
	resetTiltPid(TILT_PID_P, TILT_PID_I, TILT_PID_D);
	resetDistPid(DIST_PID_P, DIST_PID_I, DIST_PID_D);
}

ControlOutput BalanceControl::getControlOutput() {
	Orientation orientation = orientationHandler->getOrientation();
//	if (abs(orientation.roll - tiltPidData.input) > 100) {
//		orientation = orientationHandler->getOrientation();
//	}
	tiltPidData.input = orientation.roll;
	tiltPidData.setPoint = calculateTiltPidSetPoint();
	tiltPid->Compute();
	printTiltIO();
	return ControlOutput(tiltPidData.output, tiltPidData.output);
}

double BalanceControl::calculateTiltPidSetPoint() {
	if(controlState.speed == 0) {
		distPidData.input = encoderHandler->getDistance();
		distPid->Compute();
		printDistIO();
		return balanceSetPoint + distPidData.output;
	} else {
		return ((double) controlState.speed) / DIRECTION_RESOLUTION * directionSetPoint + balanceSetPoint;
	}
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
	this->distPid = new PID(&distPidData.input, &distPidData.output,
				&distPidData.setPoint, p, i, d, DIRECT);
	distPid->SetMode(AUTOMATIC);
	distPid->SetOutputLimits(-DIST_PID_MAX_TILT_OFFSET, DIST_PID_MAX_TILT_OFFSET);
	distPid->SetSampleTime((int)round(1000.0/NOMINAL_FRQ));
}

double BalanceControl::getTiltP() const {
	return tiltPid->GetKp();
}

double BalanceControl::getTiltI() const {
	return tiltPid->GetKi();
}

double BalanceControl::getTiltD() const {
	return tiltPid->GetKd();
}

double BalanceControl::getDistP() const {
	return distPid->GetKp();
}

double BalanceControl::getDistI() const {
	return distPid->GetKi();
}

double BalanceControl::getDistD() const {
	return distPid->GetKd();
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

void BalanceControl::setControlState(ControlState controlState) {
	this->controlState = controlState;
}
