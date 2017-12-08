﻿#include "trmTime.h"
#include "../../Device/devHardware.h"
//---------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Constructor																		*
* //------------------------------------------------------------------------------------*
*///
AtrmTime :: AtrmTime()
{
	
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // Возвратим название команды для интерпритатора										*
* //------------------------------------------------------------------------------------*
*///
void AtrmTime :: getCommandName(char * outName)
{
	strCopyPgm(outName, TEXT("time"));
}
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // проверка и выполнение команды														*
* //------------------------------------------------------------------------------------*
*///
bool AtrmTime :: isExecute(const char* cmdName, const int argc, char * const argv[], AStream *stream)
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
void AtrmTime :: help(AStream *stream)
{
	stream->printPgm(TEXT("time    - system timer."));
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // Обработка команды power															*
* //------------------------------------------------------------------------------------*
*///
void AtrmTime :: execute(const int argc, char * const argv[], AStream *stream)
{
	stream->printPgm(TEXT("System timer:"));
	AHardware *hardware = ptrHardware;
	char szBuffer[10];
	
	//текущее время
	zeroMemory((BYTE*)szBuffer, 10);
	strFromDWORD(szBuffer, hardware->time.getTimeMS());
	AProxyTerminal::sendEnter(stream);
	stream->printPgm(TEXT(" Count tick = "));
	stream->print(szBuffer);
}
//---------------------------------------------------------------------------------------









