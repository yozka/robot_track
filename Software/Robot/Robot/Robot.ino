#include "rtLineSensor.h"
#include "rtMotor.h"
#include <NewPing.h>

AMotor motor; //моторы
ALineSensor line; //датчики линии
NewPing sonar(13, 14, 100); 

enum EState //команды робота
{
	stop,		//ничего не делать
	move,		//двигатся вперед
	moveBack,	//двигатся назад
	moveLeft,	//развернемся влева
	moveRight	//развернемся вправо
};

EState	cmd = EState::move; //текущие состояние
int		time = 0; //время выполнения состояния
bool	enemy = false; //видим или нет противника


//установка текущей команды
//с учетом времни выполнения
void command(EState c, int t)
{
	cmd = c; //команда
	time = millis() + t; //время выполнения команды
}
//


//выберем следующую команду
void next()
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
	int i = random(4);
	if (i == 0)
	{
		//двигаемся вперед
		command(EState::move, random(1000, 3000));
	}
	if (i == 1)
	{
		//разворот влева
		command(EState::moveLeft, random(500, 1000));
	}
	if (i == 2)
	{
		//разворот вправа
		command(EState::moveRight, random(500, 1000));
	}
}
//


void setup() 
{
	  motor.begin();
	  line.begin();
	  time = millis();
}

void loop() 
{
	//часть 1, обработка машины состояния
	switch (cmd)
	{
	case EState::move:
	{
		motor.setSpeed(400, 400); //двигаемся вперед
		break;
	}

	case EState::moveBack:
	{
		motor.setSpeed(-400, -400); //движемся назад
		break;
	}

	case EState::moveLeft:
	{
		motor.setSpeed(-200, 400); //поворот налево
		break;
	}

	case EState::moveRight:
	{
		motor.setSpeed(400, -200); //поворот вправо
		break;
	}

	case EState::stop:
	{
		next();//мы остановились, ничго не делаем, выберем
		break; //другую команду
	}
	default:
		break;
	}

	//часть 2, перевод машины состояния
	//для экстренного реагирования
	//проверяем время выполнения команды
	if (millis() > time)
	{
		//время выполнения команды вышло, остановимся
		cmd = EState::stop;
	}

	//проверка сенсоров, на предмет выхода из за линий
	if (line.left() || line.center() || line.right())
	{
		  //поймали край черной линии! останавливаем текущую команду
		  //даем новую, полный назад!
		  command(EState::moveBack, 300);
	}
	//

  //проверка сонара на предмет врагов
  int s = sonar.ping_cm();
  if (s > 0 && s < 50)
  {
      enemy = true;
      //нашли врага, остановимся
      //ивыберем дальнейшее действие
      command(EState::stop, 0);
  }
  else
  {
      enemy = false;
  }
}

