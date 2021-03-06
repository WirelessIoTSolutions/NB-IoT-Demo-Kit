/**
 * @file TempSensor.h
 * @description Functions to drive the Seeed temp sensor
 * @author htemizel
 * @copyright (C) 2019 WIOTS GmbH - all rights reserved.
 * @licence MIT licence
 *
 * Find out more about WIOTS:
 * Company: https://wireless-iot-solutions.com/wp/
 * GitHub:  https://github.com/WirelessIoTSolutions/
 */
#ifndef TEMPSENSOR_h_
#define TEMPSENSOR_h_

#include <Arduino.h>
#include <math.h>

class TempSensor {
    private:
    int analogPinNumber;

    public:
    TempSensor(int analogPinNumber);
    float getTemperature();
};
#endif
