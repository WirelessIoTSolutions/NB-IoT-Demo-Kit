//make sure to connect the sensor to one of the digital PINS
#include "motionSensor.h"

MotionSensor moSe1(4);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if(moSe1.isMotionDetected())//if it detects the moving people?
        Serial.print("Motion detected");
    delay(2000);
}
