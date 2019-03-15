//make sure to connect the OLED Screen to I2C

#include <Wire.h>
#include "SeeedOLED.h"

SeeedOLED SeeedOled;
 
void setup() {

  Wire.begin();
  SeeedOled.setupOLED();
  
}

void loop() {
 /*
  * use this function to print on the OLED Screen
  * first parameter is either String, Int, Char[], Float, Double
  * second and third parameters are Row and Column of where to print it
  */
  SeeedOled.printOLED("Test OLED", 0, 0);
  
  delay(3000);
  SeeedOled.clearDisplay();
}

