#pragma once
#include "../devSettings.h"
#include "../devTime.h"
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Светодиодная матрица																*
* //------------------------------------------------------------------------------------*
*///
class
	ALedMatrix
{
public:
	ALedMatrix ();


	void initialization();							//инциализация системы
	void update(const ATime &time);					//системное обновелине экрана
	
	void clear();									//очистка экрана
	void setLine(const int row, const BYTE data);	//установка в линиию данных
	BYTE getLine(const int row) const;				//возвратим линию данных

private:
	
	int m_index;			//номер отрисовыванного фрейма
	WORD m_frameRows[8];	//буфер фреймов
	BYTE m_data[8];			//данные дублирующие

};
