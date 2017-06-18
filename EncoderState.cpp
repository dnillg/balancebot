#include "EncoderState.h"

EncoderState::EncoderState(bool inverted) {
	this->ticks = 0;
	this->lastA = LOW;
	this->inverted = inverted;
}

int16_t EncoderState::getTicks() {
	if (inverted) {
		return -ticks;
	} else {
		return ticks;
	}
}

void EncoderState::update(uint8_t a, uint8_t b) {
	if (lastA == LOW && a == HIGH) {
		if (b == LOW) {
			ticks--;
		} else {
			ticks++;
		}
	}
	lastA = a;
}

void EncoderState::reset() {
	ticks = 0;
}
