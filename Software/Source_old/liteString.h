#pragma once
#include <avr/pgmspace.h>
#include "resource.h"


#define TEXT(x) (PSTR(x))


int	strLength(const char *s);

void strFromInt(char *s, const int intValue);//переводим число в строчку
void strFromIntDigit(char *s, const int intValue, const BYTE digit); //число в строчку с учетом разделителя
void strFromDWORD(char *s, const DWORD dwValue);//переводим число в строчку

void strCopy(char *sDest, const char *s, const int len);//копирование строки
void strCopy(char *sDest, const char *s);//копирование строки
void strCopy(char *sDest, const char s);//копирование строки

void strCopyPgm(char *sDest, const char *sPgm);//копирование строки из памяти программы


void strRevcat(char *sDest, const char *s, const int len);//реверсивное объеденение (добавление с переди  
bool strCompare(const char *s1, const char *s2);//проверка на совпадение строк
bool strComparePgm(const char *s, const char *sPgm);//проверка на совпадение строк данные береутся из программной памяти	

int strToInt(const char *s, bool * error = 0); //преоброзование строчки в число
int hexToInt(const char *s, bool * error = 0); //преоброзование строчки в число