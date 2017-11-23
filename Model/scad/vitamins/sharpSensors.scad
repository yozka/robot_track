/* шарповские инфокрасные сеноры
*/

include <../conf/config.scad>
//-------------------------------------------------------------------------------------//







/* //===================================================================================*
* //                                                                                    *
* // отрисовка инфакрасного сенсора на 10мм    											*
* //------------------------------------------------------------------------------------*
*///
module sharpSensor10mm()
{
	iDepth = 3;
	iShiftZ = 0.5;
	
	rotate([0,0,180])
	difference()
	{
		union()
		{
			color("darkgreen")	translate([-1.5,0,0])	cube([iDepth, 9, 22], center = true);
			color("DimGray")	translate([2,0,iShiftZ])		cube([4, 7, 13.6], center = true);
			color("DimGray")	translate([2 + 4,0,iShiftZ])	cube([5, 6.14, 13.6], center = true);
			
		}

		translate([-4,0,-9])rotate([0,90,0])cylinder(r = 2.3/2, h = iDepth + 4);
		
	}

}
//-------------------------------------------------------------------------------------//












/* //===================================================================================*
* //                                                                                    *
* // отрисовка ультразвукового сенсора         											*
* //------------------------------------------------------------------------------------*
*///
module render_sharpSensorFront()
{
	
	translate([-gcWidthChassies / 2 + gcSharpSensorFrontShiftX,0, gcSharpSensorFrontDepth])
	union()
	{
	
		translate([0, gcSharpSensorFrontShiftY, 0])
		{
			sharpSensor10mm();
		}

		translate([0, -gcSharpSensorFrontShiftY, 0])
		{
			sharpSensor10mm();
		}
	}
}
//-------------------------------------------------------------------------------------//
















/* //===================================================================================*
* //                                                                                    *
* // отрисовка корпуса держателя сенсора      											*
* //------------------------------------------------------------------------------------*
*///
module sharpSensorFrontMount()
{

	iheight = 9 + gcThicknessChassies * 2;
	ir = 13.5;
	rotate([0,0,180])
	difference()
	{
		union()
		{
			translate([-3,0,0]) rotate([90,0,0])cylinder(r = ir, h = iheight, center = true);
			translate([-2,0,0]) cube([10,iheight, ir *2], center = true);
			translate([3,0,-14]) cube([1,iheight, 1], center = true);
		}


		translate([-10,0,0]) cube([ir+6, ir + gcThicknessChassies , ir * 2 + 2], center = true);
		
		translate([-7,0,-17]) rotate([0,45,0])cube([20, 20 , 20], center = true);
	}

}
//-------------------------------------------------------------------------------------//










/* //===================================================================================*
* //                                                                                    *
* // отрисовка вырзки нишы		 по сеноср     											*
* //------------------------------------------------------------------------------------*
*///
module sharpSensorFrontMountInside()
{
	iheight = 9 + gcThicknessChassies * 2;
	ir = 15;
	rotate([0,0,180])
	union()
	{
		translate([-3.5,-5,-11.5]) cube([4, 10 , 23]);
		translate([0,-4,-6.5]) cube([15, 8 , 14]);

		//translate([-9.5,-4, 7.5]) cube([6, 8 , 10]);
		translate([-9.5,-10/2, 7.5]) cube([6, 10 , 4]);

		translate([0,0,-9])rotate([0,90,0])cylinder(r = 0.8, h = 4);
	}

}
//-------------------------------------------------------------------------------------//







/* //===================================================================================*
* //                                                                                    *
* // отрисовка корпуса держателя сенсора      											*
* //------------------------------------------------------------------------------------*
*///
module chassies_sharpSensorsFront()
{
	translate([-gcWidthChassies / 2 + gcSharpSensorFrontShiftX,0, gcSharpSensorFrontDepth])
	union()
	{
	
		translate([0, gcSharpSensorFrontShiftY, 0])
		{
			sharpSensorFrontMount();
		}

		translate([0, -gcSharpSensorFrontShiftY, 0])
		{
			sharpSensorFrontMount();
		}
	}
}
//-------------------------------------------------------------------------------------//








/* //===================================================================================*
* //                                                                                    *
* // отрисовка выреза для сенсоров     													*
* //------------------------------------------------------------------------------------*
*///
module chassies_sharpSensorsFrontInside()
{
	translate([-gcWidthChassies / 2 + gcSharpSensorFrontShiftX,0, gcSharpSensorFrontDepth])
	union()
	{
	
		translate([0, gcSharpSensorFrontShiftY, 0])
		{
			sharpSensorFrontMountInside();
		}

		translate([0, -gcSharpSensorFrontShiftY, 0])
		{
			sharpSensorFrontMountInside();
		}
	}
	
}
//-------------------------------------------------------------------------------------//


























