/* Калеса и треки, (информационные непечатаются
*/

include <../conf/config.scad>








module lineSensor()
{
	translate([-4, 0, 0]) 
	union()
	{
		difference()
		{
			translate([0, -11/2,0]) color("green")cube([41,11,2]);
			//дырки под крепления
			translate([4,0,-2])cylinder(r = 3.7 / 2, h = 5);
			translate([4 + 11,0,-2])cylinder(r = 3.7 / 2, h = 5);
		}
		
		//сенсор
		translate([4 + 11 / 2 - 5.5/2, -10/2, -6]) color("black")cube([5.5,10,6]);
		
		//крутилка
		translate([4 + 18,0, -8.5])color("white")cylinder(r = 7 / 2, h = 8.5);
	}
}



/* отрисовка обычная
*/
module render_lineSensor()
{
	translate([-gcWidthChassies / 2 + gcLineSensorMarginFront,0, gcLineSensorDepth])
	union()
	{
		translate([0, 0,0]) lineSensor();
		translate([0, -gcLineSensorLeftRight,0]) lineSensor();
		translate([0,  gcLineSensorLeftRight,0]) lineSensor();
	}
}


//выступ на переднем бампере
module lineBorder()
{
	difference()
	{
		hull()
		{
			translate([3,-4,1])sphere(r=5);
			translate([3, 4,1])sphere(r=5);
		}
		translate([1,-10, -10])cube([10, 20, 20]);
	}
}



/* //===================================================================================*
* //                                                                                    *
* // отрисовка корпуса держателя сенсора      											*
* //------------------------------------------------------------------------------------*
*///
module chassies_lineSensorMount_SHAPE()
{
	ix = -gcWidthChassies / 2 + gcLineSensorMarginFront;
	iWidthMount = 6;
	
	ix1 = -gcWidthChassies / 2;
	iw1 = 11 + iWidthMount / 2;
	union()
	{
		//перекладина
		translate([ix + 11 - iWidthMount / 2, -gcHeightChassies/2, 0]) cube([iWidthMount, gcHeightChassies, gcLineSensorDepth]);
		
		//перемычки
		translate([ix1, 6, 0]) cube([iw1, gcLineSensorLeftRight-12, gcLineSensorDepth + 3]);
		translate([ix1, -gcLineSensorLeftRight + 6, 0]) cube([iw1, gcLineSensorLeftRight-12, gcLineSensorDepth + 3]);
		
		//выступающие части
		translate([-gcWidthChassies / 2, 0, gcLineSensorDepth])
		union()
		{
			translate([0, 0,0]) lineBorder();
			translate([0, -gcLineSensorLeftRight,0]) lineBorder();
			translate([0,  gcLineSensorLeftRight,0]) lineBorder();
		}	
	}
}
//-------------------------------------------------------------------------------------//








/* //===================================================================================*
* //                                                                                    *
* // отрисовка выреза для сенсоров     													*
* //------------------------------------------------------------------------------------*
*///
module chassies_lineSensorMount_INSIDE()
{
	ix = -gcWidthChassies / 2 + gcLineSensorMarginFront + 11;
	iWidthMount = 6;
	ix2 = -gcWidthChassies / 2 + gcThicknessChassies / 2;
	iw2 = 12;
	ir = 3.5/2;
	
	union()
	{
		//дырки под болты
		
		translate([ix, 0, -30]) color("red") cylinder(r=ir, h= 40);
		translate([ix, gcLineSensorLeftRight, -30]) color("red") cylinder(r=ir, h= 40);
		translate([ix, -gcLineSensorLeftRight, -30]) color("red") cylinder(r=ir, h= 40);
		
		//дырки под платы
		
		translate([ix2, -iw2/2, gcLineSensorDepth]) cube([5, iw2, 4]);
		translate([ix2, -iw2/2 + gcLineSensorLeftRight, gcLineSensorDepth]) cube([5, iw2, 4]);
		translate([ix2, -iw2/2 - gcLineSensorLeftRight, gcLineSensorDepth]) cube([5, iw2, 4]);
		/*
		//выступающие части
		translate([-gcWidthChassies / 2, 0, gcLineSensorDepth])
		union()
		{
			translate([0, 0,0]) lineBorder();
			translate([0, -gcLineSensorLeftRight,0]) lineBorder();
			translate([0,  gcLineSensorLeftRight,0]) lineBorder();
		}*/	
	}
	
}
//-------------------------------------------------------------------------------------//









