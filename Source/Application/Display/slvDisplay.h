#pragma once
#include "../../resource.h"
#include "../../Device/devHardware.h"
#include "slvFonts.h"
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Реализация дисплея, и показ всяких штук на дисплее, анимация, цыфры итд			*
* //------------------------------------------------------------------------------------*
*///
class
	ADisplay

{
	public:
		ADisplay ();

		void initialization(AHardware &hardware);	//инциализация дисплея
		void update(const ATime &time, AHardware &hardware);	//обновление дисплея

		void draw(const int index);//отрисовка картинки 

	protected:

		ALedMatrix *graphics;//девайс на котором идет отрисовка

		int x;
		int y;
		int delay;
	
	
};
