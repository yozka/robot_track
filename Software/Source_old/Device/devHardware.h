#pragma once
#include "devSettings.h"
#include "devTime.h"
#include "LedMatrix/devLedMatrix.h"
#include "Serial/devSerialUART.h"
#include "Power/devPower.h"
#include "Motors/devMotors.h"
#include "ADConverter/devADConverter.h"
#include "EEPROM/devEEPROM.h"
#include "Servos/devServos.h"
//---------------------------------------------------------------------------------------




//доступ к железу
#define ptrHardware AHardware::instance()





/* //===================================================================================*
* //                                                                                    *
* // Интерфес для доступа и управлением железом контроллера								*
* // вовсей программе используется только один экземпляр железа
* //------------------------------------------------------------------------------------*
*///
class
	AHardware
{
	public:
		AHardware ();
		/* реалиация синглентона класса, для быстрого доступпа к железу
		*/
		static AHardware* instance();
		//---------------------------------------------------------------

		
		ATime			time;		//время системы
		ALedMatrix		ledMatrix;	//лед матрица
		ASerialUART		uart;		//серийный протокол UART
		APower			power;		//Заряд батареи
		AMotors			motors;		//Моторы
		AADConverter	adc;		//Аналоговоцифровой преобразователь
		AServo			servo;		//Сервоприводы
	
		void initialization();	//инциализация системы
		void update();//Системное обновление
		void updateProcess();//Системное обновление вызывающие извне


	private:	
		bool m_lock;//блокировка процесса, чтобы издругих частей невозможно было выполнить

};
