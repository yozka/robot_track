#include "slvTerminal.h"
//---------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Constructor																		*
* //------------------------------------------------------------------------------------*
*///
ATerminal :: ATerminal()
{
	
}
//---------------------------------------------------------------------------------------










/* //===================================================================================*
* //                                                                                    *
* // Обработка команды																	*
* //------------------------------------------------------------------------------------*
*///
void ATerminal :: onInterpretation(const int argc, char * const argv[], AStream *stream)
{
	if (argc > 0)
	{
		char *cmd = argv[0];//команда
		
		/* проверка внешних команд
		*/
		if (trmDisplay.	isExecute(cmd, argc, argv, stream)) return;
		if (trmPower.	isExecute(cmd, argc, argv, stream)) return;
		if (trmMotors.	isExecute(cmd, argc, argv, stream)) return;
		if (trmTime.	isExecute(cmd, argc, argv, stream)) return;
		if (trmPrint.	isExecute(cmd, argc, argv, stream)) return;
		
		
		/* встроеные каманды
		*/
		if (strComparePgm(cmd, TEXT("help")))
		{
			help(stream); //краткая справка
			return;
		}			

		if (strComparePgm(cmd, TEXT("exit")))
		{
			exit(stream); //выход из терминала
			return;
		}
		
		stream->printPgm(TEXT("Command '"));
		stream->print(cmd);
		stream->printPgm(TEXT("' not found"));	
		return;
	}
	stream->printPgm(TEXT("Error, not command"));
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // вывод справку по командам															*
* //------------------------------------------------------------------------------------*
*///
void ATerminal :: help(AStream *stream)
{
	trmDisplay.help(stream);
	sendEnter(stream);
	trmPower.help(stream);
	sendEnter(stream);
	trmMotors.help(stream);
	sendEnter(stream);
	trmTime.help(stream);
	sendEnter(stream);
	trmPrint.help(stream);
	sendEnter(stream);
	stream->printPgm(TEXT("exit    - disconnect terminal"));
}
//---------------------------------------------------------------------------------------




