#pragma once

/* типы данных
*/
typedef	signed char				INT8;
typedef unsigned char			BYTE;
typedef unsigned short int 		WORD;
typedef unsigned long int		DWORD;
#define NULL (0)


/*
* описание ресурсов системы и базовые настройки компилятора
*/
#include "liteString.h"



/*тип среды, микроконтроллер это или нет
*/
#define AVR 1


//#define NEW 1
/* оператор new delete
*/
#ifdef NEW
	#include <stdlib.h>
	void * operator new(size_t size);
	void operator delete(void * ptr);
#endif



/* штуки для тестирвоания
*/
//#define _TESTCMD //тест команд терминала


/* имя терминальной программы
*/
#define NAME_TERMINAL "TrackPixel"




void zeroMemory(BYTE * data, const int length);