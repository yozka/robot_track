#include "rtMotor.h"

AMotor motor;


void setup() 
{
	motor.begin();

}


void loop() 
{
	motor.setSpeed(400, 400);
	delay(5000);
	motor.setSpeed(-200, -200);
	delay(2000);
}
