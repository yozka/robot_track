#pragma once
#include "../../resource.h"
#include "../../Protocol/prtProtocol.h"
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Вывод статистики по внтренне время контроллера										*
* //------------------------------------------------------------------------------------*
*///
class
	AtrmTime

{
	public:
		AtrmTime ();

		bool isExecute(const char* cmdName, const int argc, char * const argv[], AStream *stream);//проверка и выполнение команды
		void getCommandName(char * outName);//Возвратим название команды для интерпритатора
		void execute(const int argc, char * const argv[], AStream *stream);//выполнение команды
		void help(AStream *stream);//вывод справки помощи

	protected:



	
	
};
