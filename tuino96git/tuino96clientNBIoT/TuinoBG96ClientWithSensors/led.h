/**
 * @file led.h
 * @description Functions to drive the OLED display
 * @author htemizel
 * @copyright (C) 2019 mm1 Technology GmbH - all rights reserved.
 * @licence proprietary licence - mm1 Technology grants all users of the mm1 Technology relay service 
 * the right to use this software for evaluation and testing. It is not allowed to use this software 
 * with any other service than the mm1 Technology relay service of copy or use this software into other 
 * projects than related to the mm1 Technology relay service.
 *
 * Find out more about WIOTS:
 * Company:     https://wireless-iot-solutions.com/wp/
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
