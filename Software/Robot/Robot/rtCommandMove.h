#pragma once
#include <Arduino.h>
#include "rtStateMachine.h"
#include "rtMotor.h"
//-----------------------------------------------------------------------------





 ///---------------------------------------------------------------------------
///
/// Команда движения вперед
///
///----------------------------------------------------------------------------
class ACommand_move
	:
		public SM::AStateObject
{
public:
	
	void onEnter()		override { motor.setSpeed(400, 400);};
	void onUpdate()		override {};
	void onExit()		override {};
	int	 onTimeActive() override { return 100; };

private:
};
//-----------------------------------------------------------------------------




 ///---------------------------------------------------------------------------
///
/// Команда поворот вправо
///
///----------------------------------------------------------------------------
class ACommand_moveRight
	:
		public SM::AStateObject
{
public:
	
	void onEnter()		override { motor.setSpeed(400, -200);};
	void onUpdate()		override {};
	void onExit()		override {};
	int	 onTimeActive() override { return 800; };

private:
};
//-----------------------------------------------------------------------------





 ///---------------------------------------------------------------------------
///
/// Команда поворот налево
///
///----------------------------------------------------------------------------
class ACommand_moveLeft
	:
	public SM::AStateObject
{
public:

	void onEnter()		override { motor.setSpeed(-200, 400); };
	void onUpdate()		override {};
	void onExit()		override {};
	int	 onTimeActive() override { return 800; };

private:
};
//-----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// Команда движения назад
///
///----------------------------------------------------------------------------
class ACommand_moveBack
	:
	public SM::AStateObject
{
public:

	void onEnter()		override { motor.setSpeed(-300, -300); };
	void onUpdate()		override {};
	void onExit()		override {};
	int	 onTimeActive() override { return 1000; };

private:
};
//-----------------------------------------------------------------------------








 ///---------------------------------------------------------------------------
///
/// Команда рандомного движения
///
///----------------------------------------------------------------------------
class ACommand_moveRandom
	:
	public SM::AStateObject
{
public:

	void onEnter() override { };
	
	void onUpdate() override 
	{
		const auto time = millis();
		if (time < mTime)
		{
			return;
		}
		motor.setSpeed(-300, -300);
	};
	
	void onExit() override { };
	
	int	 onTimeActive() override 
	{ 
		return 1000; 
	};

private:
	unsigned long mTime = { 0 };
};
//-----------------------------------------------------------------------------
