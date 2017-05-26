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
	PID* tiltPid = 0;

	inline void printIO() {
#if LOG_PID_IO
		Serial.print("roll;");
		Serial.println(OrientationHandler::toDegree(tiltPidData.input));

		Serial.print("tilt_pid_out;");
		Serial.println(round(tiltPidData.output));
#endif
	}

public:
	BalanceControl(OrientationHandler* orientationHandler,
			EncoderHandler* encoderHandler);
	ControlOutput getControlValue();
	void resetPid(const double& p, const double& i, const double& d, const double& setPoint);
	double getP() const;
	double getI() const;
	double getD() const;
	const double& getSetPoint() const;
};

#endif
