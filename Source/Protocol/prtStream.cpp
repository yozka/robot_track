﻿#include "prtStream.h"
#include "../Device/devHardware.h"
//---------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Constructor																		*
* //------------------------------------------------------------------------------------*
*///
AStream :: AStream()
{
	
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // вывод строчки в поток																*
* //------------------------------------------------------------------------------------*
*///
void AStream :: print(char * const pString)
{
	if (pString)
	{
		char * s = pString;
		while (*s)
		{
			write(*s);
			s++;
		}
	}		
}
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Вывод строчки в поток из программной памяти										*
* //------------------------------------------------------------------------------------*
*///
#ifdef AVR
void AStream :: printPgm(const char * pString)
{
	char temp = pgm_read_byte(pString);
	while (temp)
	{
		write(temp);
		pString++;
		temp = pgm_read_byte(pString);
	}
}	
#endif // AVR
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // проверка на наличе данных для чтения												*
* //------------------------------------------------------------------------------------*
*///
bool AStream :: isRead() const
{
	return onIsRead();
}
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // чтение данных из потока															*
* //------------------------------------------------------------------------------------*
*///
BYTE AStream :: read() 
{
	return onRead();
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // Запись данных в поток																*
* //------------------------------------------------------------------------------------*
*///
bool AStream :: write(const BYTE data)
{
	AHardware *hardware = ptrHardware;
	DWORD dwError = 100000;
	//количество попыток при записи, нужно чтобы был освобожден буфер
	while (!onWrite(data) && dwError)
	{
		dwError--;
		hardware->updateProcess();
	}
	return dwError ? false : true;
	
}


