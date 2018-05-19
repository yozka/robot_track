#pragma once
#include <Arduino.h>
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
namespace Setting
{
	//��������� �����
	const unsigned char pinBumperA = PD3;
	const unsigned char pinBumperB = PD5;
}
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
#ifndef FAction
	using FAction = void(*)();	//��������
#endif
//-----------------------------------------------------------------------------




 ///---------------------------------------------------------------------------
///
/// ������ �������
///
///----------------------------------------------------------------------------
	class ABumperSensor
	{
	public:

		ABumperSensor();			//constructor
		virtual ~ABumperSensor(); 	//destructor


		void begin(); //���������


		bool left()const;	//����� ������
		bool right()const;	//������ ������

		mutable FAction signal_detect = { nullptr };
		void update(); //����������


	private:
		bool mLeft = { false };
		bool mRight = { false };


		byte mFLeft = { 0 };
		byte mFRight = { 0 };

	
	unsigned long mTimeLeft;



};


extern ABumperSensor bumper;