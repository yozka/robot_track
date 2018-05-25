#include "rtMotor.h" //библиотека моторов
#include "rtBumperSensor.h" //библиотека сенсоров на бампере
#include "rtStateMachine.h" //машина состояний
#include "rtCommandMove.h" //команды для машины, команды движения
#include "rtLineSensor.h"	//сенсор линий
#include <NewPing.h>


//команды управления
ACommand_moveLeft     moveLeft;
ACommand_moveRight    moveRight;
ACommand_moveBack     moveBack;
ACommand_move         move; //движение вперед
ACommand_moveRandom   moveRandom;

NewPing 		sonar(13, 14, 200); //датчик растояния


//настройка
void setup() 
{
    motor.begin(); //настройка моторов
    bumper.begin();//настройка бамперов сенсеров
    line.begin();
  
    sm.signal_next = nextCommand; //привязываем функцию выбора следующей команды
    line.signal_detect = lineDetect; //привязка функции что обработан датчик линий
}

//обновление
void loop() 
{
    sm.update(); //обновление машины состояния
    bumper.update(); //обновление состояние бампера
    line.update(); //обновление сенора линий
}

//следующая команда
void nextCommand()
{
    //проверям бампер
    //мы начтото наткнулись, то едем вперед
    if (bumper.left() && bumper.right())
    {
        sm.command(move); //команда движения
        return;
    }

    if (bumper.left()) //бампер сработал слевой стороны
	{
        sm.command(moveLeft, 200); //движемся
        return;
    }

	  if (bumper.right()) //бампер сработал справой сторны
	  {
		    sm.command(moveRight, 200);//движемся
		    return;
	  }

	
	  //проверка сонара на предмет врагов
	  int s = sonar.ping_cm();
	  if (s > 2 && s < 40)
	  {
		    sm.command(move);
		    return;
	  }
	
	  sm.command(moveRandom); //если нет припятствий, то движемся вперед
}

void lineDetect()
{
    if (line.left() && line.right())
    {
        sm.command(moveBack);
        return;
    }
    if (line.center())
    {
        sm.command(moveBack);
        return;
    }

    if (line.left())
    {
        sm.command(moveRight);
        return;
    }
    if (line.right())
    {
        sm.command(moveLeft);
        return;
    }
}
