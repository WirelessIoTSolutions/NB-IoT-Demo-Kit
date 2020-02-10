/**
 * @file lightSensor.h
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
