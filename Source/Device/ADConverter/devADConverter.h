#pragma once
#include "../devSettings.h"
#include "../devTime.h"
//---------------------------------------------------------------------------------------






#define MAX_COUNT_ADC				5		//Максимальное количество обрабатываемых каналов
#define ADC_SLEEP_MS				20		//интервал милисекунд перед преоброзованием каналов
#define ADC_CONVERSION_SAMPLE		15		//количество преоброзований чтобы найти нужную цыфру АДС 
											//не более 60!!! иначе будет переполнение стека
#define ADC_AVCC_CALIBRATION_DEF	5000	//опорное напряжение в миливольтах на AREFF ADCC

/* список каналов
*/
enum eChannelADC
{
	channelADC0 = 0x00,
	channelADC1 = 0x01,
	channelADC2 = 0x02,
	channelADC3 = 0x03,
	channelADC6 = 0x04
};


/* стадии конечного автомата, который преобразует данные
*/
enum eAutomatADC
{
	autoNext,				//ждем для перехода в следующую итерацию
	autoStartConversion,	//начало конверсии для текущей АЦП
	autoReady,				//ждем готовности к старту АЦП
	autoConvertingSample	//конвертация данных
	
};



/* //===================================================================================*
* //                                                                                    *
* // Система АНАЛОГОВО цифрового преоброзования											*
* //   использование ADC                                                                *
* //   идет непрерывное сканирование в фоне, кажды канал опрашивается					*
* //   ADC_CONVERSION_SAMPLE раз и усредняются данные                                   *
* //                                                                                    *
* //   ADC0 - напряжение на батарее                                                     *
* //   ADC1 - правый ус                                                                 *
* //   ADC2 - левый ус                                                                  *
* //   ADC3 - внешние питалово для зарядки                                              *
* //   ADC6 - сенсор потребления тока                                                   *
* //------------------------------------------------------------------------------------*
*///
class
	AADConverter
{
	public:
		AADConverter ();



		void initialization(); //инциализация системы
	
		void	update			(const ATime &time);				//запуск преоброзвания АЦП
		int		getADC			(const eChannelADC channel) const;	//выборка сырых данных
		int		getMillivolt	(const eChannelADC channel) const;	//возвратим подсчитанные данные в миливольтах

		int		getCalibrationAVCC()const;//Значение калибровки опорного напряжения для АЦП
		void	setCalibrationAVCC(const int AVCC);//Установка калибровки напряжения для АЦП		

	
	private:
		eAutomatADC m_step;		//шаг конечного автомата действий
		eChannelADC m_channel;	//текущий номер АЦП
		int			m_timeLast;	//пропуск времени для следующего обрабоки АЦП
		BYTE		m_sample;	//текущее количество семплирования данных с АЦП
		WORD		m_sumData;	//текущая сумма семплирующих данных
		
		int			m_calibrationAVCC;//Опорное напряжение для АЦП
		int			m_adcData[MAX_COUNT_ADC]; //посчитанные даные по каналам
		
		
		inline void automatNext(const ATime &time); //выполнение следующего шага по уонверсии
		inline void automatStartConversion();		//запуск АЦП с новыми параметрами для канала
		inline void automatReady();					//ждать готовности снятия данных с АЦП
		inline void automatConvertingSample();		//чтение потока данных с АЦП и высчитывания среднего значения
};
