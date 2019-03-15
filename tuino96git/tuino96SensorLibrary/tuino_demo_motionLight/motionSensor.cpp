#include "motionSensor.h"

MotionSensor::MotionSensor(int digitalPinNumber) {
    this->digitalPinNumber = digitalPinNumber;
    pinMode(this->digitalPinNumber, INPUT);
}

bool MotionSensor::isMotionDetected()
{
    return digitalRead(this->digitalPinNumber);
}
