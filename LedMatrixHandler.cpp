#include "LedMatrixHandler.h"

LedMatrixHandler::LedMatrixHandler() {
	ledControl.shutdown(0, false);
	ledControl.setIntensity(0, LED_MATRIX_LIGHT_INTENSITY);
	ledControl.clearDisplay(0);
	drawImage(IMAGE_SMILEY_HAPPY);
}

void LedMatrixHandler::drawImage(const char image[]) {
	for(int i = 0; i < 8; i++) {
		ledControl.setColumn(0, i, image[7-i]);
	}
}

const char LedMatrixHandler::IMAGE_SMILEY_HAPPY[8] = {0x00, 0x24, 0x00, 0x00, 0x00, 0x42, 0x3C, 0x00};
const char LedMatrixHandler::IMAGE_SMILEY_SAD[8] = {0x00, 0x24, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x00};
