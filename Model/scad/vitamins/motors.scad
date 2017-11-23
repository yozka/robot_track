/* Моторчики
*/

include <../conf/config.scad>




module motor()
{
	union()
	{
		translate([24.2,-19.4, -1.3])
		scale(10)
		color("red")
		import("imp_motors.stl");  
	}
}


 






/* отрисовка моторов
*/
module render_motors()
{
    iVaterline = 5;


	iHeightDiv = gcHeightChassies / 2;
	iWidthDiv = gcTrackLength / 2;

	translate([iWidthDiv, -iHeightDiv - gcHeightHub, iVaterline])
	{
		motor();
	}

	rotate([0,0,180])
	translate([-iWidthDiv, -iHeightDiv - gcHeightHub, iVaterline])
	{
		motor();
	}
}

//-------------------------------------------------------------------------------------//










/* //===================================================================================*
* //                                                                                    *
* // крепление мотора			             											*
* //------------------------------------------------------------------------------------*
*///
module motorBracket()
{
	iLength = 23;

	iHeightB = 17;	//высота столба на котором прикручивается плата энкодера

	iHeightMotor = 22;
	
	
	union()
	{
		//отрисовка ступицы редуктора мотора
		translate([-16/2, 0, -6])
		cube([16, gcHeightHub, 12 ]);


		//держатель мотора
		translate([-iHeightMotor / 2, gcHeightHub, -6])
		cube([iHeightMotor, iLength, iHeightB]);

	}
}
//-------------------------------------------------------------------------------------//










/* //===================================================================================*
* //                                                                                    *
* // вырез внутреностей для крепления мотора   											*
* //------------------------------------------------------------------------------------*
*///
module motorBracketInside()
{
	color("red")
	union()
	{
		itop = 13-1.7;
		ic = 2.9;
		
		//вырез под редуктор мотора
		translate([(-12 - eta_motor)/2, -1, -7])
		difference()
		{
			//под редуктор
			cube([(12 + eta_motor), 27 + eta_motor, itop]);
			
			//направляющие косые шипы для фиксации двигателя
			translate([-2.0,1 + 1.5, itop])rotate([0,45,0])cube([ic, 4.3,ic]); //фиксация редуктора
			translate([-2.0,1 + 11, itop])rotate([0,45,0])cube([ic, 17,ic]);//фиксация мотора
			
			translate([12.5,1 + 1.5,-2.1+itop])rotate([0,-45,0])cube([ic, 4.3,ic]);//фиксация мотора
			translate([12.5,1 + 11,-2.1+itop])rotate([0,-45,0])cube([ic, 17,ic]);//фиксация мотора
		}
		translate([(-12 - eta_motor)/2, 22, 2])
		cube([(12 + eta_motor), 10, 15]);


	}


}
