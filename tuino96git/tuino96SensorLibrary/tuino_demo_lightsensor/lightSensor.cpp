/**
 * @file lightSensor.cpp
 * @description Functions to drive the OLED display
 * @author htemizel
 * ATTENTION: Need a subscription to Nb-IoT relay service and client library on IoT device to work
 * @copyright (C) 2019 WIOTS GmbH - all rights reserved.
 * @licence MIT licence
 *
 * Find out more about WIOTS:
 * Company:     https://wireless-iot-solutions.com/wp/
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
