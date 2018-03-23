#include "rtLineSensor.h"
#include "rtMotor.h"

AMotor motor; //моторы
ALineSensor line; //датчики линии

void setup() 
{
	  motor.begin();
	  line.begin();
}

void loop() 
{
    motor.setSpeed(400, 400);
    line.left();
    line.center();
    line.right();
}

