#include "rtMotor.h" //библиотека моторов
#include "rtBumperSensor.h" //библиотека сенсоров на бампере
#include "rtStateMachine.h" //машина состояний
#include "rtCommandMove.h" //команды для машины, команды движения
#include <NewPing.h>


//команды управления
ACommand_moveLeft		moveLeft;
ACommand_moveRight		moveRight;
ACommand_moveBack		moveBack;
ACommand_move			move; //движение вперед
ACommand_moveRandom		moveRandom;

NewPing 		sonar(13, 14, 200); //датчик растояния

//настройка
void setup() 
{
	motor.begin(); //настройка моторов
	bumper.begin();//настройка бамперов сенсеров

	sm.signal_next = nextCommand; //привязываем функцию выбора следующей команды
}

//обновление
void loop() 
{
	sm.update(); //обновление машины состояния
	bumper.update(); //обновление состояние бампера
}

//следующая команда
void nextCommand()
{
	//проверям бампер
	//мы начтото наткнулись, то едем назад
	if (bumper.left() && bumper.right())
	{
		sm.command(moveBack); //команда движения назад
		return;
	}

	if (bumper.left()) //бампер сработал слевой стороны
	{
		sm.command(moveRight); //движемся направо
		return;
	}

	if (bumper.right()) //бампер сработал справой сторны
	{
		sm.command(moveLeft);//движемся на лево
		return;
	}

	
	//проверка сонара на предмет врагов
	int s = sonar.ping_cm();
	if (s > 2 && s < 20)
	{
		sm.command(moveRight);
		return;
	}
	sm.command(moveRandom); //если нет припятствий, то движемся вперед
}
