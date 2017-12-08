#pragma once
#include <Arduino.h>
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
namespace Setting
{
	//��������� �����
	const unsigned char motor1_dir = 7;
	const unsigned char motor2_dir = 8;
	const unsigned char motor1_pwm = 9;
	const unsigned char motor2_pwm = 10;
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
	~AMotor(); 	//destructor


	void begin		(); //��������� �������
	void setSpeed1	(const int speed); //��������� �������� ��� ��������� 1
	void setSpeed2	(const int speed); //��������� �������� ��� ��������� 2
	void setSpeed	(const int speed1, const int speed2); //��������� ��������
	void stop		();//������ ���������

};