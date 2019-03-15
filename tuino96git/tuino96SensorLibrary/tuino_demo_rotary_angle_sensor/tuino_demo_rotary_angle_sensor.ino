//make sure to connect the sensor to one of the analog PINS
#include "rotaryAngleSensor.h"

RotarySensor rotSen1(A1);

void setup() 
{
    Serial.begin(9600);
}

void loop() 
{
    float angle = rotSen1.getDegree();
    Serial.println("The Rotarysensors angle: ");
    Serial.println(angle);
    delay(1000);
}


