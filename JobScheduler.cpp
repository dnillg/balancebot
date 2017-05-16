#include "JobScheduler.h"

void JobScheduler::addJob(const uint16_t& period, void (*userFunc)(void)) {
	timedFunctions.push_back(TimedFunc(period, userFunc));
}

void JobScheduler::tick() {
	for(size_t i = 0; i < timedFunctions.size(); i++) {
		TimedFunc& tf = timedFunctions[i];
		tf.passed++;
		if(tf.passed == tf.period) {
			timedFunctions[i].userFunc();
			tf.passed = 0;
		}
	}
}
