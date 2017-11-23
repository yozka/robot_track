/* создание шасси нижния часть где установлены двигатели
*/
include <conf/config.scad>
include <vitamins/motors.scad>
include <vitamins/screws.scad>

include <vitamins/bat.scad>
include <vitamins/line_sensor.scad>
include <vitamins/sharpSensors.scad>
//-------------------------------------------------------------------------------------//







/* //===================================================================================*
* //                                                                                    *
* // отрисовка поддона                      											*
* //------------------------------------------------------------------------------------*
*///
module chassies_pan()
{
	difference()
	{
		union()
		{
			difference()
			{
				chassies_pan_SHAPE();
				chassies_pan_INSIDE();
			}
			chassies_mountMotors_SHAPE();
			//chassies_sharpSensorsFront();
		}
		
		//вырезы
		chassies_mountMotors_INSIDE();
	}
}
//-------------------------------------------------------------------------------------//









/* //===================================================================================*
* //                                                                                    *
* // отрисовка поддона общая фигура                     											*
* //------------------------------------------------------------------------------------*
*///
module chassies_pan_SHAPE()
{
	iHeight = gcHeightChassies;
    iWidth =  gcWidthChassies;

    iThickness	= gcThicknessChassies; //общая толщина стенки
    
    iWidthDiv	= iWidth / 2;
	iHeightDiv	= iHeight / 2;

	iwr = iWidthDiv - gcBottomRadius;
	ihr = iHeightDiv - gcBottomRadius;
	
	hull()
	{
		translate([iwr, ihr,0]) cylinder(r = gcBottomRadius, h = gcBottomDepth);
		translate([iwr, -ihr,0]) cylinder(r = gcBottomRadius, h = gcBottomDepth);
		translate([-iwr, ihr,0]) cylinder(r = gcBottomRadius, h = gcBottomDepth);
		translate([-iwr, -ihr,0]) cylinder(r = gcBottomRadius, h = gcBottomDepth);
	}
	
	//пупырьки
	//сзади
	for (t = [gcBottomDepth - 6, 6, gcBottomDepth / 2])
	{
		translate([iwr - 0.5,0, t]) 
		for (x = [0 : 1 : 2])
		{
			xx = x * 11;
			translate([0, xx ,0]) sphere(r = 7);
			translate([0, -xx ,0]) sphere(r = 7);
		
		}
	}
}
//-------------------------------------------------------------------------------------//






/* //===================================================================================*
* //                                                                                    *
* // отрисовка вырезка поддона                      									*
* //------------------------------------------------------------------------------------*
*///
module chassies_pan_INSIDE()
{
	iHeight = gcHeightChassies;
    iWidth =  gcWidthChassies;

	iThickness	= gcThicknessChassies; //общая толщина стенки
    iWidthDiv	= iWidth / 2 - iThickness;
	iHeightDiv	= iHeight / 2 - iThickness;
 

	ispace = 2; //отступы для вырезание
	ir = gcBottomRadius;
	iwr = iWidthDiv - ir;
	ihr = iHeightDiv - ir;
	idepth = gcBottomDepth + ispace + ispace;
	hull()
	{
		translate([iwr, ihr, -ispace]) cylinder(r = ir, h = idepth);
		translate([iwr, -ihr, -ispace]) cylinder(r = ir, h = idepth);
		translate([-iwr, ihr, -ispace]) cylinder(r = ir, h = idepth);
		translate([-iwr, -ihr, -ispace]) cylinder(r = ir, h = idepth);
	}
}
//-------------------------------------------------------------------------------------//







/* //===================================================================================*
* //                                                                                    *
* // выступ для фиксации верхней части	    											*
* //------------------------------------------------------------------------------------*
*///
/*module chassies_bracingRing()
{
	translate([0,0, gcDepthBottomChassies])
		bracingRing_bottom_deck();
}*/
//-------------------------------------------------------------------------------------//









/* //===================================================================================*
* //                                                                                    *
* // отрисовка крепления моторов и колес       											*
* //------------------------------------------------------------------------------------*
*///
module chassies_mountMotors_SHAPE()
{
	iVaterline = gcBottomVaterline;

