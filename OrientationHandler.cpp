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
	read((byte*)&orientation.pitch, BNO055_EULER_P_MSB_ADDR, 2);
	read((byte*)&orientation.roll, BNO055_EULER_R_LSB_ADDR, 2);
	read((byte*)&orientation.yaw, BNO055_EULER_H_MSB_ADDR, 2);
	return orientation;
}

void OrientationHandler::printCalibrationData() {
	uint8_t calib = readRegister(BNO055_CALIB_STAT_ADDR);
	char buf[4];
	sprintf(buf, "%02X", calib);
	LOGGER.print(buf);
	for (int i = 0; i < 22; i++) {
		sprintf(buf, ";%02X", readRegister(0x55 + i));
		LOGGER.print(buf);
	}
	LOGGER.println();
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

void OrientationHandler::read(byte* to, uint8_t regAddr, size_t size) {
	Wire.beginTransmission(I2C_ADDR);
	Wire.write(regAddr);
	Wire.endTransmission();
	Wire.requestFrom(I2C_ADDR, size);
	for(uint8_t i = 0; i < size; i++) {
		to[i] = Wire.read();
	}
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

double OrientationHandler::toDegree(double raw) {
	return raw * RAW_TO_DEGREE;
}

const uint8_t OrientationHandler::I2C_ADDR = I2C_ADDR_BNO055;
const double OrientationHandler::RAW_TO_DEGREE = 1.0 / 16.0;
