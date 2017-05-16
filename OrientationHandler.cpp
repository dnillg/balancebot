/*
 * OrientationProvider.cpp
 *
 *  Created on: 2017. máj. 7.
 *      Author: Reactorx2
 */

#include "OrientationHandler.h"

OrientationHandler::OrientationHandler() {
	Wire.begin();
	Wire.setClock(400000L);
	writeRegister(BNO055_OPR_MODE_ADDR, OPERATION_MODE_CONFIG);
	delay(30);
	writeCalibrationData();
	writeRegister(BNO055_SYS_TRIGGER_ADDR, 0x0);
	delay(30);
	writeRegister(BNO055_OPR_MODE_ADDR, OPERATION_MODE_NDOF);
	delay(30);
}

Orientation OrientationHandler::getOrientation() {
	Orientation orientation = Orientation();
	orientation.pitch |= readRegister(BNO055_EULER_P_MSB_ADDR) << 8;
	orientation.pitch |= readRegister(BNO055_EULER_P_LSB_ADDR);
	orientation.roll |= readRegister(BNO055_EULER_R_MSB_ADDR) << 8;
	orientation.roll |= readRegister(BNO055_EULER_R_LSB_ADDR);
	orientation.yaw |= readRegister(BNO055_EULER_H_MSB_ADDR) << 8;
	orientation.yaw |= readRegister(BNO055_EULER_H_LSB_ADDR);
//	if (millis() % 5 == 0) {
//		Serial.print(orientation.pitch);
//		Serial.print(" ");
//		Serial.print(orientation.roll);
//		Serial.print(" ");
//		Serial.print(orientation.yaw);
//		Serial.println(" ");
//	}
	return orientation;
}

void OrientationHandler::printCalibrationData() {
	uint8_t calib = readRegister(BNO055_CALIB_STAT_ADDR);
	char buf[4];
	sprintf(buf, "%02X", calib);
	Serial.write(buf);
	if (calib) {
		Serial.write(" ");
		for (int i = 0; i < 22; i++) {
			sprintf(buf, "%02X ", readRegister(0x55 + i));
			Serial.print(buf);
		}
	}
	Serial.println();
}

uint8_t OrientationHandler::readRegister(uint8_t regAddr) {
	byte value = 0;
	Wire.beginTransmission(I2C_ADDR);
	Wire.write(regAddr);
	Wire.endTransmission();
	Wire.requestFrom(I2C_ADDR, (uint8_t) 1);
	value = Wire.read();
	return value;
}

void OrientationHandler::writeRegister(uint8_t key, uint8_t value) {
	Wire.beginTransmission(I2C_ADDR);
	Wire.write(key);
	Wire.write(value);
	Wire.endTransmission();
}

void OrientationHandler::writeCalibrationData() {
	writeRegister(BNO055_CALIB_STAT_ADDR, calibrationData[0]);
	for (int i = 0; i < 22; i++) {
		writeRegister(ACCEL_OFFSET_X_LSB_ADDR + i, calibrationData[i + 1]);
	}
}

double OrientationHandler::toDegree(uint8_t raw) {
	return raw * RAW_TO_DEGREE;
}

const uint8_t OrientationHandler::I2C_ADDR = I2C_ADDR_BNO055;
const double OrientationHandler::RAW_TO_DEGREE = 1.0 / 16.0;
