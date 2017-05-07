/*
 * OrientationProvider.cpp
 *
 *  Created on: 2017. máj. 7.
 *      Author: Reactorx2
 */

#include "OrientationProvider.h"

void OrientationProvider::write8(uint8_t key, uint8_t value) {
	Wire.beginTransmission(I2C_ADDR);
	Wire.write(key);
	Wire.write(value);
	Wire.endTransmission();
}

OrientationProvider::OrientationProvider() {
	Wire.begin();
	delay(30);
	write8(BNO055_OPR_MODE_ADDR, OPERATION_MODE_NDOF);
	delay(50);
	write8(BNO055_SYS_TRIGGER_ADDR, 0x0);
	delay(10);
	write8(BNO055_OPR_MODE_ADDR, OPERATION_MODE_NDOF);
	delay(50);
}

Orientation OrientationProvider::getOrientation() {
	Orientation orientation = Orientation();
	orientation.pitch |= readRegister(PITCH_MSB) << 8;
	orientation.pitch |= readRegister(PITCH_LSB);
	orientation.roll |= readRegister(ROLL_MSB) << 8;
	orientation.roll |= readRegister(ROLL_LSB);
	orientation.yaw |= readRegister(YAW_MSB) << 8;
	orientation.yaw |= readRegister(YAW_LSB);
	return orientation;
}

uint8_t OrientationProvider::readRegister(uint8_t regNum) {
	byte value = 0;
	Wire.beginTransmission(I2C_ADDR);
	Wire.write(regNum);
	Wire.endTransmission();
	Wire.requestFrom(I2C_ADDR, (uint8_t) 1);
	value = Wire.read();
	return value;
}
