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

};


extern ALineSensor line;