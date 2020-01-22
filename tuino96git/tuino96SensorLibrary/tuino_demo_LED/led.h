/**
 * @file led.h
 * @description Functions to drive the OLED display
 * @author htemizel
 * @copyright (C) 2019 mm1 Technology GmbH - all rights reserved.
 * @licence MIT licence
 *
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
 */
#ifndef LED_h_
#define LED_h_

#include <Arduino.h>

class LED {
    private:
    int digitalPinNumber;

    public:
    LED();
    LED(int digitalPinNumber);
    void setupLED(int);
    void ledOn();
    void ledOff();
    void ledBlink();
};

#endif
