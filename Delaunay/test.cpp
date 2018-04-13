#include "Delaunay.h"
#include <fstream>
#include <string>
//#include <string.h>


using namespace std;

void main()
{
	// ��ȡsample_points.txt����ȡ����������
	vector<Pnt> vlist;
	ifstream myfile("sample_points.txt");
	if(myfile.is_open())
	{
		string line;
		while(getline(myfile, line))
		{
			// ����ȡrow_strת��Ϊchar*����
			char* line_char = new char[strlen(line.c_str())+1];
			strcpy(line_char, line.c_str());
			
			// �����Ž����ַ����ָ�
			char* r = strtok(line_char, ",");
			string x_str(r);
			r = strtok(NULL, ",");
			string y_str(r);

			double x = stod(x_str), y = stod(y_str);
			
			// ����������ӵ������б���
			Pnt p(x, y);
			vlist.push_back(p);
		}
	}

	//// ���������㣬�Գ�����в���
	//vector<Pnt> vlist;
	//Pnt p1(10,20),p2(20,10),p3(30,30),p4(40,50),p5(50,30),p6(40,20);
	//vlist.push_back(p1);vlist.push_back(p2);vlist.push_back(p3);
	//vlist.push_back(p4);vlist.push_back(p5);vlist.push_back(p6);

	// ���������뺯�������в���
	Delaunay dln;
	vector<Triangle> t = dln.IncremInsert(vlist);
	cout<<t.size()<<endl;
	for(int i=0; i<t.size(); i++)
	{
		cout<<"("<<t[i].p1.getX()<<","<<t[i].p1.getY()<<")";
		cout<<"("<<t[i].p2.getX()<<","<<t[i].p2.getY()<<")";
		cout<<"("<<t[i].p3.getX()<<","<<t[i].p3.getY()<<")"<<endl;
	}

	/*Pnt p1(0,0), p2(1,1), p3(2,0);
	Triangle tri(p1,p2,p3);
	Pnt center; double radius;
	tri.CalCircumcircle(center, radius);
	cout<<center.getX()<<","<<center.getY()<<endl;*/

	/*Pnt p1(0,0), p2(1,2), p3(2,0);
	Triangle tri(p1,p2,p3);

	Pnt op, ap1, ap2; Edge e;
	if(tri.IsObtuseTriangle(op, ap1, ap2, e))
	{
		cout<<"..."<<endl;	
	}*/
}