//make sure to connect the magneticSwitch to one of the Digital PINS
#include "magneticSwitch.h"

MagneticSwitch mag1(D4);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
    if(mag1.isButtonPressed())
      Serial.print("BTN Event");
    delay(100);
}


