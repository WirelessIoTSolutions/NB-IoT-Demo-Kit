//make sure to connect the lightsensor to one of the analog PINS
#include "lightSensor.h"

LightSensor li1(A3);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
    int lum = li1.getLightAmountiinLumen();
    Serial.print("Lichtmenge in Lumen: ");
    Serial.println(lum);
    delay(1000);

    float lux = li1.getLightAmountiinLux();
    Serial.print("Lichtmenge in Lux: ");
    Serial.println(lux);
    delay(1000);

}


