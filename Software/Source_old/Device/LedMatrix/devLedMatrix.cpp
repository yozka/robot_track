﻿#include "devLedMatrix.h"
#include <avr/io.h>



//---------------------------------------------------------------------------------------
// базовые настройки
#define SH_CP	PORTB1
#define DS		PORTB0
#define ST_CP	PORTB2
#define LEDPORT PORTB



//указатели на данные в матрице
//номер ножки который показывает строчку. на самом деле это не строчка а столбец
//ибо экран перевернут на 90 градусов.
#define	nr8 (1 << 4)
#define	nr7 (1 << 10)
#define	nr6 (1 << 11)
#define	nr5 (1 << 1)
#define	nr4 (1 << 13)
#define	nr3 (1 << 2)
#define	nr2 (1 << 6)
#define	nr1 (1 << 15)
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Constructor																		*
* //------------------------------------------------------------------------------------*
*///
ALedMatrix :: ALedMatrix()
	:
	m_index(0)
{
	
}
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // инциализация системы																*
* //------------------------------------------------------------------------------------*
*///
void ALedMatrix :: initialization()
{
	clear();
	
	DDRB |= 1 << SH_CP;
	DDRB |= 1 << DS;
	DDRB |= 1 << ST_CP;
		
	LEDPORT &= ~(1 << SH_CP);
	LEDPORT &= ~(1 << ST_CP);
	LEDPORT &= ~(1 << DS);
}
//---------------------------------------------------------------------------------------





/* //===================================================================================*
* //                                                                                    *
* // системное обновелине экрана														*
* // за одну итерацию происходит отрисовка всего экрана									*
* //------------------------------------------------------------------------------------*
*///
void ALedMatrix :: update(const ATime &time)
{
	unsigned int frame = m_frameRows[m_index];
	for (int i = 0; i < 16; i++)
	{
		//запихиваем данные
		if (frame & 0x01)
		{
			LEDPORT |= 1 << DS;
		}
		else
		{
			LEDPORT &= ~(1 << DS);
		}
			
		//продвигаем регистр
		LEDPORT |= 1 << SH_CP;
		LEDPORT &= ~(1 << SH_CP);
		//
		frame = frame >> 1;
	}

	//защелкиваем данные
	LEDPORT |= 1 << ST_CP;
	LEDPORT &= ~(1 << ST_CP);
	//
	m_index++;
	if (m_index > 7)
	{
		m_index = 0;	
	}		
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // очистка экрана																		*
* //------------------------------------------------------------------------------------*
*///
void ALedMatrix :: clear()
{
	m_index = 0;
	for (int i = 0; i < 8; i++)
	{
		m_frameRows[i] = 0;
		m_data[i] = 0;
	}
}
//---------------------------------------------------------------------------------------








/* //===================================================================================*
* //                                                                                    *
* // вставка данных в буфер																*
* //																					*
* //------------------------------------------------------------------------------------*
*///
void ALedMatrix :: setLine(const int row, const BYTE data)
{
	m_data[row] = data;
	
	/* узнаем адрес по Х
	*/
	WORD addr	 = data & (1 << 7) ? 1 << 0		: 0x0000;
	addr		|= data & (1 << 6) ? 1 << 5		: 0x0000;
	addr		|= data & (1 << 5) ? 1 << 7		: 0x0000;
	addr		|= data & (1 << 4) ? 1 << 3		: 0x0000;
	addr		|= data & (1 << 3) ? 1 << 8		: 0x0000;
	addr		|= data & (1 << 2) ? 1 << 14	: 0x0000;
	addr		|= data & (1 << 1) ? 1 << 9		: 0x0000;
	addr		|= data & (1 << 0) ? 1 << 12	: 0x0000;
	
	/* адрес Y
	*/ 
	switch (row)
	{
		case 0 :	
			m_frameRows[row] = addr | nr2 | nr3 | nr4 | nr5 | nr6 | nr7 | nr8;
			break;
			
		case 1 :	
			m_frameRows[row] = addr | nr1 | nr3 | nr4 | nr5 | nr6 | nr7 | nr8;
			break;
		
		case 2 :
			m_frameRows[row] = addr | nr1 | nr2 | nr4 | nr5 | nr6 | nr7 | nr8;
			break;
			
		case 3 :
			m_frameRows[row] = addr | nr1 | nr2 | nr3 | nr5 | nr6 | nr7 | nr8;
			break;	
		
		case 4 :
			m_frameRows[row] = addr | nr1 | nr2 | nr3 | nr4 | nr6 | nr7 | nr8;
			break;
		
		case 5 :
			m_frameRows[row] = addr | nr1 | nr2 | nr3 | nr4 | nr5 | nr7 | nr8;
			break;
			
		case 6 :
			m_frameRows[row] = addr | nr1 | nr2 | nr3 | nr4 | nr5 | nr6 | nr8;
			break;
		
		case 7 :
			m_frameRows[row] = addr | nr1 | nr2 | nr3 | nr4 | nr5 | nr6 | nr7;
			break;
			
		default:
			m_frameRows[row] = addr;
	}			

	
	/*
	unsigned int r1 = 1 << 0;
	unsigned int r2 = 1 << 5;
	unsigned int r3 = 1 << 7;
	unsigned int r4 = 1 << 3;
	unsigned int r5 = 1 << 8;
	unsigned int r6 = 1 << 14;
	unsigned int r7 = 1 << 9;
	unsigned int r8 = 1 << 12;
	
	unsigned int c1 = 1 << 4;
	unsigned int c2 = 1 << 10;
	unsigned int c3 = 1 << 11;
	unsigned int c4 = 1 << 1;
	unsigned int c5 = 1 << 13;
	unsigned int c6 = 1 << 2;
	unsigned int c7 = 1 << 6;
	unsigned int c8 = 1 << 15;
	
	*/
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------








/* //===================================================================================*
* //                                                                                    *
* // возвратим линию данных																*
* //																					*
* //------------------------------------------------------------------------------------*
*///
BYTE ALedMatrix :: getLine(const int row) const
{
	return m_data[row];
}