	//задний выступ крепления колеса
	
	difference()
	{
		union()
		{
			rotate([90,0,0]) translate([-gcTrackLength / 2, iVaterline, gcHeightChassies / 2]) cylinder(r1 = gcRadiusHubRear + 3, r2 = gcRadiusHubRear,  h = gcHeightHubRear);
			rotate([90,0,0]) translate([-gcTrackLength / 2, iVaterline, -gcHeightChassies / 2 - gcHeightHubRear]) cylinder(r1 = gcRadiusHubRear, r2 = gcRadiusHubRear + 3, h = gcHeightHubRear);
		}
		
		//обрезки снизу конусные
		translate([-gcTrackLength / 2 - 10, gcHeightChassies / 2 -1, -10]) color("red")cube([20,10,10]);
		translate([-gcTrackLength / 2 - 10, -gcHeightChassies / 2 - 9, -10]) color("red")cube([20,10,10]);
	}
	//


	//крепление мотора
	translate([gcTrackLength / 2, -gcHeightChassies / 2 - gcHeightHub, iVaterline]) motorBracket();

	rotate([0,0,180])translate([-gcTrackLength / 2, -gcHeightChassies / 2 - gcHeightHub, iVaterline]) motorBracket();

}
//-------------------------------------------------------------------------------------//








/* //===================================================================================*
* //                                                                                    *
* // внутренний выерз под крепление колес и моторов										*
* //------------------------------------------------------------------------------------*
*///
module chassies_mountMotors_INSIDE()
{
	iVaterline = gcBottomVaterline;

	//болты под задние ступицы колес
	rotate([90,0,0]) translate([-gcTrackLength / 2, iVaterline, gcHeightChassies / 2 - gcHeightHubRear]) screw_seat(M3_hex_screw, 20, 6);
	rotate([-90,0,0]) translate([-gcTrackLength / 2, -iVaterline, gcHeightChassies / 2 - gcHeightHubRear]) screw_seat(M3_hex_screw, 20, 6);
	//


	//моторы
	translate([gcTrackLength / 2, -gcHeightChassies / 2 - gcHeightHub, iVaterline]) motorBracketInside();
	rotate([0,0,180])translate([-gcTrackLength / 2, -gcHeightChassies / 2 - gcHeightHub, iVaterline]) motorBracketInside();
}
//-------------------------------------------------------------------------------------//







/* //===================================================================================*
* //                                                                                    *
* // крепление нижней и средней деки шасси												*
* //------------------------------------------------------------------------------------*
*///
module chassies_mountScrews()
{
	ih = gcHeightChassies - 5;
	iw = gcWidthChassies / 2 - gcTrackLength / 2 - 8;
	//
	union()
	{
		//задние
		translate([(gcWidthChassies/2 - gcMountRearX),  -(gcHeightChassies / 2 - gcThicknessChassies), gcBottomDepth]) rotate([0,0,90])mountClips();
		translate([(gcWidthChassies/2 - gcMountRearX),   (gcHeightChassies / 2 - gcThicknessChassies), gcBottomDepth]) rotate([0,0,-90])mountClips();

		//передние
		translate([-(gcWidthChassies/2 - gcMountFrontX),  -(gcHeightChassies / 2 - gcThicknessChassies), gcBottomDepth]) rotate([0,0,90])mountClips();
		translate([-(gcWidthChassies/2 - gcMountFrontX),   (gcHeightChassies / 2 - gcThicknessChassies), gcBottomDepth]) rotate([0,0,-90])mountClips();
		
		
		/*
		translate([gcMountShiftFrontX, 0, 0])cylinder(r=gcMountSizeChassies / 2, h=gcDepthBottomChassies + iThicknessWall);
		translate([-gcMountShiftX, gcMountShiftY, 0])cylinder(r=gcMountSizeChassies / 2, h=gcDepthBottomChassies + iThicknessWall);
		translate([-gcMountShiftX, -gcMountShiftY, 0])cylinder(r=gcMountSizeChassies / 2, h=gcDepthBottomChassies + iThicknessWall);
		*/
		
		
		translate([gcTrackLength / 2 + 6.5, -ih/2,0])	cube([iw,ih, 10]);
	}
}
//-------------------------------------------------------------------------------------//




