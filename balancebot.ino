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
	attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_RIGHT_A),
			updateRightWheel, CHANGE);
	attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_LEFT_A), updateLeftWheel,
	CHANGE);

	//Serial
	Serial.begin(9600);
	while (!Serial)
		;

	motorHandler = new MotorHandler(1);
	orientationHandler = new OrientationHandler();
	encoderHandler = new EncoderHandler();
	balanceControl = new BalanceControl(orientationHandler, encoderHandler);

	//motorTest();
}

void loop() {
	ControlOutput output = balanceControl->getControlValue();
	if (millis() < 15000) {
		motorHandler->setLeftSpeed(output.left);
		motorHandler->setRightSpeed(output.right);
	} else {
		motorHandler->setLeftSpeed(0);
		motorHandler->setRightSpeed(0);
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
	digitalWrite(PIN_HB_LEFT_FORWARD, LOW);
	digitalWrite(PIN_HB_LEFT_BACKWARD, LOW);
	digitalWrite(PIN_HB_RIGHT_BACKWARD, LOW);
	digitalWrite(PIN_HB_RIGHT_FORWARD, LOW);
	digitalWrite(PIN_HB_LEFT_ENABLE, LOW);
	digitalWrite(PIN_HB_RIGHT_ENABLE, LOW);

	digitalWrite(PIN_HB_LEFT_FORWARD, HIGH);
	analogWrite(PIN_HB_LEFT_ENABLE, 125);
	delay(500);
	digitalWrite(PIN_HB_LEFT_FORWARD, LOW);

	analogWrite(PIN_HB_RIGHT_ENABLE, 125);
	digitalWrite(PIN_HB_RIGHT_FORWARD, HIGH);
	delay(500);
	digitalWrite(PIN_HB_RIGHT_FORWARD, LOW);
}
