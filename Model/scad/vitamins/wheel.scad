/* Калеса и треки, (информационные непечатаются
*/

include <../conf/config.scad>




module track(length, alpha)
{
	color("white", alpha)
	translate([-18 - length / 2, 13, 18])
	{
		rotate([90,90,0])
		{
			import("imp_wheel.stl");	
			translate([0, length, 0]) import("imp_wheel.stl");
		}
	}
		

		
	color("black", alpha)
	translate([-length / 2, 14, 0]) 
	rotate([90,90,0])
	{	
			difference()
			{
				hull() 
				{
				   translate([0,length,0]) cylinder(r=20,h=14);
				   cylinder(r=20, h=14);
				}
				translate([0, 0, -1])
				hull() 
				{
				   translate([0,length, 0]) cylinder(r=17,h=16);
				   cylinder(r=17, h=16);
				}
			}
		}

}





module wheel_48(width)
{
    iSpace = 2;
	translate([0, width / 2 + iSpace, gcWheelRadius]) track(48, 0.5);
	translate([0, -width / 2 - iSpace, gcWheelRadius]) mirror([ 0, 1, 0 ]) track(48, 0.5);
}



/* отрисовка обычная
*/
module render_wheel()
{
	wheel_48(gcHeightChassies + gcDebugMargin * 2);
}