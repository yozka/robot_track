#include "trmPower.h"
#include "../../Device/devHardware.h"
//---------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Constructor																		*
* //------------------------------------------------------------------------------------*
*///
AtrmPower :: AtrmPower()
{
	
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // Возвратим название команды для интерпритатора										*
* //------------------------------------------------------------------------------------*
*///
void AtrmPower :: getCommandName(char * outName)
{
	strCopyPgm(outName, TEXT("power"));
}
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // проверка и выполнение команды														*
* //------------------------------------------------------------------------------------*
*///
bool AtrmPower :: isExecute(const char* cmdName, const int argc, char * const argv[], AStream *stream)
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
void AtrmPower :: help(AStream *stream)
{
	stream->printPgm(TEXT("power   - status battery, charge and energy."));
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // Обработка команды power															*
* //------------------------------------------------------------------------------------*
*///
void AtrmPower :: execute(const int argc, char * const argv[], AStream *stream)
{
	/* проверяем команды на настройку параметров
	*/
	if (setOptions(argc, argv, stream))
	{
		return;
	}

	stream->printPgm(TEXT("Status power system:"));
	AHardware *hardware = ptrHardware;
	
	//текущее напрежение батарейки
	AProxyTerminal::sendEnter(stream);
	printDigit(TEXT(" Battery\t= "),	hardware->power.getBatteryVoltage(), stream);
	printDigit(TEXT("  max\t\t= "),		hardware->power.getBatteryVoltageMax(), stream);
	printDigit(TEXT("  min\t\t= "),		hardware->power.getBatteryVoltageMin(), stream);

	//текущие потребление батареи	
	AProxyTerminal::sendEnter(stream);
	print(TEXT(" Carrier sensor\t= "),  hardware->power.getCarrier(), stream);
	print(TEXT("  max\t\t= "),			hardware->power.getCarrierMax(), stream);
	print(TEXT("  min\t\t= "),			hardware->power.getCarrierMin(), stream);

	//Настройки системы
	AProxyTerminal::sendEnter(stream);
	AProxyTerminal::sendEnter(stream);
	stream->printPgm(TEXT("Options power system:"));
	print(TEXT(" [AVCC]\t\t= "),			hardware->adc.getCalibrationAVCC(), stream);

}
//---------------------------------------------------------------------------------------








/* //===================================================================================*
* //                                                                                    *
* // отправка подписанных значений	с плавающей запятой									*
* //------------------------------------------------------------------------------------*
*///
void AtrmPower :: printDigit(const char* sCaption, const int val, AStream *stream)
{
	char szBuffer[10];
	zeroMemory((BYTE*)szBuffer, 10);
	strFromIntDigit(szBuffer, val, 3);
	AProxyTerminal::sendEnter(stream);
	stream->printPgm(sCaption);
	stream->print(szBuffer);
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // отправка подписанных значений														*
* //------------------------------------------------------------------------------------*
*///
void AtrmPower :: print(const char* sCaption, const int val, AStream *stream)
{
	char szBuffer[10];
	zeroMemory((BYTE*)szBuffer, 10);
	strFromInt(szBuffer, val);
	AProxyTerminal::sendEnter(stream);
	stream->printPgm(sCaption);
	stream->print(szBuffer);
}
//---------------------------------------------------------------------------------------








/* //===================================================================================*
* //                                                                                    *
* // Установка параметров																*
* //------------------------------------------------------------------------------------*
*///
bool AtrmPower :: setOptions(const int argc, char * const argv[], AStream *stream)
{
	if (argc <= 1)
	{
		return false;
	}
	
	if (argc >= 3 && strComparePgm(argv[1], TEXT("AVCC")))
	{
		bool er;
		int avcc = strToInt(argv[2], &er);
		if (!er)
		{
			AHardware *hardware = ptrHardware;
			hardware->adc.setCalibrationAVCC(avcc);
			stream->printPgm(TEXT("Set AVCC ok."));
			return true;
		}
		stream->printPgm(TEXT("Error AVCC."));
	}
	return false;		
}
//---------------------------------------------------------------------------------------







