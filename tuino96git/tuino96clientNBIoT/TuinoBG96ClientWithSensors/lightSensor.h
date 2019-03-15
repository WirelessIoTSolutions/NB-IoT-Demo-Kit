/**
 * @file lightSensor.h
 * @description Functions to drive the OLED display
 * @author htemizel
 * @copyright (C) 2019 mm1 Technology GmbH - all rights reserved.
 * @licence proprietary licence - mm1 Technology grants all users of the mm1 Technology relay service 
 * the right to use this software for evaluation and testing. It is not allowed to use this software 
 * with any other service than the mm1 Technology relay service of copy or use this software into other 
 * projects than related to the mm1 Technology relay service.
 *
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
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
