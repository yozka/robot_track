#include "devADConverter.h"
#include "../devHardware.h"

#include <avr/io.h>
//---------------------------------------------------------------------------------------









/* //===================================================================================*
* //                                                                                    *
* // Constructor																		*
* //------------------------------------------------------------------------------------*
*///
AADConverter :: AADConverter()
	:
	m_step		(autoNext),
	m_channel	(channelADC0),
	m_timeLast	(0),
	m_sample	(ADC_CONVERSION_SAMPLE),
	m_sumData	(0),
	m_calibrationAVCC(ADC_AVCC_CALIBRATION_DEF)
{
	
}
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // инциализация системы																*
* //------------------------------------------------------------------------------------*
*///
void AADConverter :: initialization()
{
	m_step		= autoNext;
	m_channel	= channelADC0;
	m_timeLast	= 0;
	m_sample	= ADC_CONVERSION_SAMPLE;
	m_sumData	= 0;
	for (int i = 0; i < MAX_COUNT_ADC; i++)
	{
		m_adcData[i] = 0;
	}
	
	
	/* читаем из памяти данные о калибровке датчика
	*/
	eeprom_busy_wait();
	m_calibrationAVCC =  eeprom_read_word(EEPROM_calibrationAVCC);
	if (m_calibrationAVCC == 0x0000 || m_calibrationAVCC == 0xFFFF)
	{
		m_calibrationAVCC = ADC_AVCC_CALIBRATION_DEF;
	}
	
}
//---------------------------------------------------------------------------------------





/* //===================================================================================*
* //                                                                                    *
* // /выборка сырых данных																*
* //------------------------------------------------------------------------------------*
*///
int AADConverter :: getADC(const eChannelADC index) const
{
	return m_adcData[index];
}
//---------------------------------------------------------------------------------------


	
	
	
	
/* //===================================================================================*
* //                                                                                    *
* // запуск преоброзвания АЦП															*
* //------------------------------------------------------------------------------------*
*///
void AADConverter :: update(const ATime &time)
{
	switch (m_step)
	{
		case autoNext				: automatNext(time); break;
		case autoStartConversion	: automatStartConversion();break;
		case autoReady				: automatReady();break;
		case autoConvertingSample	: automatConvertingSample();break;
	}
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // выполнение следующего шага															*
* //------------------------------------------------------------------------------------*
*///
void AADConverter :: automatNext(const ATime &time)
{
	//устанавливаем задержку между измерениями каналов
	m_timeLast += time.elapsed();
	if (m_timeLast <= 0)
	{
		m_timeLast -= ATime::fromMS(ADC_SLEEP_MS);
		
		//следующие измерение
		switch (m_channel)
		{
			case channelADC0 : m_channel = channelADC1; break;
			case channelADC1 : m_channel = channelADC2; break;
			case channelADC2 : m_channel = channelADC3; break;
			case channelADC3 : m_channel = channelADC6; break;
			case channelADC6 : m_channel = channelADC0; break;
		}
			
		//выполним следующий шаг, начала конверсии с новыми каналом
		m_step = autoStartConversion; 	
	}
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // запуск АЦП с новыми параметрами для канала											*
* //------------------------------------------------------------------------------------*
*///
void AADConverter :: automatStartConversion()
{
	//выбераем канал АЦП
	BYTE bChannel = 0;
	switch (m_channel)
	{
		case channelADC0 : bChannel = 0;break;
		case channelADC1 : bChannel = 1;break;
		case channelADC2 : bChannel = 2;break;
		case channelADC3 : bChannel = 3;break;
		case channelADC6 : bChannel = 6;break;
	}

	//настраиваем АЦП	
	ADCSRA = 0x87;		// bit 7 set: ADC enabled
						// bit 6 clear: don't start conversion
						// bit 5 clear: disable autotrigger
						// bit 4: ADC interrupt flag
						// bit 3 clear: disable ADC interrupt
						// bits 0-2 set: ADC clock prescaler is 128
						//  128 prescaler required for 10-bit resolution when FCPU = 20 MHz
	
						// NOTE: it is important to make changes to a temporary variable and then set the ADMUX
						// register in a single atomic operation rather than incrementally changing bits of ADMUX.
						// Specifically, setting the ADC channel by first clearing the channel bits of ADMUX and
						// then setting the ones corresponding to the desired channel briefly connects the ADC
						// to channel 0, which can affect the ADC charge capacitor.  For example, if you have a
						// high output impedance voltage on channel 1 and a low output impedance voltage on channel
						// 0, the voltage on channel 0 be briefly applied to the ADC capacitor before every conversion,
						// which could prevent the capacitor from settling to the voltage on channel 1, even over
						// many reads.

	unsigned char tempADMUX = (1 << REFS0);
	tempADMUX |= bChannel;    // we only get this far if channel is less than 32

	
	ADMUX = tempADMUX;
	ADCSRA |= 1 << ADSC;	// start the conversion
	
	m_step = autoReady;// следующий шаг, ждем готовности снятия данных с АЦП
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // ждать готовности снятия данных с АЦП												*
* //------------------------------------------------------------------------------------*
*///
void AADConverter :: automatReady()
{
	if (!((ADCSRA >> ADSC) & 1))
	{
		//флаг ADSC = 0 то ацп готово снимать новые данные
		//выставляем количество итераций семплирования, и запускаем АЦП
		m_sumData	 = 0;//общая сумма значений АЦП
		m_sample	 = ADC_CONVERSION_SAMPLE;
		ADCSRA		|= 1 << ADSC; //запуск АЦП
		m_step		 = autoConvertingSample;
	}
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // чтение потока данных с АЦП и высчитывания среднего значения						*
* //------------------------------------------------------------------------------------*
*///
void AADConverter :: automatConvertingSample()
{
	if (!((ADCSRA >> ADSC) & 1))
	{
		m_sumData += ADC;
		m_sample--;
		if (m_sample)		
		{
			ADCSRA |= 1 << ADSC; //конвертируем дальше
			return;
		}
		
		//конвертация данных завершенна
		//m_adcData[m_channel] = (m_sumData + (ADC_CONVERSION_SAMPLE >> 1)) / ADC_CONVERSION_SAMPLE;
		if (m_sumData)
		{
			m_adcData[m_channel] = m_sumData / ADC_CONVERSION_SAMPLE;
		}
		else
		{
			m_adcData[m_channel] = 0;
		}			
		
		m_step = autoNext;
	}		
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // возвратим подсчитанные данные в миливольтах										*
* //------------------------------------------------------------------------------------*
*///
int AADConverter :: getMillivolt(const eChannelADC channel) const
{
	const int data = m_adcData[channel];
	const DWORD temp = (DWORD)data * m_calibrationAVCC;
	return (temp + 513) / 1023;
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // Значение калибровки опорного напряжения для АЦП									*
* //------------------------------------------------------------------------------------*
*///
int AADConverter :: getCalibrationAVCC()const
{
	return m_calibrationAVCC;
}
//---------------------------------------------------------------------------------------






/* //===================================================================================*
* //                                                                                    *
* // Установка калибровки напряжения для АЦП											*
* //------------------------------------------------------------------------------------*
*///
void AADConverter :: setCalibrationAVCC(const int AVCC)
{
	m_calibrationAVCC = AVCC;
	//запишем данные в ЕППРОМ
	eeprom_busy_wait();
	eeprom_write_word(EEPROM_calibrationAVCC, m_calibrationAVCC);
}

