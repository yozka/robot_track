#pragma once
#include "../../resource.h"
#include "../../Protocol/prtProtocol.h"
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Обработка команды терминала работающие с десплеем									*
* //------------------------------------------------------------------------------------*
*///
class
	AtrmDisplay

{
	public:
		AtrmDisplay ();

		bool isExecute(const char* cmdName, const int argc, char * const argv[], AStream *stream);//проверка и выполнение команды
		void getCommandName(char * outName);//Возвратим название команды для интерпритатора
		void execute(const int argc, char * const argv[], AStream *stream);//выполнение команды
		void help(AStream *stream);//вывод справки помощи
	protected:


		void showLedMatrixData(AStream *stream);//выведем данные матрицы
		void setLedMatrixData(char * const argv[], AStream *stream);//заполним матрицу символами

	
	
};
