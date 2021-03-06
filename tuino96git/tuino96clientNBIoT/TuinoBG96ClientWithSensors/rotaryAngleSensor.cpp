/**
 * @file rotaryAngleSensor.cpp
 * @description Functions to drive the OLED display
 * @author htemizel
 * @copyright (C) 2019 WIOTS GmbH - all rights reserved.
 * @licence proprietary licence - WIOTS grants all users of the WIOTS relay service 
 * the right to use this software for evaluation and testing. It is not allowed to use this software 
 * with any other service than the WIOTS relay service of copy or use this software into other 
 * projects than related to the WIOTS relay service.
 *
 * Find out more about WIOTS:
 * Company: https://wireless-iot-solutions.com/wp/
 * GitHub:  https://github.com/WirelessIoTSolutions/
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
