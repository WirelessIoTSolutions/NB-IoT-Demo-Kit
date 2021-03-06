/**
 * @file lightSensor.cpp
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
#include "lightSensor.h"

LightSensor::LightSensor(int analogPinNumber) {
    this->analogPinNumber = analogPinNumber;
    pinMode(this->analogPinNumber, OUTPUT);
}

int LightSensor::getLightAmountiinLumen(){
    int sensorValue = analogRead(this->analogPinNumber);
    return sensorValue;
}

float LightSensor::getLightAmountiinLux(){
    int sensorValue = analogRead(this->analogPinNumber);
    float lux = LUX_FACTOR * sensorValue;
    return lux;
}
