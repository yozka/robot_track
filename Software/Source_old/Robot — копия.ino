#include "rtLineSensor.h"
#include "rtMotor.h"
#include <NewPing.h>

AMotor 			motor; 				//моторы
ALineSensor 	line; 				//датчики линии
NewPing 		sonar(13, 14, 200); //датчик растояния
const int 		led = PD3; 			//информационный светодиод

enum EState //команды робота
{
	next,		//следующая команда
	move,		//двигатся вперед
	moveBack,	//двигатся назад
	moveLeft,	//развернемся влева
	moveRight	//развернемся вправо
};

EState	        cmd     = EState::next; //текущие состояние
unsigned long	time    = 0; //время выполнения команды
bool	        enemy   = false; //видим или нет противника

//установка текущей команды
//с учетом времни выполнения
void command(EState c, int t)
{
	cmd = c; //команда
	time = millis() + t; //время выполнения команды
}

//часть 3
//выберем следующую команду
void nextCommand()
{
	//если мы видем противника прямо перед нами, то движемся на него
	//чтобы столкнуть
	if (enemy)
	{
		command(EState::move, 500); //двигаемся к противнику
		return; //выходим, команда уже подана
	}

	//противника рядом нет, поэтому
	//случайным образом выберем новое действие
	int i = random(3);
	if (i == 0)
	{
		//двигаемся вперед
		command(EState::move, random(500, 1000));
	}
	if (i == 1)
	{
		//разворот влева
		command(EState::moveLeft, random(1000, 5000));
	}
	if (i == 2)
	{
		//разворот вправа
		command(EState::moveRight, random(1000, 5000));
	}
}
//

void setup() 
{
	motor.begin();
	line.begin();
	time = millis();
    pinMode(led, OUTPUT);
}

void loop() 
{
	//часть 1, обработка машины состояния
	switch (cmd)
	{
		case EState::move :
		{
			motor.setSpeed(400, 400); //двигаемся вперед
			break;
		}

		case EState::moveBack :
		{
			motor.setSpeed(-400, -400); //движемся назад
			break;
		}

		case EState::moveLeft :
		{
			motor.setSpeed(-200, 400); //поворот налево
			break;
		}

		case EState::moveRight :
		{
			motor.setSpeed(400, -200); //поворот вправо
			break;
		}

		case EState::next :
		{
			nextCommand();//задаем следующую команду
			break; //другую команду
		}
	}
	//

	//часть 2, перевод машины состояния
	//для экстренного реагирования
	//проверяем время выполнения команды
	if (millis() > time)
	{
		//время выполнения команды вышло, остановимся
		command(EState::next, 0);
	}

	//проверка сенсоров, на предмет выхода из за линий
	if (cmd != EState::moveBack) //если движемся назад то не обращаем на линии
	{
		if (line.left() && line.right())
		{
			//поймали край черной линии! останавливаем текущую команду
			//даем новую, полный назад!
			command(EState::moveBack, 2000);
		}
		else
		if (line.left())
		{
			command(EState::moveLeft, 500);
		}
		else
		if (line.right())
		{
			command(EState::moveRight, 500);
		}
	}
	//

	//проверка сонара на предмет врагов
	int s = sonar.ping_cm();
	if (s > 2 && s < 40)
	{
		enemy = true;
		//нашли врага, остановимся
		//ивыберем дальнейшее действие
		command(EState::next, 0);
		digitalWrite(led, HIGH);
	}
	else
	{
		enemy = false; //враг потерялся
		digitalWrite(led, LOW);
	}
}