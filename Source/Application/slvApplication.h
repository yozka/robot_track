#pragma once
#include "../Device/devHardware.h"
#include "Terminal/slvTerminal.h"
#include "Command/slvCommand.h"
#include "Display/slvDisplay.h"
//---------------------------------------------------------------------------------------



enum eMove
{
	moveStart,
	moveCalibration,
	moveForward,
	moveBackWait,
	moveBack,
	moveForwardWait	
};



/* //===================================================================================*
* //                                                                                    *
* // Программная логика контроллера независищая от железа								*
* //------------------------------------------------------------------------------------*
*///
class
	AApplication
{
	public:
		AApplication ();


		void initialization(AHardware &hardware);	//инциализация программы
		void update(const ATime &time, AHardware &hardware);	//обновление рабочей логики программы

	private:
	
	
		AStream *stream;

		ASlaveCommand	slaveCommand;	//обработка команд от мастера
		ATerminal		terminal;		//сдесь находится обработчик терминала
		ADisplay		display;		//дисплей
		
		
		int mamps;
		eMove move;
		int timeWait;
	};
