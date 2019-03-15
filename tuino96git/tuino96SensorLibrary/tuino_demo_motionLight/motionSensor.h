#ifndef MOTIONSENSOR_h_
#define MOTIONSENSOR_h_

#include <Arduino.h>


class MotionSensor {
    private:
    int digitalPinNumber;
    
    public:
    MotionSensor(int digitalPinNumber);
    bool isMotionDetected();
};

#endif
