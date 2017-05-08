/*
 * OrientationProvider.cpp
 *
 *  Created on: 2017. máj. 7.
 *      Author: Reactorx2
 */

#include "OrientationHandler.h"


OrientationHandler::OrientationHandler() {
	Wire.begin();
	delay(30);
	writeRegister(BNO055_SYS_TRIGGER_ADDR, 0x0);
	delay(10);
	writeRegister(BNO055_OPR_MODE_ADDR, OPERATION_MODE_NDOF);
	delay(50);
}

Orientation OrientationHandler::getOrientation() {
	Orientation orientation = Orientation();
	orientation.pitch |= readRegister(BNO055_EULER_P_MSB_ADDR) << 8;
	orientation.pitch |= readRegister(BNO055_EULER_P_LSB_ADDR);
	orientation.roll |= readRegister(BNO055_EULER_R_MSB_ADDR) << 8;
	orientation.roll |= readRegister(BNO055_EULER_R_LSB_ADDR);
	orientation.yaw |= readRegister(BNO055_EULER_H_MSB_ADDR) << 8;
	orientation.yaw |= readRegister(BNO055_EULER_H_LSB_ADDR);
	return orientation;
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
