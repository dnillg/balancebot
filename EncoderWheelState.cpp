#include "EncoderWheelState.h"

EncoderWheelState::EncoderWheelState() {
	ticks = 0;
	lastA = LOW;
}

int16_t EncoderWheelState::getTicks() {
	return ticks;
}

void EncoderWheelState::update(uint8_t a, uint8_t b) {
	if (lastA == LOW && a == HIGH) {
		if (b == LOW) {
			ticks--;
		} else {
			ticks++;
		}
	}
	lastA = a;
}
