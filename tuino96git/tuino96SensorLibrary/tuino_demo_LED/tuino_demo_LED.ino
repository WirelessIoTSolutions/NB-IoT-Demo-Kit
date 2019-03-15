//make sure to connect the LED to one of the digital PINS
#include "led.h"

LED led1(4);

void setup() {

}

void loop() {
    led1.ledOn();
    delay(2000);
    led1.ledOff();
    delay(2000);
}
