#include "rtLineSensor.h"
#include "rtMotor.h"
#include <NewPing.h>

AMotor 			motor; 				//������
ALineSensor 	line; 				//������� �����
NewPing 		sonar(13, 14, 200); //������ ���������
const int 		led = PD3; 			//�������������� ���������

enum EState //������� ������
{
	next,		//��������� �������
	move,		//�������� ������
	moveBack,	//�������� �����
	moveLeft,	//����������� �����
	moveRight	//����������� ������
};

EState	        cmd     = EState::next; //������� ���������
unsigned long	time    = 0; //����� ���������� �������
bool	        enemy   = false; //����� ��� ��� ����������

//��������� ������� �������
//� ������ ������ ����������
void command(EState c, int t)
{
	cmd = c; //�������
	time = millis() + t; //����� ���������� �������
}

//����� 3
//������� ��������� �������
void nextCommand()
{
	//���� �� ����� ���������� ����� ����� ����, �� �������� �� ����
	//����� ���������
	if (enemy)
	{
		command(EState::move, 500); //��������� � ����������
		return; //�������, ������� ��� ������
	}

	//���������� ����� ���, �������
	//��������� ������� ������� ����� ��������
	int i = random(3);
	if (i == 0)
	{
		//��������� ������
		command(EState::move, random(500, 1000));
	}
	if (i == 1)
	{
		//�������� �����
		command(EState::moveLeft, random(1000, 5000));
	}
	if (i == 2)
	{
		//�������� ������
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
	//����� 1, ��������� ������ ���������
	switch (cmd)
	{
		case EState::move :
		{
			motor.setSpeed(400, 400); //��������� ������
			break;
		}

		case EState::moveBack :
		{
			motor.setSpeed(-400, -400); //�������� �����
			break;
		}

		case EState::moveLeft :
		{
			motor.setSpeed(-200, 400); //������� ������
			break;
		}

		case EState::moveRight :
		{
			motor.setSpeed(400, -200); //������� ������
			break;
		}

		case EState::next :
		{
			nextCommand();//������ ��������� �������
			break; //������ �������
		}
	}
	//

	//����� 2, ������� ������ ���������
	//��� ����������� ������������
	//��������� ����� ���������� �������
	if (millis() > time)
	{
		//����� ���������� ������� �����, �����������
		command(EState::next, 0);
	}

	//�������� ��������, �� ������� ������ �� �� �����
	if (cmd != EState::moveBack) //���� �������� ����� �� �� �������� �� �����
	{
		if (line.left() && line.right())
		{
			//������� ���� ������ �����! ������������� ������� �������
			//���� �����, ������ �����!
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

	//�������� ������ �� ������� ������
	int s = sonar.ping_cm();
	if (s > 2 && s < 40)
	{
		enemy = true;
		//����� �����, �����������
		//�������� ���������� ��������
		command(EState::next, 0);
		digitalWrite(led, HIGH);
	}
	else
	{
		enemy = false; //���� ���������
		digitalWrite(led, LOW);
	}
}