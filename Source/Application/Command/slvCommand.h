﻿#pragma once
#include "../../resource.h"
#include "../../Protocol/prtProtocol.h"
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Интерфес обработки команд подчиненого												*
* //------------------------------------------------------------------------------------*
*///
class
	ASlaveCommand
		:
			public AProxyCommand
{
	public:
		ASlaveCommand ();



	private:
		//virtual bool onExecute(BYTE data, AStream *stream);//Обработка и выделение командной строки


	

};
