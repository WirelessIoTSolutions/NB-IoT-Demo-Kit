/**
 * @file led.cpp
 * @description Functions to drive the OLED display
 * @author htemizel
 * @copyright (C) 2019 mm1 Technology GmbH - all rights reserved.
 * @licence MIT licence
 *
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
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