//клипса ввиде крепления
module mountClips()
{
	ihead = 7; //ширина гайки
	iwidth = ihead + 6;
	iheight = ihead + 1;
	translate([0,-iwidth/2,0])
	difference()
	{
		translate ([-14,0,-20])rotate([0,30,0])cube([iheight + 2.5, iwidth, 30]);
		
		translate ([-10,-1,0])cube([iheight + 20, iwidth + 2, 30]);
		translate ([-20,-1,-30])cube([20, iwidth + 2, 31]);
		translate ([iheight,-1, -30])cube([20, iwidth + 2, 31]);

		//паз под гайку
		translate ([0, (iwidth - ihead) /2, -30 - 3.5])cube([20, ihead, 30]);

		translate([iheight / 2, iwidth / 2,-3])cylinder(r=2, h = 20);
	}
}




/* //===================================================================================*
* //                                                                                    *
* // вырез отверстий под болты															*
* //------------------------------------------------------------------------------------*
*///
module chassies_mountScrewsInside()
{
	translate([gcWidthChassies / 2 - 5.2, -gcLineSensorLeftRight, 20])	 rotate([180,0,90]) screw_seat(M35_hex_screw, 40, 12);;//cylinder(r=2, h = 35);
	translate([gcWidthChassies / 2 - 5.2,  gcLineSensorLeftRight, 20])	 rotate([180,0,90]) screw_seat(M35_hex_screw, 40, 12);;//cylinder(r=2, h = 35);

	/*
	translate([gcMountShiftFrontX, 0, 0])			screwHead_seat(M3_hex_screw, gcDepthBottomChassies + 5, gcDepthBottomChassies - 4);
	translate([-gcMountShiftX, gcMountShiftY, 0])	screwHead_seat(M3_hex_screw, gcDepthBottomChassies + 5, gcDepthBottomChassies - 4);
	translate([-gcMountShiftX, -gcMountShiftY, 0])	screwHead_seat(M3_hex_screw, gcDepthBottomChassies + 5, gcDepthBottomChassies - 4);
	*/
}
//-------------------------------------------------------------------------------------//








/* //===================================================================================*
* //                                                                                    *
* // дырки под контакты																	*
* //------------------------------------------------------------------------------------*
*///
/*module chassies_contact()
{

	wi = gcWidthChassies / 2;
	hi = gcChargeLength / 2;
	ti = 10;

	rr = 7; //радиус
	hh = gcChargeHeight; //длина
	
	
	for(i = [	[-wi, hi, ti],
				[-wi, -hi, ti]
			])
		translate(i)
			union()
			{
				rotate([0,90,0])cylinder(r = rr, h = hh);
				translate([0, -rr, -ti])cube([hh, rr * 2, ti]);
			}
}*/
//-------------------------------------------------------------------------------------//






/* //===================================================================================*
* //                                                                                    *
* // дырки под контакты																	*
* //------------------------------------------------------------------------------------*
*///
/*module chassies_contactInside()
{

	wi = gcWidthChassies / 2;
	hi = gcChargeLength / 2;
	ti = 10;

	rr = 7; //радиус
	hh = gcChargeHeight; //длина
	
	
	for(i = [	[-wi, hi, ti],
				[-wi, -hi, ti]
			])
		translate(i)
		translate([hh + 14,0,0])
		rotate([180,90,0])
			union()
			{
				translate([0,0,19]) cylinder(r1 = 4/2, r2=6, h = 8.5);
				screw_seat(M3_hex_screw, 30, 15);
			}
}*/
//-------------------------------------------------------------------------------------//









