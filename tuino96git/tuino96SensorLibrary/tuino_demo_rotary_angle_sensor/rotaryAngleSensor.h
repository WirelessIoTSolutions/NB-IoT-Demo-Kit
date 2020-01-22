/**
 * @file rotaryAngleSensor.h
 * @description Functions to drive the OLED display
 * @author htemizel
 * @copyright (C) 2019 mm1 Technology GmbH - all rights reserved.
 * @licence MIT licence
 *
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
 */
#ifndef ROTARYANGLESENSOR_h_
#define ROTARYANGLESENSOR_h_

#include <Arduino.h>

#define ADC_REF 5//reference voltage of ADC is 5v.If the Vcc switch on the seeeduino
//board switches to 3V3, the ADC_REF should be 3.3
#define GROVE_VCC 5//VCC of the grove interface is normally 5v
#define FULL_ANGLE 300//full value of the rotary angle is 300 degrees

class RotarySensor {
    private:
    int analogPinNumber;

    public:
    RotarySensor(int analogPinNumber);
    float getDegree();
};

#endif
