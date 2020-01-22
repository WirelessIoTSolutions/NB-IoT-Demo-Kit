/**
 * @file rotaryAngleSensor.cpp
 * @description Functions to drive the OLED display
 * @author htemizel
 * @copyright (C) 2019 mm1 Technology GmbH - all rights reserved.
 * @licence MIT licence
 *
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
 */
#include "rotaryAngleSensor.h"

RotarySensor::RotarySensor(int analogPinNumber) {
    this->analogPinNumber = analogPinNumber;
    pinMode(this->analogPinNumber, INPUT);
}

float RotarySensor::getDegree()
{
    int sensor_value = analogRead(this->analogPinNumber);
    float voltage = (float)sensor_value*ADC_REF/1023;
    float degrees = (voltage*FULL_ANGLE)/GROVE_VCC;
    return degrees;
}
