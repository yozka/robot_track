#pragma once
#include "../resource.h"
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Интерфейс потока который реализует обмен между устройствами						*
* //------------------------------------------------------------------------------------*
*///
class
	AStream
{
	public:
		AStream ();

		bool isRead() const; //проверка на наличе данных для чтения

		void print(char * const pString);//вывод строчки в поток
		bool write(const BYTE data);//Запись данных в поток
		BYTE read();//чтение данных из потока


		#ifdef AVR
		void printPgm(const char * pString);//Вывод строчки в поток из программной памяти
		#endif // AVR

	protected:
		virtual bool onWrite(const BYTE data){return false;};//запись данных в поток
		virtual BYTE onRead(){return 0;};//чтение данных из потока 
		virtual bool onIsRead() const {return false;}//проверка, есть данные для чтения или нет
		

	
};
