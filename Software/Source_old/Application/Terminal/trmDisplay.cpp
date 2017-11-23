#include "trmDisplay.h"
#include "../../Device/devHardware.h"
//---------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Constructor																		*
* //------------------------------------------------------------------------------------*
*///
AtrmDisplay :: AtrmDisplay()
{
	
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // Возвратим название команды для интерпритатора										*
* //------------------------------------------------------------------------------------*
*///
void AtrmDisplay :: getCommandName(char * outName)
{
	strCopyPgm(outName, TEXT("display"));
}
//---------------------------------------------------------------------------------------








/* //===================================================================================*
* //                                                                                    *
* // проверка и выполнение команды														*
* //------------------------------------------------------------------------------------*
*///
bool AtrmDisplay :: isExecute(const char* cmdName, const int argc, char * const argv[], AStream *stream)
{
	char szName[MAX_TERMINAL_BUFFER];
	getCommandName(szName);
	if (strCompare(cmdName, szName))
	{
		execute(argc, argv, stream);
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // вывод справки помощи																*
* //------------------------------------------------------------------------------------*
*///
void AtrmDisplay :: help(AStream *stream)
{
	stream->printPgm(TEXT("display - show status led matrix."));
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // Обработка команды display															*
* //   display - если нет параметров то выводим матрицу дисплея                         *
* //   display 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 - заполнение дисплея значениями  *
* //   display число - покажем число                                                    *
* //------------------------------------------------------------------------------------*
*///
void AtrmDisplay :: execute(const int argc, char * const argv[], AStream *stream)
{
	switch (argc)
	{
		case 1:
			//параметров нет, покажем просто матрицу дисплея
			showLedMatrixData(stream);
			break;
			
		case 1 + 8:
			//8 параметров, зажгем матрицу
			setLedMatrixData(argv, stream);
			break;
			
			
		
		default:
			stream->printPgm(TEXT("Error parametrs."));
	}
	
	
	//AProxyTerminal::sendEnter(stream);
}
//---------------------------------------------------------------------------------------








/* //===================================================================================*
* //                                                                                    *
* // выведем данные матрицы																*
* //------------------------------------------------------------------------------------*
*///
void AtrmDisplay :: showLedMatrixData(AStream *stream)
{
	AHardware * hardware = ptrHardware;
	for (int i = 0; i < 8; i++)
	{
		//Цикл по линиям
		BYTE data = hardware->ledMatrix.getLine(i);
		for (int j = 0; j < 8; j++)
		{
			//данные по битово
			if (data & 0b10000000)
			{
				stream->write('#');
			}
			else
			{
				stream->write('.');
			}
			data = data << 1;	
		}
		if (i < 7)
		{
			AProxyTerminal::sendEnter(stream);
		}			
	}
}
//---------------------------------------------------------------------------------------








/* //===================================================================================*
* //                                                                                    *
* // заполним матрицу символами															*
* //------------------------------------------------------------------------------------*
*///
void AtrmDisplay :: setLedMatrixData(char * const argv[], AStream *stream)
{
	bool l1,l2,l3,l4,l5,l6,l7,l8;
	BYTE d1 = hexToInt(argv[1], &l1);
	BYTE d2 = hexToInt(argv[2], &l2);
	BYTE d3 = hexToInt(argv[3], &l3);
	BYTE d4 = hexToInt(argv[4], &l4);
	BYTE d5 = hexToInt(argv[5], &l5);
	BYTE d6 = hexToInt(argv[6], &l6);
	BYTE d7 = hexToInt(argv[7], &l7);
	BYTE d8 = hexToInt(argv[8], &l8);
	if (!l1 && !l2 && !l3 && !l4 && !l5 && !l6 && !l7 && !l8)
	{
		AHardware * h = ptrHardware;
		h->ledMatrix.setLine(0, d1);
		h->ledMatrix.setLine(1, d2);
		h->ledMatrix.setLine(2, d3);
		h->ledMatrix.setLine(3, d4);
		h->ledMatrix.setLine(4, d5);
		h->ledMatrix.setLine(5, d6);
		h->ledMatrix.setLine(6, d7);
		h->ledMatrix.setLine(7, d8);
		showLedMatrixData(stream);
	}
	else
	{
		stream->printPgm(TEXT("Parametr error"));
	}		
		
}
//---------------------------------------------------------------------------------------







