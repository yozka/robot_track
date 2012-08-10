#include "trmMotors.h"
#include "../../Device/devHardware.h"
//---------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Constructor																		*
* //------------------------------------------------------------------------------------*
*///
AtrmMotors :: AtrmMotors()
{
	
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // Возвратим название команды для интерпритатора										*
* //------------------------------------------------------------------------------------*
*///
void AtrmMotors :: getCommandName(char * outName)
{
	strCopyPgm(outName, TEXT("motors"));
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // проверка и выполнение команды														*
* //------------------------------------------------------------------------------------*
*///
bool AtrmMotors :: isExecute(const char* cmdName, const int argc, char * const argv[], AStream *stream)
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
void AtrmMotors :: help(AStream *stream)
{
	stream->printPgm(TEXT("motors  - control speed motors."));
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // Обработка команды моторов															*
* //------------------------------------------------------------------------------------*
*///
void AtrmMotors :: execute(const int argc, char * const argv[], AStream *stream)
{
	if (argc == 1)
	{
		//покажем статус моторов
		statusMotors(stream);
		return;
	}
	
	AHardware *hardware = ptrHardware;
	if (argc == 2)
	{
		//один параметр на два мотора
		bool boError = false;
		int speed = strToInt(argv[1], &boError);
		if (!boError)
		{
			hardware->motors.setSpeedM1(speed);
			hardware->motors.setSpeedM2(speed);
			statusMotors(stream);
			return;
		}			
	}
	
	if (argc == 3)
	{
		//два параметра на разные моторы
		bool boError1 = false;
		bool boError2 = false;
		int speed1 = strToInt(argv[1], &boError1);
		int speed2 = strToInt(argv[2], &boError2);
		if (!boError1 && !boError2)
		{
			hardware->motors.setSpeedM1(speed1);
			hardware->motors.setSpeedM2(speed2);
			statusMotors(stream);
			return;
		}
	}
	stream->printPgm(TEXT("invalid parametrs"));
}
//---------------------------------------------------------------------------------------








/* //===================================================================================*
* //                                                                                    *
* // Покажем состояние моторов															*
* //------------------------------------------------------------------------------------*
*///
void AtrmMotors :: statusMotors(AStream *stream)
{
	stream->printPgm(TEXT("Status motor:"));
	AHardware *hardware = ptrHardware;
	char szBuffer[10];
	
	
	//текущие настройки моторов 1
	zeroMemory((BYTE*)szBuffer, 10);
	strFromInt(szBuffer, hardware->motors.getSpeedM1());
	AProxyTerminal::sendEnter(stream);
	stream->printPgm(TEXT("   left motor = "));
	stream->print(szBuffer);
	
	//текущие настройки моторов 2
	zeroMemory((BYTE*)szBuffer, 10);
	strFromInt(szBuffer, hardware->motors.getSpeedM2());
	AProxyTerminal::sendEnter(stream);
	stream->printPgm(TEXT("  right motor = "));
	stream->print(szBuffer);
}
//---------------------------------------------------------------------------------------








/* //===================================================================================*
* //                                                                                    *
* // заполним матрицу символами															*
* //------------------------------------------------------------------------------------*
*///
/*
void AtrmDisplay :: setLedMatrixData(char * const argv[], AStream *stream)
{
	
}
*/
//---------------------------------------------------------------------------------------







