#ifndef DIAGNOSTICSMETHODS_H_
#define DIAGNOSTICSMETHODS_H_

#include "MotorHandler.h"
#include "EncoderHandler.h"

void motorTest(MotorHandler& motorHandler, EncoderHandler& encoderHandler) {
	for (int offset = 0; offset < 1; offset += 3) {
		Serial.write("OFFSET: ");
		Serial.print(offset);
		Serial.write("\n");
		for (int i = 0; i < 10; i++) {
			motorHandler.setLeftSpeed(45 + i * 10);
			motorHandler.setRightSpeed(45 + i * 10);
			delay(3000);
			motorHandler.setLeftSpeed(0);
			motorHandler.setRightSpeed(0);
			delay(500);
			encoderHandler.printDistance();
			encoderHandler.reset();
		}
	}
}

#endif
