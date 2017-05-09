#include "Arduino.h"

#include "BalanceBotPins.h"
#include "MotorHandler.h"
#include "OrientationHandler.h"
#include "EncoderHandler.h"
#include "BalanceControl.h"

MotorHandler* motorHandler;
OrientationHandler* orientationHandler;
EncoderHandler* encoderHandler;
BalanceControl* balanceControl;

void setup() {
	//Pins
	pinMode(PIN_ENCODER_LEFT_A, INPUT);
	pinMode(PIN_ENCODER_LEFT_A, INPUT);
	pinMode(PIN_ENCODER_RIGHT_A, INPUT_PULLUP);
	pinMode(PIN_ENCODER_RIGHT_B, INPUT_PULLUP);
	pinMode(PIN_HB_RIGHT_ENABLE, OUTPUT);
	pinMode(PIN_HB_LEFT_FORWARD, OUTPUT);
	pinMode(PIN_HB_LEFT_BACKWARD, OUTPUT);
	pinMode(PIN_HB_LEFT_ENABLE, OUTPUT);
	pinMode(PIN_HB_RIGHT_BACKWARD, OUTPUT);
	pinMode(PIN_HB_RIGHT_FORWARD, OUTPUT);

	//Interrupts
	//attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_RIGHT_A),
	//		updateRightWheel, CHANGE);
	//attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_LEFT_A), updateLeftWheel,
	//CHANGE);

	//Serial
	Serial.begin(9600);
	while (!Serial);

	motorHandler = new MotorHandler(50, 3, 0);
	orientationHandler = new OrientationHandler();
	encoderHandler = new EncoderHandler();
	balanceControl = new BalanceControl(orientationHandler, encoderHandler);

}

void printDistance() {
	Serial.write("LEFT: ");
	Serial.print(encoderHandler->getLeftDistance());
	Serial.write("    ");
	Serial.write("RIGHT: ");
	Serial.print(encoderHandler->getRightDistance());
	Serial.write("\n");
}

long i = 0;

void loop() {
	ControlOutput output = balanceControl->getControlValue();
	//delay(100);
	if (millis() < 32000) {
		motorHandler->setLeftSpeed(output.left);
		motorHandler->setRightSpeed(output.right);
	} else {
		motorHandler->setLeftSpeed(0);
		motorHandler->setRightSpeed(0);
	}
	//delay(7);
	i++;
	if(i%100 == 0) {
//		Serial.print(millis());
//		Serial.write("\n");
	}
}

void updateLeftWheel() {
	encoderHandler->updateLeftWheel(digitalRead(PIN_ENCODER_LEFT_A),
			digitalRead(PIN_ENCODER_LEFT_B));
}

void updateRightWheel() {
	encoderHandler->updateRightWheel(digitalRead(PIN_ENCODER_RIGHT_A),
			digitalRead(PIN_ENCODER_RIGHT_B));
}

void motorTest() {
	for (int offset = 0; offset < 16; offset+=3) {
			Serial.write("OFFSET: ");
			Serial.print(offset);
			Serial.write("\n");
			for (int i = 0; i < 5; i++) {
				motorHandler->setLeftSpeed(50 + i*20 + offset);
				motorHandler->setRightSpeed(50 + i*20 );
				delay(2000);
				motorHandler->setLeftSpeed(0);
				motorHandler->setRightSpeed(0);
				delay(1000);
				printDistance();
				encoderHandler->reset();
			}
		}
}
