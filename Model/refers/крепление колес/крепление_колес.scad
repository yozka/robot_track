
cDepthChassies = 4; //������� ������
cDepth = 4; //������� ���������
cLength = 15; //����� ���������
cHeight = 15; //������ ���������



difference()
{
	translate([-cHeight / 2,0,-cDepthChassies])
	union()
	{
		cube([cHeight, cDepth, 20 + 5 + 4]);
		translate ([0,0, cDepthChassies])cube([cHeight, cLength, cDepth]);
	}
	
	//����� ��� ������
	translate([0, 0, 5]) rotate ([90,0,0]) cylinder (h = 10, r=2.6/2, center = true, $fn=100);
	translate([0, 5, 5]) rotate ([90,0,0]) cylinder (h = 5, r=6.0/2, center = true, $fn=6);
}