#include "magneticSwitch.h"

MagneticSwitch::MagneticSwitch(int digitalPinNumber) {
    this->digitalPinNumber = digitalPinNumber;
    pinMode(this->digitalPinNumber, INPUT);
}

bool MagneticSwitch::isButtonPressed(){
    bool buttonState = digitalRead(this->digitalPinNumber);
    delay(300);
    return buttonState;
}
