﻿#pragma once
#include "../devSettings.h"
#include "../devTime.h"
//-------------------------------------------------------------------------------------//






/* //===================================================================================*
* //                                                                                    *
* // Двигатели																			*
* //------------------------------------------------------------------------------------*
*///
class
	AMotors
{
	public:
		AMotors();//constructor


		void initialization();//Инциализация двигателей

		void setSpeedM1(const int iSpeed);//Устанавливаем скорость движения левого двигателя -255 255
		void setSpeedM2(const int iSpeed);//Устанавливаем скорость движения правого двигателя

		int getSpeedM1()const;//Возвратим скорость мотора 1
		int getSpeedM2()const;//Возвратим скорость мотора 2
	private:
		
		int m_motor1;
		int m_motor2;

		int correct(const int iSpeed) const;//устанавливаем корректность диапазаона моторов
};

//-------------------------------------------------------------------------------------//
