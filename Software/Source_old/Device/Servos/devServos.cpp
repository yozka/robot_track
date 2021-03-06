﻿#include "devServos.h"
#include "../devHardware.h"
#include "../ADConverter/devADConverter.h"
#include <avr/interrupt.h>
//---------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------
/* сервоприводы повешаны на PD4 PD7
*/
#define SERVO_A		PORTD4
#define SERVO_B		PORTD7
#define SERVOPORT	PORTD



int _c = 0;
int _d = 0;

ISR(TIMER1_COMPB_vect)
{
	/* 0.0005 сек
	 * лево 0.8мс центр 1.5мс 2.3мс
	 *	0.0008 
	 *	0.0015
	 *  0.0023
	*/
	//OCR1B += TIME_OCR_SERVO;	//0.00005сек
								//0.01500
	
	OCR1B += 16;
	
	if (_c == 0)
	{
		_c++;
		_d = 0;
		SERVOPORT |= 1 << SERVO_B;
		return;
	}
	
	if (_d)
	{
		_d++;
		if (_d > 200)
		{
			_c = 0;
			_d = 0;
		}
		return;
	}
	
	_c++;
	if (_c > 150)
	{
		SERVOPORT &= ~(1 << SERVO_B);
		_d = 1;
	}		


}






/* //===================================================================================*
* //                                                                                    *
* // Constructor																		*
* //------------------------------------------------------------------------------------*
*///
AServo :: AServo()
	:
	m_positionA(0),
	m_positionB(0)
{
	
}
//---------------------------------------------------------------------------------------









/* //===================================================================================*
* //                                                                                    *
* // Инциализация батарей																*
* //------------------------------------------------------------------------------------*
*///
void AServo :: initialization()
{
	//переключим пины порта на вывод данных
	DDRD |= 1 << SERVO_A;
	DDRD |= 1 << SERVO_B;
		
	SERVOPORT &= ~(1 << SERVO_A);
	SERVOPORT &= ~(1 << SERVO_B);
	
	tt= 0;
}
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // системное обновелине мониторинга питания											*
* //------------------------------------------------------------------------------------*
*///
void AServo :: update(const ATime &time)
{
	if (tt)
	{
		SERVOPORT |= 1 << SERVO_A;
		tt = 0;
	}
	else
	{
		SERVOPORT &= ~(1 << SERVO_A);
		tt =1;
	}		
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // возвратим напряжение батарейки в миливольтах										*
* //------------------------------------------------------------------------------------*
*///
/*
int AServo :: getBatteryVoltage() const
{
	return m_batt;
}
*/
//---------------------------------------------------------------------------------------





/* //===================================================================================*
* //                                                                                    *
* // Минимальное напряжение батарейки													*
* //------------------------------------------------------------------------------------*
*///
/*
int AServo :: getBatteryVoltageMin() const
{
	return m_battMin;
}
*/
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // Максимально зафиксированное напряжение батарейки									*
* //------------------------------------------------------------------------------------*
*///
/*
int AServo :: getBatteryVoltageMax() const
{
	return m_battMax;
}
*/
//---------------------------------------------------------------------------------------




