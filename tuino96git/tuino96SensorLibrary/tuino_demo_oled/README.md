# tuino_demo_oled
Tuino application that demonstrates the usage of an OLED display.

## Setup
* Connect the OLED display with the I2C port of the Tuino.
* Connect the Tuino with a PC using the USB cable.
* Open this project with the Arduino IDE.
* Compile and upload the project to the Tuino.

## Feature(s)
The example shows a system uptime clock, i.e. it counts up the seconds since last startup. The display shows the total number of seconds, as well as a human readable clock using the format HH:MM:SS.

During initialisation (function setup()) the OLED will be prepared with a text mask which will not be changed anymore in normal operation. This is an optimsation step since the output on the display is slow enough to significantly delay the seconds counter. Therefore, only the counter and clock are printed to the display in normal operation (function loop()).

## Notes
The OLED library (see SeeedOLED.h) not only provides a character based interface, but also functions to print integers and floating point numbers.
