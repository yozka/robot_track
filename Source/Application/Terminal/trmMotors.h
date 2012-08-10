#pragma once
#include "../../resource.h"
#include "../../Protocol/prtProtocol.h"
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Обработка команды работы с моторами												*
* //------------------------------------------------------------------------------------*
*///
class
	AtrmMotors

{
	public:
		AtrmMotors ();

		bool isExecute(const char* cmdName, const int argc, char * const argv[], AStream *stream);//проверка и выполнение команды
		void getCommandName(char * outName);//Возвратим название команды для интерпритатора
		void execute(const int argc, char * const argv[], AStream *stream);//выполнение команды
		void help(AStream *stream);//вывод справки помощи

	protected:


		void statusMotors(AStream *stream);//Покажем состояние моторов

	
	
};
