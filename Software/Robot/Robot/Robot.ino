#include "rtMotor.h"
#include <hcsr04.h>

AMotor motor;
HCSR04 hcsr04(13, A0, 20, 4000);

bool r = false;
bool fr = false;

void setup() 
{
	motor.begin();
	Serial.begin(9600);
	
}


void loop() 
{
	/*
	motor.setSpeed(400, 400);
	delay(5000);
	motor.setSpeed(0, 0);
	delay(2000);
	*/

	int d = hcsr04.distanceInMillimeters();
	if (d > 100)
	{
		int sp = map(d, 100, 400, 200, 400);
		motor.setSpeed(-sp, -sp);
		if (!fr)
		{
			fr = true;
			r = !r;
		}
	}
	else
	{
		
		if (r)
		{
			motor.setSpeed(-400, 400);
		}
		{
			motor.setSpeed(400, -400);
		}
		fr = false;
	}

}
