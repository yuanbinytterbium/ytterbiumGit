#pragma once 
#include "opencv2\core\core.hpp"
using namespace cv;
class  cProcessFunction 
{
public:
	static int signalContoursJudge(Mat  binaryImage,CvRect theRect);   //��״��⣬�Ƿ�Ϊ������
	static void   getImgAboutContours(Mat &binImg,Mat &MarkImg ,vector<vector<Point> > &theContours);  //
	//У��ͬһ�е�����
	static bool check2Rect310190117(Rect &r1, Rect &r2, int theLevel); //
	static bool check1cent310190117(Rect &r1, Rect &r2);
	static bool check3cent311290117(Rect &r0, Rect &r1, Rect &r2);
	static bool cProcessFunction::check2cent311290117(Rect &r0, Rect &r1);
};

struct SORTLAYERSTRUCT
{
	int XAverage;     //ƽ��x������
	int indexOfLayer;  //����
};

//����
class cLayer 
{
public:
	vector <Point> m_vector_LayerPoint;
	int   m_i_PointCentXAverage;   //ƽ��x����
	int   m_i_PointCentXMax;       //�������
	int   m_i_PointCentXMin;       //��С����
	int   m_i_CentSum;             //��Xֵ
	void  Caclute();    //��ȡƽ������
};