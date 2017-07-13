#pragma once 
#include "opencv2\core\core.hpp"
using namespace cv;
class  cProcessFunction 
{
public:
	static int signalContoursJudge(Mat  binaryImage,CvRect theRect);   //形状检测，是否为三角形
	static void   getImgAboutContours(Mat &binImg,Mat &MarkImg ,vector<vector<Point> > &theContours);  //
};