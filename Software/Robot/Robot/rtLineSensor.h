#pragma once
#include <Arduino.h>
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
namespace Setting
{
	//настройка пинов
	const unsigned char pinLineSensorA = 12;
	const unsigned char pinLineSensorB = 8;
	const unsigned char pinLineSensorC = 7;
}
//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------
#ifndef FAction
  using FAction = void(*)();  //действие
#endif
//-----------------------------------------------------------------------------





 ///---------------------------------------------------------------------------
///
/// Датчик линий
///
///----------------------------------------------------------------------------
class ALineSensor
{
public:

	ALineSensor();				//constructor
	virtual ~ALineSensor(); 	//destructor


	void begin(); //настройка
	

	bool left()const;	//левый сенсор
	bool center()const; //центральный сенсор
	bool right()const;	//правый сенсор

  mutable FAction signal_detect = { nullptr };
  void update(); //обновление

private:
    bool mLeft    = { false };
    bool mCenter  = { false };
    bool mRight   = { false };


    byte mFLeft   = { 0 };
    byte mFCenter = { 0 };
    byte mFRight  = { 0 };

};


extern ALineSensor line;
