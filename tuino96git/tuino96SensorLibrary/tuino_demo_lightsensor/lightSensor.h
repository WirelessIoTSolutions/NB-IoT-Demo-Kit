/**
 * @file lightSensor.h
 * @description Functions to drive the OLED display
 * @author htemizel
 * @copyright (C) 2019 WIOTS GmbH - all rights reserved.
 * @licence MIT licence
 *
 * Find out more about WIOTS:
 * Company: https://wireless-iot-solutions.com/wp/
 * GitHub:  https://github.com/WirelessIoTSolutions/
 */
#ifndef LIGHTSENSOR_h_
#define LIGHTSENSOR_h_

#include <Arduino.h>

#define LUX_FACTOR 1.18795

class LightSensor {
    private:
    int analogPinNumber;

    public:
    LightSensor(int analogPinNumber);
    int getLightAmountiinLumen();
    float getLightAmountiinLux();
};

#endif
