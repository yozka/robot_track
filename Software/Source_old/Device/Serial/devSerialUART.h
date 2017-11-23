#pragma once
#include "../devSettings.h"
#include "../../Protocol/prtStream.h"
#include "devFIFO.h"
//---------------------------------------------------------------------------------------












/* //===================================================================================*
* //                                                                                    *
* // Физическая реализация двухпроводного протокола										*
* // внимание! используется привязка одного экземпляра объекта к только					*
* // к одному прерыванию																*
* //------------------------------------------------------------------------------------*
*///
class
	ASerialUART 
		: 
			public AStream
{
	public:
		ASerialUART ();


		void initialization(); //инциализация системы


		void isrUDREhandle();//Обработчик прерывания, данные успешно отправленны
		void isrRXhandle();//прерывание по завершению приема
	
	
		void setBaudRate(const DWORD dwBaud);//Установка скорости передачи данных
	

	protected:

		bool onIsRead() const; //проверка, есть данные для чтения или нет
		BYTE onRead();//чтение данных из порта
		bool onWrite(const BYTE data);//запись данных в поток

	
	private:

		//внутренние буферы для чтения записи данных
		AFIFO m_read;
		AFIFO m_write;
	
		volatile bool m_readLock;//блокировка буфера на чтение данных
		volatile bool m_writeLock;//блокировка буфера на запись данных

		inline void enableTxInterrupt();//включение прерывания на прием данных
		inline void disableTxInterrupt();//отключение прерывания на прием данных

};
