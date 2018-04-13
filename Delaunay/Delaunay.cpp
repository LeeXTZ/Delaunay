#include "Delaunay.h"


Delaunay::Delaunay(void)
{
}


Delaunay::~Delaunay(void)
{
}

// �������㷨ʵ��
vector<Triangle> Delaunay::IncremInsert(vector<Pnt> vertexList)
{
	vector<Triangle> triangleList;

	// ��ȡx,y��min��maxֵ
	vector<Pnt>::iterator iter;
	double Xmin=-1, Ymin=-1, Xmax=0, Ymax=0;
	for(iter=vertexList.begin(); iter!=vertexList.end(); iter++)
	{
		//Xmin=-1, Ymin=-1;
		if(Xmin==-1||(iter->getX())<Xmin)
			Xmin=iter->getX();
		if(Ymin==-1||iter->getY()<Ymin)
			Ymin=iter->getY();

		//Xmax=0, Ymax=0;
		if(iter->getX()>Xmax)
			Xmax=iter->getX();
		if(iter->getY()>Ymax)
			Ymax=iter->getY();
	}

	// ����SuperTriangle�����������Σ�
	double half = (Xmax-Xmin)/2; // ���x �� ��Сx ����һ��
	double Xmid = Xmin + half, Ymid = Ymin; // �ױ��е�����

	double Xrd = Xmid + 2*half + 10, Yrd = Ymin-10;
	double Xld = Xmid - 2*half - 10, Yld = Ymin-10;
	double Xup = Xmid, Yup = Ymax+(Ymax-Ymin);

	Pnt prd(Xrd,Yrd), pld(Xld,Yld), pup(Xup,Yup);
	
	vertexList.push_back(prd);
	vertexList.push_back(pld);
	vertexList.push_back(pup);
	
	Triangle superTri(prd, pld, pup);
	
	triangleList.push_back(superTri);

	vector<Pnt>::iterator i_p;
	for(i_p=vertexList.begin(); i_p!=vertexList.end(); i_p++)
	{
		//��ʼ�� edge buffer
		vector<Edge> edgeBuffer;
		//vector<Pnt> pntBuffer;

		vector<Triangle>::iterator i_t;
		for(i_t=triangleList.begin(); i_t!=triangleList.end(); ) //error??
		{
			// �������������ԲԲ�ĺͰ뾶
			Pnt center; double radius;
			i_t->CalCircumcircle(center, radius);
			// ����������Բ�ڣ��������ε������߼ӵ�edgeBuffer�У�����ǰ�����δ�trangleList��ɾ��
			if(i_p->getDist(center)<=radius)
			{
				/*Pnt oP, aP1, aP2; Edge longEdge;
				// �ж��������Ƿ��Ƕ۽�������
				if(i_t->IsObtuseTriangle(oP, aP1, aP2, longEdge))
				{
					// �жϵ�ǰ������������ԲԲ���Ƿ���ͬһ��
					// aP1->aP2 | aP1->center | aP1->i_p
					double ax = aP2.getX()-aP1.getX(); double ay = aP2.getY()-aP1.getY();
					double bx = center.getX()-aP1.getX(); double by = center.getY()-aP1.getY();
					double cx = i_p->getX()-aP1.getX(); double cy = i_p->getY()-aP1.getY();
					
					if((ax*by - ay*bx)*(ax*cy - ay*cx) > 0)
					{
						if(i_t->e1 == longEdge)
						{
							edgeBuffer.push_back(i_t->e2);
							edgeBuffer.push_back(i_t->e3);
						}
						else if(i_t->e2 == longEdge)
						{
							edgeBuffer.push_back(i_t->e1);
							edgeBuffer.push_back(i_t->e3);
						}
						else if(i_t->e3 == longEdge)
						{
							edgeBuffer.push_back(i_t->e1);
							edgeBuffer.push_back(i_t->e2);
						}
					}
				}
				else
				{
					edgeBuffer.push_back(i_t->e1);
					edgeBuffer.push_back(i_t->e2);
					edgeBuffer.push_back(i_t->e3);
				}*/

				edgeBuffer.push_back(i_t->e1);
				edgeBuffer.push_back(i_t->e2);
				edgeBuffer.push_back(i_t->e3);
				i_t = triangleList.erase(i_t);
			}
			else
				i_t++;

		}

		/*// ��edgeBuffer�еı߽���ȥ��
		for(int fst=0; fst<edgeBuffer.size(); fst++)
		{
			for(int snd=fst+1; snd<edgeBuffer.size(); snd++)
			{
				if(edgeBuffer[snd]==edgeBuffer[fst])
				{
					edgeBuffer.erase(edgeBuffer.begin()+snd);
				}
			}
		}*/


		// ȥ��edgeBuffer���������ظ��ı�(����ֻ��ȥ���ظ����������е�һ��)
		for(int fst=0; fst<edgeBuffer.size(); fst++)
		{
			bool isDoubly = false;

			for(int snd=fst+1; snd<edgeBuffer.size(); snd++)
			{
				if(edgeBuffer[snd]==edgeBuffer[fst])
				{
					isDoubly = true;
					edgeBuffer.erase(edgeBuffer.begin()+snd);
				}
			}

			if(isDoubly)
			{
				edgeBuffer.erase(edgeBuffer.begin()+fst);
			}
		}

		// ��edgeBuffer�еı��뵱ǰ�ĵ���ϳ����������β���ӵ�trangleList
		vector<Edge>::iterator i_e2;
		for(i_e2=edgeBuffer.begin(); i_e2!=edgeBuffer.end(); i_e2++)
		{
			Triangle t(*i_p, i_e2->p1, i_e2->p2);
			triangleList.push_back(t);
		}

	}

	// ɾ��triangleList��ʹ�� ���������ζ��� ��������
	vector<Triangle>::iterator i_t_;
	for(i_t_=triangleList.begin(); i_t_!=triangleList.end(); )
	{
		if((i_t_->p1.getX()==prd.getX()&&i_t_->p1.getY()==prd.getY()) ||(i_t_->p2.getX()==prd.getX()&&i_t_->p2.getY()==prd.getY()) ||(i_t_->p3.getX()==prd.getX()&&i_t_->p3.getY()==prd.getY()))
			i_t_ = triangleList.erase(i_t_);

		else if((i_t_->p1.getX()==pld.getX()&&i_t_->p1.getY()==pld.getY()) ||(i_t_->p2.getX()==pld.getX()&&i_t_->p2.getY()==pld.getY()) ||(i_t_->p3.getX()==pld.getX()&&i_t_->p3.getY()==pld.getY()))
			i_t_ = triangleList.erase(i_t_);

		else if((i_t_->p1.getX()==pup.getX()&&i_t_->p1.getY()==pup.getY()) ||(i_t_->p2.getX()==pup.getX()&&i_t_->p2.getY()==pup.getY()) ||(i_t_->p3.getX()==pup.getX()&&i_t_->p3.getY()==pup.getY()))
			i_t_ = triangleList.erase(i_t_);
		else
			i_t_++;
	}

	// ��vertextList��ɾ�����������εĶ���
	vector<Pnt>::iterator i_v;
	for(i_v=vertexList.begin(); i_v!=vertexList.end(); )
	{
		if((i_v->getX()==prd.getX()&&i_v->getY()==prd.getY())||
			(i_v->getX()==pld.getX()&&i_v->getY()==pld.getY())||
			(i_v->getX()==pup.getX()&&i_v->getY()==pup.getY()))
			i_v = vertexList.erase(i_v);
		else
			i_v++;
	}

	return triangleList;
}
