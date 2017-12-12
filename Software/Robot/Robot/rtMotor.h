#pragma once
#include <Arduino.h>
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
namespace Setting
{
	//настройка ножек
	const unsigned char motor1_dir = 7;
	const unsigned char motor2_dir = 8;
	const unsigned char motor1_pwm = 9;
	const unsigned char motor2_pwm = 10;
}
//-----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// Система моторов
///
///----------------------------------------------------------------------------
class AMotor
{
public:
	
	AMotor(); //constructor
	~AMotor(); 	//destructor


	void begin		(); //настройка моторов
	void setSpeed1	(const int speed); //установка скорости для двигателя 1
	void setSpeed2	(const int speed); //установка скорости для двигателя 2
	void setSpeed	(const int speed1, const int speed2); //установка скорости
	void stop		();//полная остановка

};