#pragma once 
#include "opencv2\core\core.hpp"
using namespace cv;
class cMultiLayers;
class  cProcessFunction 
{
public:
	static int signalContoursJudge(Mat  binaryImage,CvRect theRect);   //形状检测，是否为三角形
	static void   getImgAboutContours(Mat &binImg,Mat &MarkImg ,vector<vector<Point> > &theContours);  //
	//校验同一列的轮廓
	static bool check2Rect310190117(Rect &r1, Rect &r2, int theLevel); //
	static bool check1cent310190117(Rect &r1, Rect &r2);
	static bool check3cent311290117(Rect &r0, Rect &r1, Rect &r2);
	static bool check2cent311290117(Rect &r0, Rect &r1);
	static bool delateSomeClass1101710119(Mat &graySrc, Mat &m_mat_binContourImg_, cMultiLayers & theSetOfserial);
};

struct SORTLAYERSTRUCT
{
	int XAverage;     //平均x的坐标
	int indexOfLayer;  //层的坐标
};

//单层
class cLayer 
{
public:
	cLayer();   //单层构造函数
	vector <int>  m_vector_contoursIndex; //该层中所有轮廓对应allcontours的index 
	vector <Rect> m_vecotr_contoursRect; //该层中所有的轮廓的rect
	vector <Point> m_vector_LayerPoint;   //原有的轮廓中心点
	int   m_i_PointCentXAverage;   //平均x坐标
	int   m_i_PointCentXMax;       //最大坐标
	int   m_i_PointCentXMin;       //最小坐标
	int   m_i_CentSum;             //总X值


	int m_i_FitPointCentXAverage;   //平均X值
	int m_i_FitPointCentXMax;      //最大坐标
	int m_i_FitPointCentXMin;     //最小坐标
	int m_i_FitPointXSum;          //X总和
	vector <Point> m_vector_FitLayerCentPoint;  //自适应线上对应的各点
	double m_d_fitLine_b;   //直线b值 y = kx + b 
	double m_d_fitLine_k;   //直线k值

	bool  m_b_LayerLegal;  //该层是否有效
	int   m_i_LayerId;     //该层在整个层次中的顺序
	void  Caclute();    //获取平均坐标
	void  GetFitLine();  //线性化
	void  AddMember(int &layerIndex,Rect &ContoursRect,Point &contoursCentPoint);

};


class  cMultiLayers 
{
public:
	vector <vector <Point>>  * m_pointvecvec_allContours; //指向所有轮廓的点
	vector <Rect>  * m_pointvec_allContoursRect;          //指向所有轮廓的矩形
	vector <Point> * m_pointvec_allContoursCent;          //指向所有的轮廓中心点
	vector<vector <int>> * m_pointVector_indexOfAllLayer; //所有层对应的allcontours中的index

	vector <int>   m_vector_sortIndexOfLayer;  //对应的经过sort排序后的层的index
	vector <bool>  m_vector_Layerstatus;      //各层状态  是否为有效层(对应m_vector_sortIndexOfLayer)
	vector <int>   m_vector_indexLegal;        //合法的层
	vector <Point> m_vector_SortLayer;        //用于对所有层进行排序所用的vector
	vector <cLayer>m_vector_clayer_AllLayer; //存放所有单层对象的vector;

	static bool SortCompareFunction(Point & one,Point &two);
	void    SortLayer();  
	void    ArrangeLayer();  //整理所有层
	void   AddMember(cLayer & inputLayer);
	int   size();
	cLayer * at(int i);
};