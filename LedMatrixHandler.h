#ifndef LEDMATRIXHANDLER_H_
#define LEDMATRIXHANDLER_H_

#include "Arduino.h"
#include "LedControl.h"

#include "Configuration.h"

class LedMatrixHandler {
public:
	static const char IMAGE_SMILEY_HAPPY[8];
	static const char IMAGE_SMILEY_SAD[8];
private:
	LedControl ledControl = LedControl(PIN_LEDMATRIX_DIN, PIN_LEDMATRIX_CLK, PIN_LEDMATRIX_CS, 1);
public:
	LedMatrixHandler();
private:
	void drawImage(const char image[]);
};

#endif
