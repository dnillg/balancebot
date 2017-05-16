#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include "Arduino.h"

class StringUtils {
public:
	static void initDisplayBuffer(char* buffer, size_t size) {
		memset(buffer, ' ', size);
		memset(buffer + size - 1, 0, 1);
	}
	static void printDouble(char* buffer, double value, signed char width,
			unsigned char prec) {
		size_t tmpBufSize = width + prec + 2;
		char* tmpBuf = new char[tmpBufSize];
		dtostrf(value, width, prec, tmpBuf);
		memcpy(buffer, tmpBuf, tmpBufSize - 1);
		delete tmpBuf;
	}

};

#endif
