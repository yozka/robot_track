#pragma once
#include "../../resource.h"
#include "../../Protocol/prtProtocol.h"
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Вывод пееременных и служебной информации											*
* //------------------------------------------------------------------------------------*
*///
class
	AtrmPrint

{
	public:
		AtrmPrint ();

		bool isExecute(const char* cmdName, const int argc, char * const argv[], AStream *stream);//проверка и выполнение команды
		void getCommandName(char * outName);//Возвратим название команды для интерпритатора
		void execute(const int argc, char * const argv[], AStream *stream);//выполнение команды
		void help(AStream *stream);//вывод справки помощи

	protected:

		void helpParametrs(AStream *stream);//вывод всех доступных параметров переменных

	private:
		bool is_ADC(const char* valuesName, const bool boLoop, AStream *stream);//вывод в поток данных с АЦП
		bool is_time(const char* valuesName, const bool boLoop, AStream *stream);//вывод системных тиков
	
	
		void printADC(const char* name, const int data, const int mvolt, AStream *stream);//Вывод данных с АЦП одной строчкой
};
