include <conf/config.scad>
//include <vitamins/screws.scad>


/* 
*========================================================================
* фейса
*/
module chassiesBody()
{
	difference()
	{
		chassies_body_SHAPE();
		
		
		//срезка снизу
		color("red")translate([-70,-70, - 50]) cube([140,140,50]);
	}
	
}




/* //===================================================================================*
* //                                                                                    *
* // отрисовка поддона общая фигура                     											*
* //------------------------------------------------------------------------------------*
*///
module chassies_body_SHAPE()
{
	iHeight = gcHeightChassies;
    iWidth =  gcWidthChassies;

    iThickness	= gcThicknessChassies; //общая толщина стенки
  	iRadius = 13;
	
    iWidthDiv	= iWidth / 2;
	iHeightDiv	= iHeight / 2 + 10;

	//iWidthDiv = 35;
	//iHeightDiv = 35;
	
	iwr = iWidthDiv - iRadius;
	ihr = iHeightDiv - iRadius;
	ihh = 10;
	
	idd = 11;
	hull()
	{
		translate([iwr, ihr,0]) cylinder(r = iRadius, h = ihh);
		translate([iwr, -ihr,0]) cylinder(r = iRadius, h = ihh);
		translate([-iwr, ihr,0]) cylinder(r = iRadius, h = ihh);
		translate([-iwr, -ihr,0]) cylinder(r = iRadius, h = ihh);
		
		translate([iwr, ihr,ihh]) sphere(r = iRadius);
		translate([iwr, -ihr,ihh]) sphere(r = iRadius);
		translate([-iwr, ihr,ihh]) sphere(r = iRadius);
		translate([-iwr, -ihr,ihh]) sphere(r = iRadius);
		
		//translate([-10,idd,10]) sphere(r = 35);
		//translate([-10,-idd,10]) sphere(r = 35);
		translate([-8,0,10]) sphere(r = 45);
	}
	
	
}
//-------------------------------------------------------------------------------------//









//chassiesBody();




/* 
*========================================================================
* отрисовка шасси
*/
module render_chassiesBody()
{
    translate([0, 0, gcWheelRadius - gcBottomVaterline + gcBottomDepth + 3]) 
    {
        color("lightblue") chassiesBody();
       
    }
}