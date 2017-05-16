#define SERIAL_RX_BUFFER_SIZE 96
#define SERIAL_TX_BUFFER_SIZE 96

#include "Arduino.h"

#include "Configuration.h"
#include "MotorHandler.h"
#include "OrientationHandler.h"
#include "EncoderHandler.h"
#include "BalanceControl.h"
#include "DiagnosticsMethods.h"
#include "FrequencyRegulator.h"
#include "DisplayHandler.h"
#include "JobScheduler.h"
#include "SerialCommandParser.h"

typedef struct {
	MotorHandler* motorHandler;
	OrientationHandler* orientationHandler;
	EncoderHandler* encoderHandler;
	BalanceControl* balanceControl;
	FrequencyRegulator* frequencyRegulator;
	JobScheduler* jobScheduler;
	DisplayHandler* displayHandler;
	SerialCommandParser* commandParser;
} Context;

Context context;

void updateLeftWheel();
void updateRightWheel();
void printEffectiveFrequency();
void printEffectiveFrequencyLcd();
void printStatusCharLcd();

void setup() {
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

	attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_RIGHT_A),
			updateRightWheel, CHANGE);
	attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_LEFT_A), updateLeftWheel,
	CHANGE);

	Serial.begin(38400);
	while (!Serial)
		;

	context.motorHandler = new MotorHandler(MOTOR_MIN, MOTOR_LEFT_OFFSET,
	MOTOR_RIGHT_OFFSET);
	context.orientationHandler = new OrientationHandler();
	context.encoderHandler = new EncoderHandler();
	context.balanceControl = new BalanceControl(context.orientationHandler,
			context.encoderHandler);
	context.frequencyRegulator = new FrequencyRegulator(100);
	context.displayHandler = new DisplayHandler(context.balanceControl,
			context.frequencyRegulator);
	context.jobScheduler = new JobScheduler();
	context.commandParser = new SerialCommandParser(context.balanceControl, context.motorHandler, context.displayHandler);

	context.jobScheduler->addJob(100, printEffectiveFrequency);
	context.jobScheduler->addJob(500, printEffectiveFrequencyLcd);
	context.jobScheduler->addJob(100, printStatusCharLcd);

	context.displayHandler->printParams(context.balanceControl->getP(),
			context.balanceControl->getI(), context.balanceControl->getD());
}

unsigned long loops = 0;

void loop() {
	context.commandParser->handleCommands();
	context.frequencyRegulator->waitTick();
	context.jobScheduler->tick();
	ControlOutput output = context.balanceControl->getControlValue();
	context.motorHandler->setLeftSpeed(output.left);
	context.motorHandler->setRightSpeed(output.right);

	if (millis() > 2000000) {
		context.motorHandler->setEnabled(0);
	}

	Serial.flush();
	loops++;
}

void updateLeftWheel() {
	context.encoderHandler->updateLeftWheel(digitalRead(PIN_ENCODER_LEFT_A),
			digitalRead(PIN_ENCODER_LEFT_B));
}

void updateRightWheel() {
	context.encoderHandler->updateRightWheel(digitalRead(PIN_ENCODER_RIGHT_A),
			digitalRead(PIN_ENCODER_RIGHT_B));
}

void printEffectiveFrequency() {
	context.frequencyRegulator->printEffectiveFrequency();
}

void printEffectiveFrequencyLcd() {
	context.displayHandler->printFrequency(
			context.frequencyRegulator->getEffectiveFrequency());
}

void printStatusCharLcd() {
	context.displayHandler->printStatusChar();
}
