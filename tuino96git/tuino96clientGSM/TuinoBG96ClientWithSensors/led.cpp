/**
 * @file led.cpp
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
#include "led.h"

LED::LED() {
    
}

LED::LED(int digitalPinNumber) {
    this->digitalPinNumber = digitalPinNumber;
    pinMode(this->digitalPinNumber, OUTPUT);
}

void LED::ledOn(){
  // set the LED on
  digitalWrite(this->digitalPinNumber, HIGH);
}

void LED::ledOff(){
  // set the LED on
  digitalWrite(this->digitalPinNumber, LOW);
}

void LED::ledBlink(){
    digitalWrite(this->digitalPinNumber, HIGH);
    delay(500);               
    digitalWrite(this->digitalPinNumber, LOW);
    delay(500);  
}
