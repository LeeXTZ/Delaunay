#include "Delaunay.h"

using namespace std;

void main()
{
	vector<Pnt> vlist;
	Pnt p1(10,20),p2(20,10),p3(30,30),p4(40,20);
	vlist.push_back(p1);vlist.push_back(p2);vlist.push_back(p3);vlist.push_back(p4);

	Delaunay dln;
	vector<Triangle> t = dln.IncremInsert(vlist);
	cout<<t.size()<<endl;

	/*Pnt p1(0,0), p2(1,1), p3(2,0);
	Triangle tri(p1,p2,p3);
	Pnt center; double radius;
	tri.CalCircumcircle(center, radius);
	cout<<center.getX()<<","<<center.getY()<<endl;*/
}