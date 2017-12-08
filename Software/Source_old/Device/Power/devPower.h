﻿#pragma once
#include "../devSettings.h"
#include "../devTime.h"
//---------------------------------------------------------------------------------------




#define POWER_SLEEP_MS	500 //количество миилисикунд на обнолвение всей статистики по батареи




/* //===================================================================================*
* //                                                                                    *
* // Система отслеживание уровня заряда, и потребеление энергии							*
* // Также идет зарядка и контроль над акамуляторами                                    *
* //------------------------------------------------------------------------------------*
*///
class
	APower
{
	public:
		APower ();


		void initialization();				//Инциализациия сборки батарей
		void update(const ATime &time);		//системное обновелине мониторинга питания
	
		int getBatteryVoltage() const;		//Возвратим напряжение батарейки в миливольтах
		int getBatteryVoltageMin() const;	//Минимальное напряжение батарейки
		int getBatteryVoltageMax() const;	//Максимально зафиксированное напряжение батарейки
		
		int getCarrier() const;				//Текущая нагрузка на батарею
		int getCarrierMin() const;			//Минимальная нагрузка на батарею
		int getCarrierMax() const;			//Максимальная нагрузка на батарею
		
	private:
	
	
		int m_batt;		//текущие напряжение батарейки
		int m_battMin;	//минимальное напряжение батарейки
		int m_battMax;	//максимальное напряжение батарейки

		int m_carrier;		//текущая нагрузка на батарейку
		int m_carrierMin;	//минимальное значение нагрузки
		int m_carrierMax;	//максимальное значение нагрузки
		
		


		int m_timeLast; //время обновления состояние батарейки
};
