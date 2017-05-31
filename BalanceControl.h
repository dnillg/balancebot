#ifndef BALANCECONTROL_H_
#define BALANCECONTROL_H_

#include <PID_v1.h>

#include "Configuration.h"
#include "OrientationHandler.h"
#include "EncoderHandler.h"
#include "ControlOutput.h"
#include "PidData.h"

class BalanceControl {
private:
	OrientationHandler* orientationHandler;
	EncoderHandler* encoderHandler;
	PidData tiltPidData;
	PidData distPidData;
	PID* tiltPid = 0;
	PID* distPid = 0;
	int16_t balanceSetPoint = TILT_PID_BALANCE_SETPOINT;
	int16_t directionSetPoint = TILT_PID_FORWARD_SETPOINT;

	inline void printIO() {
#if LOG_TILT_PID_IO
		Serial.print("tpi;");
		Serial.println(OrientationHandler::toDegree(tiltPidData.input));
		Serial.print("tpo;");
		Serial.println(round(tiltPidData.output));
#endif
#if LOG_DIST_PID_IO
		Serial.print("dpi;");
		Serial.println(OrientationHandler::toDegree(tiltPidData.input));
		Serial.print("dpo;");
		Serial.println(round(tiltPidData.output));
#endif
	}

public:
	BalanceControl(OrientationHandler* orientationHandler,
			EncoderHandler* encoderHandler);
	ControlOutput getControlValue();
	void resetTiltPid(const double& p, const double& i, const double& d);
	void resetDistPid(const double& p, const double& i, const double& d);
	double getP() const;
	double getI() const;
	double getD() const;
	int16_t getBalanceSetPoint() const;
	void setBalanceSetPoint(int16_t balanceSetPoint);
	int16_t getDirectionSetPoint() const;
	void setDirectionSetPoint(int16_t directionSetPoint);
};

#endif
