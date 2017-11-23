
use <vitamins/wheel.scad>
use <vitamins/motors.scad>


use <chassiesBottom.scad>
use <chassiesBody.scad>
/*
use <chassiesDeck.scad>
use <chassiesBody.scad>
use <chassiesFace.scad>
*/

/* обычная отрисовка для экрана
*/ 

 
union()
{
	render_wheel();             //колеса
	
	render_chassiesBottom();    //нижняя часть шасси ыробота
	render_chassiesBody(); 		//верхняя часть
	/*
	
	render_chassiesDeck();      //отрисовка средней части шасси ввиде крышки нижней/
	render_chassiesFace();		//отрисовка лица робота
	render_chassiesBody();      //трисовка головы
	render_pcbMain();
	*/
}


//chassies_bodySphereInside();



/*
chassiesBody();
translate(translateFace())
rotate(rotateFace())
{
	color("DimGray") 
	union()
	{
		//chassiesFace();
		//chassiesFaceMount();
	}
}
*/


/*
difference() 
{
irDetectorMount();
irDetectorMountInside();
#translate([-1,-10,0])cube([10,50,10]);
}
irDetector();
*/



//print_chassiesBottom();
//print_chassiesDeck();
//print_chassiesBody();
