#ifndef JOBSCHEDULER_H_
#define JOBSCHEDULER_H_

#include "Arduino.h"

#include "AvrVector.h"

class JobScheduler {
private:
	struct TimedFunc {
		uint16_t passed;
		uint16_t period;
		void (*userFunc)(void) = 0;
		TimedFunc(const uint16_t& period, void (*userFunc)(void)) {
			this->period = period;
			this->userFunc = userFunc;
			this->passed = 0;
		}
	};

	AvrVector<TimedFunc> timedFunctions;
public:
	void addJob(const uint16_t& period, void (*userFunc)(void));
	void tick();
};

#endif
