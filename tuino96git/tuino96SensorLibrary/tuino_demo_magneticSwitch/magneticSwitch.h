#ifndef LED_h_
#define LED_h_

#include <Arduino.h>

class MagneticSwitch {
    private:
    int digitalPinNumber;
    
    public:
    MagneticSwitch::MagneticSwitch(int digitalPinNumber);
    bool MagneticSwitch::isButtonPressed();
};

#endif



