/*
 Name:		Robot.ino
 Created:	08.12.2017 0:59:48
 Author:	Yozka
*/
#include "rtMotor.h"

AMotor motor;

// the setup function runs once when you press reset or power the board
void setup() 
{
	//digitalWrite(0, 0);
	motor.begin();
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	motor.speed(100, 100);
	motor.stop();
	motor.speedM1(100);
	motor.speedM2(-100);

}
