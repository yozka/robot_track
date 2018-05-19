#include "rtMotor.h" //библиотека моторов
#include "rtBumperSensor.h" //библиотека сенсоров на бампере
#include "rtStateMachine.h" //машина состояний
#include "rtCommandMove.h" //команды для машины, команды движения


//команды управления
ACommand_moveLeft		moveLeft;
ACommand_moveRight		moveRight;
ACommand_moveBack		moveBack;
ACommand_move			move; //движение вперед


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

	sm.command(move); //если нет припятствий, то движемся вперед
}
