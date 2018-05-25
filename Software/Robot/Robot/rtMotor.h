#pragma once
#include <Arduino.h>
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
namespace Setting
{
	//настройка пинов
	const unsigned char pinMotor1_dir = 6;
	const unsigned char pinMotor2_dir = 11;
	const unsigned char pinMotor1_pwm = 9;
	const unsigned char pinMotor2_pwm = 10;
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
	virtual ~AMotor(); 	//destructor


	void begin		(); //настройка моторов
	void setSpeed1	(const int speed); //установка скорости дл¤ двигател¤ 1
	void setSpeed2	(const int speed); //установка скорости дл¤ двигател¤ 2
	void setSpeed	(const int speed1, const int speed2); //установка скорости
	void stop		();//полная остановка

};


extern AMotor motor;