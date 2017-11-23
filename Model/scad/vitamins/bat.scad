/* Калеса и треки, (информационные непечатаются
*/

include <../conf/config.scad>








module bat()
{
   translate([-68 / 2, 0,0]) rotate([0, 90,0]) color("green")cylinder(r=18/2, h = 68);
}


module bat_INSIDE()
{
	il = 71;
	translate([-il / 2, 0,0]) rotate([0, 90,0]) color("green")cylinder(r=gcBatDiametr/2, h = il);
}


//вырез под батарейки
module chassies_mountBat_INSIDE()
{
	translate([0,0, gcBatDepth])
	union()
	{
		translate([0,-gcBatDiametr / 2,0]) bat_INSIDE();
		translate([0, gcBatDiametr / 2,0]) bat_INSIDE();
	}
}




/* отрисовка обычная
*/
module render_bat()
{
	translate([0,0, gcBatDepth])
	union()
	{
		translate([0,-gcBatDiametr / 2,0]) bat();
		translate([0, gcBatDiametr / 2,0]) bat();
	}
}