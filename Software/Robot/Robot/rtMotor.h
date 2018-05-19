#pragma once
#include <Arduino.h>
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
namespace Setting
{
	//��������� �����
	const unsigned char pinMotor1_dir = 6;
	const unsigned char pinMotor2_dir = 11;
	const unsigned char pinMotor1_pwm = 9;
	const unsigned char pinMotor2_pwm = 10;
}
//-----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// ������� �������
///
///----------------------------------------------------------------------------
class AMotor
{
public:
	
	AMotor(); //constructor
	virtual ~AMotor(); 	//destructor


	void begin		(); //��������� �������
	void setSpeed1	(const int speed); //��������� �������� �� �������� 1
	void setSpeed2	(const int speed); //��������� �������� �� �������� 2
	void setSpeed	(const int speed1, const int speed2); //��������� ��������
	void stop		();//������ ���������

};


extern AMotor motor;