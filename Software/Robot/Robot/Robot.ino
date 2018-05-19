#include "rtMotor.h" //���������� �������
#include "rtBumperSensor.h" //���������� �������� �� �������
#include "rtStateMachine.h" //������ ���������
#include "rtCommandMove.h" //������� ��� ������, ������� ��������


//������� ����������
ACommand_moveLeft		moveLeft;
ACommand_moveRight		moveRight;
ACommand_moveBack		moveBack;
ACommand_move			move; //�������� ������


//���������
void setup() 
{
	motor.begin(); //��������� �������
	bumper.begin();//��������� �������� ��������

	sm.signal_next = nextCommand; //����������� ������� ������ ��������� �������
}

//����������
void loop() 
{
	sm.update(); //���������� ������ ���������
	bumper.update(); //���������� ��������� �������
}

//��������� �������
void nextCommand()
{
	//�������� ������
	//�� ������� ����������, �� ���� �����
	if (bumper.left() && bumper.right())
	{
		sm.command(moveBack); //������� �������� �����
		return;
	}

	if (bumper.left()) //������ �������� ������ �������
	{
		sm.command(moveRight); //�������� �������
		return;
	}

	if (bumper.right()) //������ �������� ������� ������
	{
		sm.command(moveLeft);//�������� �� ����
		return;
	}

	sm.command(move); //���� ��� �����������, �� �������� ������
}
