#pragma once
#include <math.h>

// �������
class Pnt
{
public:
	Pnt(){};
	Pnt(double xx, double yy):x(xx), y(yy){};
	//~Pnt(void);
	double getX(){return x;}
	double getY(){return y;}
	double getDist(Pnt other){return sqrt(pow(x-other.getX(),2)+pow(y-other.getY(),2));}

private:
	double x, y;
};

// ����߽ṹ��
struct Edge
{
	Pnt p1;
	Pnt p2;

	// ���������
	bool operator == (Edge &e)
	{
		if(p1.getX()==e.p1.getX()&&p1.getY()==e.p1.getY()&&p2.getX()==e.p2.getX()&&p2.getY()==e.p2.getY())
			return true;
		else if(p1.getX()==e.p2.getX()&&p1.getY()==e.p2.getY()&&p2.getX()==e.p2.getX()&&p2.getY()==e.p2.getY())
			return true;
		return false;
	}
};

// ��������
class Triangle
{
public:
	Triangle(Pnt pp1, Pnt pp2, Pnt pp3):p1(pp1), p2(pp2), p3(pp3)
	{
		e1.p1 = p1; e1.p2 = p2;
		e2.p1 = p1; e2.p2 = p3;
		e2.p1 = p2; e3.p2 = p3;
	};
	~Triangle(void);
	void CalCircumcircle(Pnt &center, double &radius);  //�������������Բ�İ뾶��Բ��

	Pnt p1, p2, p3;
	Edge e1, e2, e3;
};

