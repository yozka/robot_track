#include "rtMotor.h"

AMotor motor;

void setup() 
{
	motor.begin();


	motor.speed(100, 100);
	motor.stop();
	motor.speedM1(100);
	motor.speedM2(-100);

}

void loop() 
{
}
