
//люфт при печати, уменьшение внутренней деталей для компенсацией печати
eta_motor = 0.3;	//люфты подкрепления мотора
eta_screw = 0.4;	//удерживающий мост под болт

gcSupport = 0.5; //толщина поддержки


//чистовая ширина шасси
gcHeightChassies            = 65;
gcWidthChassies             = 85;

//колеса
gcWheelRadius               = 20; //внешний радиус колес
gcTrackLength				= 48 + 0.9; //рассотояние между колесами


/*
* шасси
*/
gcThicknessChassies         = 2.4;    //толщина стенки для шасси
gcBottomRadius              = 5;   //радиус скругления нижней деки
gcBottomDepth				= 35;  //высота нижней деки без учета дна
gcBottomVaterline			= 6;  //отступ снизу на ось двигателей



//батарейки
gcBatDepth					= 25; //высотра расположения батарекйка относитлеьно корпуса
gcBatLength					= 68; //размер батарейки
gcBatDiametr				= 19; //радиус батарейка


//сенсор линия
gcLineSensorDepth			= 6; //высота расположения сенсоров отностильено корпуса
gcLineSensorMarginFront		= 0; //отступ от переда
gcLineSensorLeftRight		= 20; //боковые сенсоры относитлеьно центра расположенияе



//расположение шарповских датчико растояние на передней части робота
gcSharpSensorFrontShiftX	= 5;	//смещение по иксу (ближе к передней части)
gcSharpSensorFrontShiftY	= 24;	//смещение по игреку (28, -28)
gcSharpSensorFrontDepth		= 24;	//растояние относительно нижней точки шасси



//ступицы шасси для колес
gcHeightHub                 = 6;    //размер выступа оси ступицы на колесо
gcHeightHubRear				= 4;	//размер выступа задней оси ступицы
gcRadiusHubRear				= 6;	//радиус задней ступицы



//смещение крепления верхней крыжки
gcMountRearX 				= 8; 
gcMountFrontX				= 23;

//depricated


//нижняя часть шасси
gcDepthBottomChassies       = 18 + 3;   //высота нижней части шасси
gcMarginBottomChassies      = 10 - 3;   //дорожный просвет шасси

gcMountSizeChassies			= gcThicknessChassies * 2 + 10; //размер крепления для корпуса
gcMountShiftX				= gcWidthChassies / 2 - 7;		//центр крепления для корпуса, ввиде центра смещения
gcMountShiftFrontX			= gcWidthChassies / 2 - 6;		//центр крепления переднего центрального винта
gcMountShiftY				= gcHeightChassies / 2 - 5.5;



















//расположение сенсора датчика линий
gcReflectanceSensorShiftX	= 27;	//смещение
gcReflectanceSensorBottom	= 0;	//высота расположения









//расположение системной платы, отверстия
gcPCBMountX					= 30;
gcPCBMountY					= 40;






//DEBUG
gcDebugMargin               = 0.5;   //растояние между деталями.




