#pragma once
#include "../../resource.h"
#include "../../Protocol/prtProtocol.h"
#include "trmDisplay.h"
#include "trmPower.h"
#include "trmMotors.h"
#include "trmTime.h"
#include "trmPrint.h"
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Интерфес терминала, обработка входящих данных и выполнение введеной команды		*
* //------------------------------------------------------------------------------------*
*///
class
	ATerminal
		:
		public AProxyTerminal
{
	public:
		ATerminal ();



	protected:

		virtual void onInterpretation(const int argc, char * const argv[], AStream *stream);//Обработка команды

	private:

		void help(AStream *stream);//вывод справку по командам
	
		//обработчик команд
		AtrmDisplay trmDisplay;
		AtrmPower	trmPower;
		AtrmMotors	trmMotors;
		AtrmTime	trmTime;
		AtrmPrint	trmPrint;
};
