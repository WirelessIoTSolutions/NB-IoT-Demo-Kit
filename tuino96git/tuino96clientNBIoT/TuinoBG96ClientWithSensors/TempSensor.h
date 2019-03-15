/**
 * @file TempSensor.h
 * @description Functions to drive the Seeed temp sensor
 * @author htemizel
 * @copyright (C) 2019 mm1 Technology GmbH - all rights reserved.
 * @licence MIT licence
 *
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
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
