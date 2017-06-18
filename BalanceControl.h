#ifndef BALANCECONTROL_H_
#define BALANCECONTROL_H_

#include <PID_v1.h>

#include "Configuration.h"
#include "Logging.h"
#include "OrientationHandler.h"
#include "EncoderHandler.h"
#include "ControlOutput.h"
#include "ControlState.h"
#include "PidData.h"

class BalanceControl {
private:
	OrientationHandler* orientationHandler;
	EncoderHandler* encoderHandler;
	PidData tiltPidData;
	PidData distPidData;
	PidData speedPidData;
	PID* tiltPid = 0;
	PID* distPid = 0;
	PID* speedPid = 0;
	int16_t balanceSetPoint = TILT_PID_BALANCE_SETPOINT;
	int16_t directionSetPoint = TILT_PID_FORWARD_SETPOINT;
	ControlState controlState;

	inline void printTiltIO() {
#if LOG_TILT_PID_IO
		LOGGER.print("tpi;");
		LOGGER.println(OrientationHandler::toDegree(tiltPidData.input));
		LOGGER.print("tpo;");
		LOGGER.println(round(tiltPidData.output));
#endif
	}

	inline void printDistIO() {
#if LOG_DIST_PID_IO
		LOGGER.print("dpi;");
		LOGGER.println(distPidData.input);
		LOGGER.print("dpo;");
		LOGGER.println(distPidData.output);
#endif
	}

	inline void printSpeedIO() {
#if LOG_SPEED_PID_IO
		LOGGER.print("spi;");
		LOGGER.println(speedPidData.input);
		LOGGER.print("spo;");
		LOGGER.println(speedPidData.output);
#endif
	}

	double calculateTiltPidSetPoint();
	double calculateStallSpeedPidSetPoint();
	double calculateDirectionSpeedSetPoint();

public:
	BalanceControl(OrientationHandler* orientationHandler,
			EncoderHandler* encoderHandler);
	ControlOutput getControlOutput();
	void resetTiltPid(const double& p, const double& i, const double& d);
	void resetDistPid(const double& p, const double& i, const double& d);
	void resetSpeedPid(const double& p, const double& i, const double& d);
	double getTiltP() const;
	double getTiltI() const;
	double getTiltD() const;
	double getDistP() const;
	double getDistI() const;
	double getDistD() const;
	double getSpeedP() const;
	double getSpeedI() const;
	double getSpeedD() const;
	int16_t getBalanceSetPoint() const;
	void setBalanceSetPoint(int16_t balanceSetPoint);
	int16_t getDirectionSetPoint() const;
	void setDirectionSetPoint(int16_t directionSetPoint);
	void setControlState(ControlState controlState);
};

#endif
