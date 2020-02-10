/**
 * @file TempSensor.cpp
 * @description Functions to drive the Seeed temp sensor
 * @author htemizel
 * @copyright (C) 2019 WIOTS GmbH - all rights reserved.
 * @licence MIT licence
 *
 * Find out more about WIOTS:
 * Company: https://wireless-iot-solutions.com/wp/
 * GitHub:  https://github.com/WirelessIoTSolutions/
 */
#include "TempSensor.h"

TempSensor::TempSensor(int analogPinNumber) {
    this->analogPinNumber = analogPinNumber;
    pinMode(this->analogPinNumber, INPUT);
}

float TempSensor::getTemperature(){
    const int B = 4275;               // B value of the thermistor
    const int R0 = 100000; 

    int a = analogRead(this->analogPinNumber);

    float R = 1023.0/a-1.0;
    R = R0*R;

    float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet
    return temperature;
}
