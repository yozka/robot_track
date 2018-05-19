#pragma once
#include <Arduino.h>
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
namespace Setting
{
	//настройка пинов
	const unsigned char pinBumperA = PD3;
	const unsigned char pinBumperB = PD5;
}
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
#ifndef FAction
	using FAction = void(*)();	//действие
#endif
//-----------------------------------------------------------------------------




 ///---------------------------------------------------------------------------
///
/// Датчик бампера
///
///----------------------------------------------------------------------------
	class ABumperSensor
	{
	public:

		ABumperSensor();			//constructor
		virtual ~ABumperSensor(); 	//destructor


		void begin(); //настройка


		bool left()const;	//левый бампер
		bool right()const;	//правый бампер

		mutable FAction signal_detect = { nullptr };
		void update(); //обновление


	private:
		bool mLeft = { false };
		bool mRight = { false };


		byte mFLeft = { 0 };
		byte mFRight = { 0 };

	
	unsigned long mTimeLeft;



};


extern ABumperSensor bumper;