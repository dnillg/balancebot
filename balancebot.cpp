#define SERIAL_RX_BUFFER_SIZE 128
#define SERIAL_TX_BUFFER_SIZE 128

#include "Arduino.h"

#include "Configuration.h"
#include "MotorHandler.h"
#include "OrientationHandler.h"
#include "EncoderHandler.h"
#include "BalanceControl.h"
#include "FrequencyRegulator.h"
#include "DisplayHandler.h"
#include "JobScheduler.h"
#include "LedMatrixHandler.h"
#include "CommandParser.h"
#include "SoftwareSerial.h"
#include "BluetoothSerial.h"
#include "Logging.h"

typedef struct {
	MotorHandler* motorHandler;
	OrientationHandler* orientationHandler;
	EncoderHandler* encoderHandler;
	BalanceControl* balanceControl;
	FrequencyRegulator* frequencyRegulator;
	JobScheduler* jobScheduler;
	DisplayHandler* displayHandler;
	CommandParser<HardwareSerial>* hwsCommandParser;
	CommandParser<SoftwareSerial>* btCommandParser;
	LedMatrixHandler* ledMatrixHandler;
} Context;

Context context;

void updateLeftWheel();
void updateRightWheel();
void printEffectiveFrequency();
void printEffectiveFrequencyLcd();
void printStatusCharLcd();
void registerScheduledJobs();
void calculateSpeed();

void setup() {
	pinMode(PIN_ENCODER_LEFT_A, INPUT_PULLUP);
	pinMode(PIN_ENCODER_LEFT_B, INPUT);
	pinMode(PIN_ENCODER_RIGHT_A, INPUT_PULLUP);
	pinMode(PIN_ENCODER_RIGHT_B, INPUT);
	pinMode(PIN_HB_RIGHT_ENABLE, OUTPUT);
	pinMode(PIN_HB_LEFT_FORWARD, OUTPUT);
	pinMode(PIN_HB_LEFT_BACKWARD, OUTPUT);
	pinMode(PIN_HB_LEFT_ENABLE, OUTPUT);
	pinMode(PIN_HB_RIGHT_BACKWARD, OUTPUT);
	pinMode(PIN_HB_RIGHT_FORWARD, OUTPUT);

	attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_RIGHT_A),
			updateRightWheel, CHANGE);
	attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_LEFT_A),
			updateLeftWheel, CHANGE);

	Serial.begin(SERIAL_BAUD);
	BtSerial.begin(HC_06_DEFAULT_BAUDRATE);
	BtSerial.println("AT+BAUD" + HC_06_BAUD_RATE_LEVEL);

	context.motorHandler = new MotorHandler(MOTOR_MIN, MOTOR_LEFT_OFFSET,
	MOTOR_RIGHT_OFFSET);
	context.orientationHandler = new OrientationHandler();
	context.encoderHandler = new EncoderHandler(context.orientationHandler);
	context.balanceControl = new BalanceControl(context.orientationHandler,
			context.encoderHandler);
	context.frequencyRegulator = new FrequencyRegulator(NOMINAL_FRQ);
	context.displayHandler = new DisplayHandler(context.balanceControl, context.frequencyRegulator);
	context.jobScheduler = new JobScheduler();
	context.hwsCommandParser = new CommandParser<HardwareSerial>(&Serial, context.balanceControl, context.motorHandler, context.displayHandler);
	context.btCommandParser = new CommandParser<SoftwareSerial>(&BtSerial, context.balanceControl, context.motorHandler, context.displayHandler);
	context.ledMatrixHandler = new LedMatrixHandler();

	registerScheduledJobs();

	context.displayHandler->printParams(context.balanceControl->getTiltP(),
	context.balanceControl->getTiltI(), context.balanceControl->getTiltD());
}

void loop() {
	context.btCommandParser->readNativeSerialCommands();
	context.hwsCommandParser->readNativeSerialCommands();
	context.frequencyRegulator->waitTick();
	context.jobScheduler->tick();
	context.encoderHandler->handleTicks();

	ControlOutput output = context.balanceControl->getControlOutput();
	context.motorHandler->setLeftSpeed(output.left);
	context.motorHandler->setRightSpeed(output.right);

	//Serial.flush();
	//BtSerial.flush();
}

void registerScheduledJobs() {
	context.jobScheduler->addJob(SJF_EFFECTIVE_FRQ_LOG,
			printEffectiveFrequency);
	context.jobScheduler->addJob(SJF_EFFECTIVE_FRQ_LCD,
			printEffectiveFrequencyLcd);
	context.jobScheduler->addJob(SJF_STATUS_CHAR_LCD,
			printStatusCharLcd);
	context.jobScheduler->addJob(SJF_SPEED_CALC,
			calculateSpeed);
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

void calculateSpeed() {
	context.encoderHandler->calculateSpeed();
}

