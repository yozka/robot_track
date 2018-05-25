﻿#include "rtMotor.h"
///----------------------------------------------------------------------------



static AMotor motor;



 ///---------------------------------------------------------------------------
///
/// Constructor
///
///----------------------------------------------------------------------------
AMotor :: AMotor()
{

}
///----------------------------------------------------------------------------




 ///---------------------------------------------------------------------------
///
/// Destructor
///
///----------------------------------------------------------------------------
AMotor :: ~AMotor()
{

}
///----------------------------------------------------------------------------




 ///---------------------------------------------------------------------------
///
/// настройка моторов
///
///----------------------------------------------------------------------------
void AMotor :: begin()
{
	pinMode(Setting::pinMotor1_dir, OUTPUT);
	pinMode(Setting::pinMotor2_dir, OUTPUT);
	pinMode(Setting::pinMotor1_pwm, OUTPUT);
	pinMode(Setting::pinMotor2_pwm, OUTPUT);

	// PWM настройка шима
	// 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
	TCCR1A = 0b10100000;
	TCCR1B = 0b00010001;
	ICR1 = 400;
}
///----------------------------------------------------------------------------




 ///---------------------------------------------------------------------------
///
/// установка скорости для двигателя 1
///
///----------------------------------------------------------------------------
void AMotor :: setSpeed1(const int speed)
{
	bool reverse = false; //обратное кручение
	int sv = speed;

	//проверяем, если скорость меньше нуля, то нужно крутится в другую сторону
	if (sv < 0)
	{
		sv = -sv; // поставим скорость больше нулЯ (уберем знак минус)
		reverse = true;    // поставимм что нужно крутися в обратную сторону
	}

	//проверяем скорость, она не должна быть больше 400
	if (sv > 400)
	{
		sv = 400;
	}

	OCR1A = speed; //на шим установим скорость
	
	//сторона вращения
	if (reverse)
	{
		digitalWrite(Setting::pinMotor1_dir, LOW);
	}
	else
	{
		digitalWrite(Setting::pinMotor1_dir, HIGH);
	}
}
///----------------------------------------------------------------------------





 ///---------------------------------------------------------------------------
///
/// установка скорости для двигателя 2
///
///----------------------------------------------------------------------------
void AMotor :: setSpeed2(const int speed)
{
	bool reverse = false; //обратное кручение
	int sv = speed;

	//проверяем, если скорость меньше нулЯ, то нужно крутитсЯ в другую сторону
	if (sv < 0)
	{
		sv = -sv; // поставим скорость больше нулЯ (уберем знак минус)
		reverse = true;    // поставимм что нужно крутися в обратную сторону
	}

	//проверяем скорость, она не должна быть больше 400
	if (sv > 400)
	{
		sv = 400;
	}

	OCR1B = speed; //на шим установим скорость

	//сторона вращения
	if (reverse)
	{
		digitalWrite(Setting::pinMotor2_dir, LOW);
	}
	else
	{
		digitalWrite(Setting::pinMotor2_dir, HIGH);
	}
}
///----------------------------------------------------------------------------





 ///---------------------------------------------------------------------------
///
/// установка скорости
///
///----------------------------------------------------------------------------
void AMotor :: setSpeed(const int speed1, const int speed2)
{
	setSpeed1(speed1);
	setSpeed2(speed2);
}
///----------------------------------------------------------------------------




 ///---------------------------------------------------------------------------
///
/// полнаЯ остановка
///
///----------------------------------------------------------------------------
void AMotor :: stop()
{
	setSpeed1(0);
	setSpeed2(0);
}
