#include "slvApplication.h"
//---------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // Constructor																		*
* //------------------------------------------------------------------------------------*
*///
AApplication :: AApplication()
	:
	stream(NULL)
{
	
}
//---------------------------------------------------------------------------------------











/* //===================================================================================*
* //                                                                                    *
* // инциализация программы																*
* //------------------------------------------------------------------------------------*
*///
void AApplication :: initialization(AHardware &hardware)
{
	stream = &hardware.uart;
	display.initialization(hardware);
	
	
	mamps = 0;
	timeWait = 0;
	move = moveStart;
}
//---------------------------------------------------------------------------------------







/* //===================================================================================*
* //                                                                                    *
* // обновление рабочей логики программы												*
* // сдесь задерживатся ненадо
* //------------------------------------------------------------------------------------*
*///
void AApplication :: update(const ATime &time, AHardware &hardware)
{
	if (stream->isRead())
	{
		const BYTE data = stream->read();
		if (slaveCommand.isCorrect(data))		
		{
			slaveCommand.execute(data, stream);
		}
		else		
		if (terminal.isCorrect(data))
		{
			/* обработка терминала
			*/
			terminal.execute(data, stream);
		}
		else
		{
			/* произошла ошибка!!!
			*/
			
		}
	}
	
	//обновим экран
	display.update(time, hardware);
	
	return;
	
	
	/* устраиваем блуждание
	*/
	switch (move)
	{
		//начало движения
		case moveStart :
		{
			timeWait += time.elapsed();
			if (timeWait > 2000)
			{
				timeWait = 0;
				move = moveCalibration;
				mamps = hardware.power.getCarrier();
				hardware.motors.setSpeedM1(255);
				hardware.motors.setSpeedM2(255);
				display.draw(0);
			}
			break;
		}
		
		//калибровка
		case moveCalibration:
		{
			timeWait += time.elapsed();
			if (timeWait > 400)
			{
				timeWait = 0;
				move = moveForward;
				mamps = hardware.power.getCarrier();
				display.draw(1);
				hardware.motors.setSpeedM1(255);
				hardware.motors.setSpeedM2(255);
			}				
		}
		
		
		//двигаемся вперед
		case moveForward :
		{
			int temp =  hardware.power.getCarrier();
			if (temp - mamps > 12)
			{
				hardware.motors.setSpeedM1(0);
				hardware.motors.setSpeedM2(0);
				move = moveBackWait;
				timeWait = 0;
				display.draw(2);
			}
			break;
		}
		
		//ждем и двигаемся назад
		case moveBackWait :
		{
			timeWait += time.elapsed();
			if (timeWait > 600)
			{
				hardware.motors.setSpeedM1(-200);
				hardware.motors.setSpeedM2(-255);
				
				timeWait = 0;
				move = moveBack;
				display.draw(3);
			}
			break;
		}
		
		//двигаемся назад
		case moveBack :
		{
			timeWait += time.elapsed();
			int temp =  hardware.power.getCarrier();
			if (temp - mamps > 10 || timeWait > 2000)
			{
				hardware.motors.setSpeedM1(0);
				hardware.motors.setSpeedM2(0);
				move = moveForwardWait;
				display.draw(timeWait > 500 ? 4 : 6);
				timeWait = 0;
			}
			break;
		}
		
		
		//ждем и двигаемся вперед
		case moveForwardWait :
		{
			timeWait += time.elapsed();
			if (timeWait > 300)
			{
				hardware.motors.setSpeedM1(255);
				hardware.motors.setSpeedM2(255);
						
				timeWait = 0;
				move = moveForward;
				display.draw(5);
			}
			break;
		}
	}
	
	
	
	
	
}
//---------------------------------------------------------------------------------------





