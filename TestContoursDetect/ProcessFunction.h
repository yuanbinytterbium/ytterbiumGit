#pragma once 
#include "opencv2\core\core.hpp"
using namespace cv;
class  cProcessFunction 
{
public:
	static int signalContoursJudge(Mat  binaryImage,CvRect theRect);   //形状检测，是否为三角形
	static void   getImgAboutContours(Mat &binImg,Mat &MarkImg ,vector<vector<Point> > &theContours);  //
	//校验同一列的轮廓
	static bool check2Rect310190117(Rect &r1, Rect &r2, int theLevel); //
	static bool check1cent310190117(Rect &r1, Rect &r2);
	static bool check3cent311290117(Rect &r0, Rect &r1, Rect &r2);
	static bool cProcessFunction::check2cent311290117(Rect &r0, Rect &r1);
};

struct SORTLAYERSTRUCT
{
	int XAverage;     //平均x的坐标
	int indexOfLayer;  //层数
};

//单层
class cLayer 
{
public:
	vector <Point> m_vector_LayerPoint;   //原有的轮廓中心点
	int   m_i_PointCentXAverage;   //平均x坐标
	int   m_i_PointCentXMax;       //最大坐标
	int   m_i_PointCentXMin;       //最小坐标
	int   m_i_CentSum;             //总X值


	int m_i_FitPointCentXAverage;   //平均X值
	int m_i_FitPointCentXMax;      //最大坐标
	int m_i_FitPointCentXMinj;     //最小坐标
	int m_i_FitPointXSum;          //X总和
	vector <Point> m_vector_FitLayerCentPoint;  //自适应线上对应的各点
	double m_d_fitLine_b;   //直线b值 y = kx + b 
	double m_d_fitLine_k;   //直线k值

	void  Caclute();    //获取平均坐标
	void  GetFitLine();  //线性化
};