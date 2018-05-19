#pragma once
#include <Arduino.h>
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
namespace Setting
{
	//��������� �����
	const unsigned char pinLineSensorA = 12;
	const unsigned char pinLineSensorB = 8;
	const unsigned char pinLineSensorC = 7;
}
//-----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// ������ �����
///
///----------------------------------------------------------------------------
class ALineSensor
{
public:

	ALineSensor();				//constructor
	virtual ~ALineSensor(); 	//destructor


	void begin(); //���������
	

	bool left()const;	//����� ������
	bool center()const; //����������� ������
	bool right()const;	//������ ������

};


extern ALineSensor line;