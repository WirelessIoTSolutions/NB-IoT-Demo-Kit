//make sure to connect the sensor to one of the I2C PINS
#include "Accelerometer_Compass_LSM303D.h"
#include <Wire.h>
#include <SPI.h>

LSM303D Lsm303d;

void setup()
{
    Serial.begin(9600);  // Serial is used for debugging
    Lsm303d.initI2C();
}

void loop()
{
    Serial.println(Lsm303d.getXAxisAcceleration());
    Serial.println(Lsm303d.getYAxisAcceleration());
    Serial.println(Lsm303d.getZAxisAcceleration());
    Serial.println(Lsm303d.getAngleMagNorthANDXAxis());
    delay(2000);
}
