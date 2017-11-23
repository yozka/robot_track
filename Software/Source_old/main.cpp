#include "Device/devHardware.h"
#include "Application/slvApplication.h"



int main() 
{
	/*
	char t[10];
	strFromIntDigit(t, -10, 3);
	*/
	
	/* железо
	*/
	AHardware hardware;
	hardware.initialization();
	
	/* логика программы
	*/
	AApplication app;
	app.initialization(hardware);
	
	while (true)
	{
		hardware.update();		
		app.update(hardware.time, hardware);
	}
	
	
}