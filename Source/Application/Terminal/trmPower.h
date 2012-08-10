#pragma once
#include "../../resource.h"
#include "../../Protocol/prtProtocol.h"
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Терминальная команда работающая с батарейками и зарядкой							*
* //------------------------------------------------------------------------------------*
*///
class
	AtrmPower

{
	public:
		AtrmPower ();

		bool isExecute(const char* cmdName, const int argc, char * const argv[], AStream *stream);//проверка и выполнение команды
		void getCommandName(char * outName);//Возвратим название команды для интерпритатора
		void execute(const int argc, char * const argv[], AStream *stream);//выполнение команды
		void help(AStream *stream);//вывод справки помощи

	protected:


		void printDigit(const char* sCaption, const int val, AStream *stream);//отправка подписанных значений с плавающей запятой
		void print(const char* sCaption, const int val, AStream *stream);//отправка подписанных значений
	
	
		bool setOptions(const int argc, char * const argv[], AStream *stream);//Установка параметров
};