/* //===================================================================================*
* //                                                                                    *
* // отрисовка нижней части шасси              											*
* //------------------------------------------------------------------------------------*
*///
module chassiesBottom()
{
	difference()
	{
		union()
		{
			chassies_pan();	//сам поддон
			chassies_sharpSensorsFront(); //крепление сенсоров
			chassies_lineSensorMount_SHAPE(); //крепление сенсоров линии
			chassies_mountScrews(); //крепления
			
			//chassies_mountMotors();	//крепление моторов
			//chassies_reflectanceSensorMount(); //крепление сенсоров
		}

		//вырезающие части
		chassies_sharpSensorsFrontInside();//вырезка под фронтальные датчики
		chassies_lineSensorMount_INSIDE(); //вырезка под датчики линии
		chassies_mountScrewsInside();//вырез под скрепляющие болты
		chassies_mountBat_INSIDE();//вырез под акумулторы
		/*
		chassies_mountMotorsInside();//вырезка под моторы
		


		chassies_sharpSensorsGroundInside(); //датчик наличия земли
		chassies_reflectanceSensorMountInside(); //вырезаем крепление сенсоров нижних
		chassies_contactInside();//дырки под зарядку 
		*/
		
		
		//верхгяя часть
		translate([-gcWidthChassies/2 - 20, -gcHeightChassies/2 - 20, gcBottomDepth - 0.001])color("red")cube([gcWidthChassies + 40, gcHeightChassies + 40, 20]);
		
		//нижняя часть
		translate([-gcWidthChassies/2 - 20, -gcHeightChassies/2 - 20, -20 + 0.001])color("red")cube([gcWidthChassies + 40, gcHeightChassies + 40, 20]);

	}
}
//-------------------------------------------------------------------------------------//










/* //===================================================================================*
* //                                                                                    *
* // отрисовка поддержек		            											*
* //------------------------------------------------------------------------------------*
*///
module chassiesBottomSupport()
{
	iVaterline = gcWheelRadius - gcMarginBottomChassies;

	idt = 5;
	iwidth = 16;
	//крепление мотора
	//translate([gcTrackLength / 2 - iwidth / 2, -gcHeightChassies / 2 - gcHeightHub - idt + 0.1, 0]) cube([iwidth,idt,6.5]);
	//translate([gcTrackLength / 2 - iwidth / 2, +gcHeightChassies / 2 + gcHeightHub - 0.1, 0]) cube([iwidth,idt,6.5]);


	translate([gcTrackLength / 2 - iwidth / 2 + 16, gcHeightChassies / 2, 0]) cylinder(r=17,h=gcSupport);
	translate([(gcTrackLength / 2 - iwidth / 2 + 16), -(gcHeightChassies / 2), 0]) cylinder(r=17,h=gcSupport);
	
	translate([-(gcTrackLength / 2 - iwidth / 2 + 16), gcHeightChassies / 2, 0]) cylinder(r=17,h=gcSupport);
	translate([-(gcTrackLength / 2 - iwidth / 2 + 16), -(gcHeightChassies / 2), 0]) cylinder(r=17,h=gcSupport);





}




//print_chassiesBottom();

//test
//mountClips();

chassiesBottom();
//chassies_pan();

//difference(){sharpSensorFrontMount();sharpSensorFrontMountInside();}
//sharpSensor10mm();

//difference(){motorBracket();motorBracketInside();}


//render_sharpSensorGround();
//render_motors();
//render_reflectanceSensor();


/*
render_sharpSensorGround();
difference()
{
	chassies_sharpSensorsGround();
	chassies_sharpSensorsGroundInside();

	//#translate([30,0,0])cube([20,20,30]);	
}


*/



/*
reflectanceSensor();
difference()
{
	reflectanceSensorMount();
	reflectanceSensorMountInside();
}
*/

 


        
        


/* 
*========================================================================
* отрисовка шасси
*/
module render_chassiesBottom()
{
    translate([0, 0, gcWheelRadius - gcBottomVaterline]) 
    {
        color("lightblue") chassiesBottom();
        render_motors();
		render_bat();
		render_lineSensor();
		render_sharpSensorFront();
    }
}



/* генерация модели на выводе
*/
module print_chassiesBottom()
{
    chassiesBottom();
	chassiesBottomSupport();
}   