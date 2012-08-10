#include "trmPrint.h"
#include "../../Device/devHardware.h"
//---------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Constructor																		*
* //------------------------------------------------------------------------------------*
*///
AtrmPrint :: AtrmPrint()
{
	
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // Возвратим название команды для интерпритатора										*
* //------------------------------------------------------------------------------------*
*///
void AtrmPrint :: getCommandName(char * outName)
{
	strCopyPgm(outName, TEXT("print"));
}
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // проверка и выполнение команды														*
* //------------------------------------------------------------------------------------*
*///
bool AtrmPrint :: isExecute(const char* cmdName, const int argc, char * const argv[], AStream *stream)
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
void AtrmPrint :: help(AStream *stream)
{
	stream->printPgm(TEXT("print   - out variable."));
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // Обработка команды вывода информации												*
* //------------------------------------------------------------------------------------*
*///
void AtrmPrint :: execute(const int argc, char * const argv[], AStream *stream)
{
	if (argc == 1)
	{
		helpParametrs(stream);
		return;
	}
	char* valuesName = argv[1];
	
	//признак того что нужно зациклевать данные
	bool boLoop = false;
	if (argc > 2 && strComparePgm(argv[2], TEXT("l")))
	{
		boLoop = true;
	}
	
	//выполнение команды
	if (is_ADC	(valuesName, boLoop, stream)) return;
	if (is_time	(valuesName, boLoop, stream)) return;	

	//
	stream->write('\'');
	stream->print(valuesName);
	stream->printPgm(TEXT("' was not declared"));
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // вывод всех доступных параметров переменных											*
* //------------------------------------------------------------------------------------*
*///
void AtrmPrint :: helpParametrs(AStream *stream)
{
	stream->printPgm(TEXT("Print parameters:"));

	AProxyTerminal::sendEnter(stream);
	stream->printPgm(TEXT("adc [l]"));
	
	AProxyTerminal::sendEnter(stream);
	stream->printPgm(TEXT("time [l]"));
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // вывод в поток данных с АЦП															*
* //------------------------------------------------------------------------------------*
*///
bool AtrmPrint :: is_ADC(const char* valuesName, const bool boLoop, AStream *stream)
{
	if (!strComparePgm(valuesName, TEXT("adc")))
	{
		return false;
	}
	
	AHardware * hw = ptrHardware;
	bool boNext = true;
	while (boNext)
	{	
		printADC(TEXT("ADC0"), hw->adc.getADC(channelADC0), hw->adc.getMillivolt(channelADC0), stream);
		printADC(TEXT("ADC1"), hw->adc.getADC(channelADC1), hw->adc.getMillivolt(channelADC1), stream);
		printADC(TEXT("ADC2"), hw->adc.getADC(channelADC2), hw->adc.getMillivolt(channelADC2), stream);
		printADC(TEXT("ADC3"), hw->adc.getADC(channelADC3), hw->adc.getMillivolt(channelADC3), stream);
		printADC(TEXT("ADC6"), hw->adc.getADC(channelADC6), hw->adc.getMillivolt(channelADC6), stream);
		
		boNext = boLoop;
		if (boLoop)
		{
			if (stream->isRead())
			{
				BYTE data = stream->read();
				if (data == KEY_CR)
				{
					break;
				}
			}				
			//перейдем на 5 строчки выше чтобы затереть старые данные
			AProxyTerminal::sendCursorUP(5, stream);
			hw->updateProcess();
		}
	}

	return true;
}	
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Вывод данных с АЦП одной строчкой													*
* //------------------------------------------------------------------------------------*
*///
void AtrmPrint :: printADC(const char* name, const int data, const int mvolt, AStream *stream)
{
	char szBuffer[10];
	AProxyTerminal::sendClearRight(stream);
	stream->printPgm(name);
	
	zeroMemory((BYTE*)szBuffer, 10);
	strFromInt(szBuffer, data);
	stream->write('\t');
	stream->print(szBuffer);
	
	zeroMemory((BYTE*)szBuffer, 10);
	strFromIntDigit(szBuffer, mvolt, 3);
	stream->write('\t');
	stream->print(szBuffer);

	AProxyTerminal::sendEnter(stream);
}


//---------------------------------------------------------------------------------------


/* //===================================================================================*
* //                                                                                    *
* // вывод временных тиков																*
* //------------------------------------------------------------------------------------*
*///
bool AtrmPrint :: is_time(const char* valuesName, const bool boLoop, AStream *stream)
{
	if (!strComparePgm(valuesName, TEXT("time")))
	{
		return false;
	}
	
	char szBuffer[10];
	AHardware * hw = ptrHardware;
	bool boNext = true;
	while (boNext)
	{
		stream->printPgm(TEXT("time "));
		zeroMemory((BYTE*)szBuffer, 10);
		strFromInt(szBuffer, hw->time.getTime());
		stream->print(szBuffer);
		AProxyTerminal::sendClearRight(stream);
		AProxyTerminal::sendEnter(stream);
		
		boNext = boLoop;
		if (boLoop)
		{
			if (stream->isRead())
			{
				BYTE data = stream->read();
				if (data == KEY_CR)
				{
					break;
				}
			}
			//перейдем на 4 строчки выше чтобы затереть старые данные
			AProxyTerminal::sendCursorUP(1, stream);
			hw->updateProcess();
		}
	}
	
	
	
	return true;
}