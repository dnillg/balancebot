#include "Arduino.h"

#include "OrientationProvider.h"

OrientationProvider* orientationProvider;

void setup()
{
	Serial.begin(9600);
	while (!Serial);
	delay(100);
	orientationProvider = new OrientationProvider();
}

// The loop function is called in an endless loop
void loop()
{
	Orientation orientation = orientationProvider->getOrientation();
	Serial.print(orientation.pitch);
	Serial.write("\n");
	delay(2000);
}
