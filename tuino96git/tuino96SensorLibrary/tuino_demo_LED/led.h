/**
 * @file led.h
 * @description Functions to drive the OLED display
 * @author htemizel
 * @copyright (C) 2019 WIOTS GmbH - all rights reserved.
 * @licence MIT licence
 *
 * Find out more about WIOTS:
 * Company: https://wireless-iot-solutions.com/wp/
 * GitHub:  https://github.com/WirelessIoTSolutions/
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
