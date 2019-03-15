/**
 * @file Ultrasonic.h
 * @description Functions to drive the Seed Ultrasonic Ranger
 * @author FrankieChu
 * @reworker htemizel
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 */
#ifndef Ultrasonic_H
#define Ultrasonic_H

#include "Arduino.h"

class Ultrasonic
{
	public:
		Ultrasonic(int pin);
		long MeasureInCentimeters(void);
		long MeasureInInches(void);
	private:
		int _pin;//pin number of Arduino that is connected with SIG pin of Ultrasonic Ranger.
};

#endif
