#pragma once 
#include "opencv2\core\core.hpp"
using namespace cv;
class  cProcessFunction 
{
public:
	static int signalContoursJudge(Mat  binaryImage,CvRect theRect);   //��״��⣬�Ƿ�Ϊ������
	static void   getImgAboutContours(Mat &binImg,Mat &MarkImg ,vector<vector<Point> > &theContours);  //
};