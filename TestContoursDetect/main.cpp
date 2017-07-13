#pragma  once 
#include <iostream>
#include "highgui.h"
#include "opencv2/opencv.hpp"
#include "opencv/cv.h" 
#include "opencv2\imgproc\imgproc.hpp"
#include "ProcessFunction.h"
//#include <string>
using namespace std;
using namespace  cv;

int main()
{

	//const char *imgpath = "stitch1.bmp";
	string tp_imagePath ="C:/VC/测试/TestContoursDetect/Debug/stitch1.bmp";
	//IplImage *img = cvLoadImage(imgpath);//加载图像文件至内存
	//Mat imag(cvSize(img->width,img->height),CV_8UC1,img->imageDataOrigin);
	Mat image;
	image = imread(tp_imagePath);
	if (NULL == image.data) 
	{
		//MessageBox(NULL,"s","s",1);
		cout<<"empty"<<endl;
	}
    float	tp_f_sizeScaler = 1.3f;
	Mat image_Resized;
	//改变其大小
	resize(image, image_Resized, cvSize(image.cols*tp_f_sizeScaler, image.rows*tp_f_sizeScaler*1.3f),0,0,2);
	image.release();
	namedWindow("Example1",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
	imshow("Example1",image_Resized);
	cvWaitKey(0);//等待用户触发按键
	destroyWindow("Example1");
	//imag.release();
	Mat image_Gray;
	Mat image_Color;
	//对其大小判断并剪裁以及生成黑白图
	if (image_Resized.rows > 420)
	{
		image_Resized(Rect(0, image_Resized.rows / 2.0 - 210, image_Resized.cols, 420)).copyTo(image_Color);
		cvtColor(image_Resized(Rect(0, image_Resized.rows / 2.0 - 210, image_Resized.cols, 420)), image_Gray, CV_BGR2GRAY);
	}
	else 
	{
		image_Resized.copyTo(image_Color);
		cvtColor(image_Resized,image_Gray,CV_BGR2GRAY);
	}
	//显示裁剪的图像
	namedWindow("Example4",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
	imshow("Example4",image_Color);
	cvWaitKey(0);//等待用户触发按键
	destroyWindow("Example4");
	//image_Resized.release();
	//模糊图像
	Mat  image_Gray_Blur;
	blur (image_Gray,image_Gray_Blur,cvSize(2,3));
	namedWindow("Example2",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
	imshow("Example2",image_Gray_Blur);
	cvWaitKey(0);//等待用户触发按键
	destroyWindow("Example2");
	//二值化
	Mat  image_Gray_adaptiveThreshold;
	adaptiveThreshold(image_Gray_Blur, image_Gray_adaptiveThreshold, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, 11, 5);
	int tp_sizeofBinaryHeight = image_Gray_adaptiveThreshold.size().height;
	int tp_sizeofBinaryWidth = image_Gray_adaptiveThreshold.size().width;
	int tp_type = image_Gray_adaptiveThreshold.type();
	int tp_pointOfImage = image_Gray_adaptiveThreshold.at<uchar>(20,15);
	namedWindow("Example3",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
	imshow("Example3",image_Gray_Blur);
	cvWaitKey(0);//等待用户触发按键
	destroyWindow("Example3");
	//创造轮廓
	Mat image_element1 = getStructuringElement(MORPH_RECT, Size(3, 3));
	//形态学操作
	Mat image_GetElementl;
	morphologyEx(image_Gray_adaptiveThreshold, image_GetElementl, MORPH_OPEN, image_element1);
	namedWindow("Example5",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
	imshow("Example5",image_GetElementl);
	cvWaitKey(0);//等待用户触发按键
	destroyWindow("Example5");
	//发现轮廓
	vector<vector<Point> > tp_contours;
	cv::vector<Vec4i> tp_hierarchy;
	findContours(image_GetElementl,tp_contours,tp_hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE,Point(0, 0));
	Scalar color( rand()&255, rand()&255, rand()&255 );
	//将所有获取的轮廓画上去
	//drawContours(image_Color,tp_contours,-1,color,CV_FILLED,8,tp_hierarchy);
	namedWindow("Example6",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
	imshow("Example6",image_Color);
	cvWaitKey(0);//等待用户触发按键
	destroyWindow("Example6");
	//对轮廓进行筛选
	vector<vector<Point> > tp_contours_filter;
	vector<Point>		   tp_vector_centofContours;
	vector<Rect>		   tp_vector_rect;
	vector<vector<Point> >  tp_hull(tp_contours.size());
	//存储较大的轮廓
	int tp_bigContoursNumber = 0;  //较大轮廓的数量
	int tp_i_bigContoursOneNumber = 0;
	int tp_i_bigContoursTwoNumber = 0;
	vector <int >    tp_vector_contoursIndex_bigone;
	vector <int >    tp_vector_contoursIndex_bigtwo;
	//for循环中临时使用
	double tp_contourArea;
	Rect tp_contoursRect;
	double tp_contoursRectArea;
	int  tp_contoursHeight;
	int  tp_contoursWidth;
	Point tp_centOfContours;
	//对轮廓进行分类,较大轮廓分两批处理
	for (int i =0; i < tp_contours.size();i++)
	{
		tp_contourArea = fabs(contourArea(tp_contours[i]));
		tp_contoursRect = boundingRect(tp_contours[i]);
		tp_contoursRectArea = (tp_contoursRect.height)*(tp_contoursRect.width);
		tp_contoursHeight = tp_contoursRect.height;
		tp_contoursWidth = tp_contoursRect.width;
		tp_centOfContours = Point(tp_contoursRect.x + tp_contoursRect.width / 2, tp_contoursRect.y + tp_contoursRect.height / 2);
		if (tp_contourArea<400 && tp_contourArea>6 && tp_contoursHeight<24 && tp_contoursWidth<21 && tp_contoursRectArea<700 && tp_contoursRectArea>6){
			//满足条件则为符合要求的正确轮廓
			tp_contours_filter.push_back(tp_contours[i]);
			tp_vector_centofContours.push_back(tp_centOfContours);
			tp_vector_rect.push_back(tp_contoursRect);
		}
		if (tp_contourArea >= 400 || (tp_contoursHeight >= 24 && tp_contoursWidth >= 3) || (tp_contoursHeight >= 3 && tp_contoursWidth >= 21)){
			tp_bigContoursNumber++;

			if ((tp_contoursWidth >= 21) && (tp_contoursWidth <= 48) && (tp_contoursHeight <= 24)){
				tp_i_bigContoursOneNumber++;
				//drawContours(binSrc4, contours, i, cvScalar(255, 255, 255), CV_FILLED);
				tp_vector_contoursIndex_bigone.push_back(i);
			}

			else{
				//
				tp_i_bigContoursTwoNumber++;
				//drawContours(binSrc7, contours, i, cvScalar(255, 255, 255), CV_FILLED);
				tp_vector_contoursIndex_bigtwo.push_back(i);
			}
		}
	}
	//正确的轮廓显示
	Mat tp_mat_image_normal = Mat::zeros(image_Gray.size(), CV_8UC1);
	//drawContours(tp_mat_image_normal,tp_contours_filter,-1,Scalar(255,255,255),CV_FILLED);
	//namedWindow("Example7",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
	//imshow("Example7",tp_mat_image_normal);
	//cvWaitKey(0);//等待用户触发按键
	//destroyWindow("Example7");

	//轮廓分类完成后  需要对较大轮廓进行单独处理
	Mat  tp_mat_image_bigContoursOne =  Mat::zeros(image_Gray.size(), CV_8UC1);
	if ( tp_vector_contoursIndex_bigone.size() > 0 )
	{
		for (int i =0 ; i <tp_vector_contoursIndex_bigone.size(); i++ )
		{
			drawContours(tp_mat_image_bigContoursOne,tp_contours,tp_vector_contoursIndex_bigone[i],Scalar(255),CV_FILLED);
		}
	}
	tp_vector_contoursIndex_bigone.clear();
	namedWindow("Example7",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
	imshow("Example7",tp_mat_image_bigContoursOne);
	cvWaitKey(0);//等待用户触发按键
	destroyWindow("Example7");

	Mat  tp_mat_image_bigContoursTwo =  Mat::zeros(image_Gray.size(), CV_8UC1);
	if (tp_vector_contoursIndex_bigtwo.size() > 0) {
		for (int i =0 ; i < tp_vector_contoursIndex_bigtwo.size(); i++ )
		{
			drawContours(tp_mat_image_bigContoursTwo,tp_contours,tp_vector_contoursIndex_bigtwo[i],Scalar(255),CV_FILLED);
		}
	}
	tp_vector_contoursIndex_bigtwo.clear();
	namedWindow("Example8",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
	imshow("Example8",tp_mat_image_bigContoursTwo);
	cvWaitKey(0);//等待用户触发按键
	destroyWindow("Example8");
	//第一批较大轮廓
	if (tp_vector_contoursIndex_bigone.size() > 0 ){	
		Mat tp_imageToTransform;
		Mat element1 = getStructuringElement(MORPH_RECT, Size(3, 1));
		morphologyEx(tp_mat_image_bigContoursOne, tp_imageToTransform, MORPH_CLOSE, element1);
		tp_imageToTransform.copyTo(tp_mat_image_bigContoursOne);
		Mat element2 = getStructuringElement(MORPH_RECT, Size(4, 4));
		morphologyEx(tp_mat_image_bigContoursOne, tp_imageToTransform, MORPH_OPEN, element2);
		tp_imageToTransform.copyTo(tp_mat_image_bigContoursOne);
		tp_imageToTransform.release();

		tp_contours.clear();
		tp_hierarchy.clear();
		findContours(tp_mat_image_bigContoursOne,tp_contours,tp_hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));
		for (int i = 0; i< tp_contours.size(); i ++ ){//
			tp_contourArea = fabs(contourArea(tp_contours[i]));
			tp_contoursRect = boundingRect(tp_contours[i]);
			tp_contoursRectArea = (tp_contoursRect.height)*(tp_contoursRect.width);
			tp_contoursHeight = tp_contoursRect.height;
			tp_contoursWidth = tp_contoursRect.width;
			tp_centOfContours = Point(tp_contoursRect.x + tp_contoursRect.width / 2, tp_contoursRect.y + tp_contoursRect.height / 2);
			//对轮廓进行判断
			if (tp_contourArea < 400 && tp_contourArea > 6 && tp_contoursHeight < 24 && tp_contoursWidth < 24 && tp_contoursRectArea < 700 && tp_contoursRectArea>6){
				tp_contours_filter.push_back(tp_contours[i]);
				tp_vector_centofContours.push_back(tp_centOfContours);
				tp_vector_rect.push_back(tp_contoursRect);
			}
			else {//检测多边形
				convexHull(tp_contours[i],tp_hull[i],false);
				Mat tp_convexhull = Mat::zeros(image_Gray.size(),CV_8UC1);
				drawContours(tp_convexhull,tp_hull,i,Scalar(255),CV_FILLED,8, vector<Vec4i>(), 0, Point());
				int tp_int = tp_convexhull.rows;
				tp_int = tp_convexhull.cols;
				//对检测到的多边形进行判断
				int tp_checktriangle = cProcessFunction::signalContoursJudge(tp_convexhull,tp_contoursRect);
				if (tp_checktriangle){
					//检测到是三角形
					tp_contours_filter.push_back(tp_contours[i]);
					tp_vector_centofContours.push_back(tp_centOfContours);
					tp_vector_rect.push_back(tp_contoursRect);
				}
				else 
				{
					tp_vector_contoursIndex_bigone.push_back(i);
				}
				//namedWindow("Example三角",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
				//imshow("Example三角",tp_convexhull);
				//cvWaitKey(0);//等待用户触发按键
				//destroyWindow("Example三角");
			}
		}
		namedWindow("Example分割轮廓",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
		imshow("Example分割轮廓",tp_mat_image_bigContoursOne);
		cvWaitKey(0);//等待用户触发按键
		destroyWindow("Example分割轮廓");
	}

	//再次对无法辨别的轮廓进行处理
	//位置10
	if (tp_vector_contoursIndex_bigone.size() > 0)
	{
		for (int i =0 ; i < tp_vector_contoursIndex_bigone.size(); i++ )
		{
			drawContours(tp_mat_image_bigContoursOne,tp_contours,tp_vector_contoursIndex_bigone[i],Scalar(255),CV_FILLED);
		}

		namedWindow("Example位置10",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
		imshow("Example位置10",tp_mat_image_bigContoursOne);
		cvWaitKey(0);//等待用户触发按键
		destroyWindow("Example位置10");

		tp_contours.clear(); //清空轮廓
		tp_hierarchy.clear();
		findContours(tp_mat_image_bigContoursOne, tp_contours, tp_hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));
		tp_mat_image_bigContoursOne = Mat::zeros(image_Gray.size(), CV_8UC1);
		for (int i = 0; i < tp_contours.size(); i++){

			tp_contourArea = fabs(contourArea(tp_contours[i]));
			tp_contoursRect = boundingRect(tp_contours[i]);
			tp_contoursRectArea = (tp_contoursRect.height)*(tp_contoursRect.width);
			tp_contoursHeight = tp_contoursRect.height;
			tp_contoursWidth = tp_contoursRect.width;
			tp_centOfContours = Point(tp_contoursRect.x + tp_contoursRect.width / 2, tp_contoursRect.y + tp_contoursRect.height / 2);

			Point  startr = Point(tp_contoursRect.x + tp_contoursRect.width / 2, tp_contoursRect.y);
			Point  endr = Point(tp_contoursRect.x + tp_contoursRect.width / 2, tp_contoursRect.y + tp_contoursRect.height);
			cv::line(tp_mat_image_bigContoursOne, startr, endr, Scalar(0, 0, 0), 3);
		}
		//位置11
		namedWindow("Example位置11",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
		imshow("Example位置11",tp_mat_image_bigContoursOne);
		cvWaitKey(0);//等待用户触发按键
		destroyWindow("Example位置11");
		tp_contours.clear(); //清空轮廓
		tp_hierarchy.clear();
		tp_i_bigContoursOneNumber = 0;
		findContours(tp_mat_image_bigContoursOne, tp_contours, tp_hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));
		tp_mat_image_bigContoursOne = Mat::zeros(image_Gray.size(), CV_8UC1);
		for (int i = 0; i < tp_contours.size(); i++){

			tp_contourArea = fabs(contourArea(tp_contours[i]));
			tp_contoursRect = boundingRect(tp_contours[i]);
			tp_contoursRectArea = (tp_contoursRect.height)*(tp_contoursRect.width);
			tp_contoursHeight = tp_contoursRect.height;
			tp_contoursWidth = tp_contoursRect.width;
			tp_centOfContours = Point(tp_contoursRect.x + tp_contoursRect.width / 2, tp_contoursRect.y + tp_contoursRect.height / 2);
			if (tp_contourArea<400 && tp_contourArea>6 && tp_contoursHeight<24 && tp_contoursWidth<21 && tp_contoursRectArea<700 && tp_contoursRectArea>6){//故意增加了取值范围，小于24都可以，由上面的80决定的
				tp_contours_filter.push_back(tp_contours[i]);
				tp_vector_centofContours.push_back(tp_centOfContours);
				tp_vector_rect.push_back(tp_contoursRect);
			}
			if ((tp_contourArea >= 400 || (tp_contoursHeight >= 24 && tp_contoursWidth >= 3) || (tp_contoursHeight >= 3 && tp_contoursWidth >= 21)) ){
				tp_i_bigContoursOneNumber++;
				drawContours(tp_mat_image_bigContoursOne, tp_contours, i, cvScalar(255, 255, 255), CV_FILLED);
			}
		}
		//位置12
		namedWindow("Example位置12",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
		imshow("Example位置12",tp_mat_image_bigContoursOne);
		cvWaitKey(0);//等待用户触发按键
		destroyWindow("Example位置12");
	
	}

	//第二批较大轮廓
	if (tp_i_bigContoursTwoNumber != 0){
		erode(tp_mat_image_bigContoursTwo, tp_mat_image_bigContoursTwo, getStructuringElement(MORPH_RECT, Size(4, 1)));
		Mat element2 = getStructuringElement(MORPH_RECT, Size(2, 5));
		morphologyEx(tp_mat_image_bigContoursTwo, tp_mat_image_bigContoursTwo, MORPH_OPEN, element2);
		tp_contours.clear();
		tp_hierarchy.clear();
		tp_i_bigContoursTwoNumber = 0; 
		findContours(tp_mat_image_bigContoursTwo, tp_contours, tp_hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));
		tp_mat_image_bigContoursTwo = Mat::zeros(image_Gray.size(), CV_8UC1);
		for (int i = 0; i < tp_contours.size(); i++){

			tp_contourArea = fabs(contourArea(tp_contours[i]));
			tp_contoursRect = boundingRect(tp_contours[i]);
			tp_contoursRectArea = (tp_contoursRect.height)*(tp_contoursRect.width);
			tp_contoursHeight = tp_contoursRect.height;
			tp_contoursWidth = tp_contoursRect.width;
			tp_centOfContours = Point(tp_contoursRect.x + tp_contoursRect.width / 2, tp_contoursRect.y + tp_contoursRect.height / 2);
			if (tp_contourArea<400 && tp_contourArea>6 && tp_contoursHeight<24 && tp_contoursWidth<21 && tp_contoursRectArea<700 && tp_contoursRectArea>6){//故意增加了取值范围，小于24都可以，由上面的80决定的
				//if (tmparea<maxContourArea && tmparea>minContourArea && contourL<24){
				tp_contours_filter.push_back(tp_contours[i]);
				tp_vector_centofContours.push_back(tp_centOfContours);
				tp_vector_rect.push_back(tp_contoursRect);
			}
			//if ((tmparea >= maxContourArea || (contourL >= 24) || (contourk >= 24)) && isBig2Little){
			if (tp_contourArea >= 400 || (tp_contoursHeight >= 24 && tp_contoursWidth >= 3) || (tp_contoursHeight >= 3 && tp_contoursWidth >= 21)){
				//if ((tmparea >= maxContourArea || contourL >= 24) && isBig2Little){
				tp_i_bigContoursTwoNumber++;
				drawContours(tp_mat_image_bigContoursTwo, tp_contours, i, cvScalar(255, 255, 255), CV_FILLED);
			}
		}
	}

	//位置13
	namedWindow("Example位置13",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
	imshow("Example位置13",tp_mat_image_bigContoursTwo);
	cvWaitKey(0);//等待用户触发按键
	destroyWindow("Example位置13");
	if (tp_i_bigContoursTwoNumber != 0){

		tp_contours.clear();
		tp_hierarchy.clear();
		tp_i_bigContoursTwoNumber = 0; 
		findContours(tp_mat_image_bigContoursTwo, tp_contours, tp_hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));
		//bigContoursNum = 0;
		tp_mat_image_bigContoursTwo = Mat::zeros(image_Gray.size(), CV_8UC1);
		for (int i = 0; i < tp_contours.size(); i++){
			tp_contourArea = fabs(contourArea(tp_contours[i]));
			tp_contoursRect = boundingRect(tp_contours[i]);
			tp_contoursRectArea = (tp_contoursRect.height)*(tp_contoursRect.width);
			tp_contoursHeight = tp_contoursRect.height;
			tp_contoursWidth = tp_contoursRect.width;
			tp_centOfContours = Point(tp_contoursRect.x + tp_contoursRect.width / 2, tp_contoursRect.y + tp_contoursRect.height / 2);

			if (tp_contoursHeight>(1.6 *tp_contoursWidth)){
				Point  startrhen = Point(tp_contoursRect.x, tp_contoursRect.y + tp_contoursRect.height / 2);
				Point  endrhen = Point(tp_contoursRect.x + tp_contoursRect.width, tp_contoursRect.y + tp_contoursRect.height / 2);
				cv::line(tp_mat_image_bigContoursTwo, startrhen, endrhen, Scalar(0, 0, 0), 2);
			}
			if ((0.5*tp_contoursHeight)>(1.6 *tp_contoursWidth)){
				Point  startrhen1 = Point(tp_contoursRect.x, tp_contoursRect.y + tp_contoursRect.height / 4);
				Point  endrhen1 = Point(tp_contoursRect.x + tp_contoursRect.width, tp_contoursRect.y + tp_contoursRect.height / 4);
				cv::line(tp_mat_image_bigContoursTwo, startrhen1, endrhen1, Scalar(0, 0, 0), 2);

				Point  startrhen2 = Point(tp_contoursRect.x, tp_contoursRect.y + tp_contoursRect.height * 3 / 4);
				Point  endrhen2 = Point(tp_contoursRect.x + tp_contoursRect.width, tp_contoursRect.y + tp_contoursRect.height * 3 / 4);
				cv::line(tp_mat_image_bigContoursTwo, startrhen2, endrhen2, Scalar(0, 0, 0), 2);
			}
		}


		//位置14
		namedWindow("Example位置14",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
		imshow("Example位置14",tp_mat_image_bigContoursTwo);
		cvWaitKey(0);//等待用户触发按键
		destroyWindow("Example位置14");


		//继续处理
		tp_contours.clear();
		tp_hierarchy.clear();
		tp_i_bigContoursTwoNumber = 0;
		findContours(tp_mat_image_bigContoursTwo, tp_contours, tp_hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));
		tp_mat_image_bigContoursTwo = Mat::zeros(image_Gray.size(), CV_8UC1);
		for (int i = 0; i < tp_contours.size(); i++){

			tp_contourArea = fabs(contourArea(tp_contours[i]));
			tp_contoursRect = boundingRect(tp_contours[i]);
			tp_contoursRectArea = (tp_contoursRect.height)*(tp_contoursRect.width);
			tp_contoursHeight = tp_contoursRect.height;
			tp_contoursWidth = tp_contoursRect.width;
			tp_centOfContours = Point(tp_contoursRect.x + tp_contoursRect.width / 2, tp_contoursRect.y + tp_contoursRect.height / 2);
			if (tp_contourArea<400 && tp_contourArea>6 && tp_contoursHeight<24 && tp_contoursWidth<21 && tp_contoursRectArea<700 && tp_contoursRectArea>6){//故意增加了取值范围，小于24都可以，由上面的80决定的
				//if (tmparea<maxContourArea && tmparea>minContourArea && contourL<24){
				tp_contours_filter.push_back(tp_contours[i]);
				tp_vector_centofContours.push_back(tp_centOfContours);
				tp_vector_rect.push_back(tp_contoursRect);
			}
			//if ((tmparea >= maxContourArea || (contourL >= 24) || (contourk >= 24)) && isBig2Little){
			if (tp_contourArea >= 400 || (tp_contoursHeight >= 24 && tp_contoursWidth >= 3) || (tp_contoursHeight >= 3 && tp_contoursWidth >= 21)){
				//if ((tmparea >= maxContourArea || contourL >= 24) && isBig2Little){
				tp_i_bigContoursTwoNumber++;
				drawContours(tp_mat_image_bigContoursTwo,tp_contours, i, cvScalar(255, 255, 255), CV_FILLED);
			}
		}
	}


	//位置15
	namedWindow("Example位置15",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
	imshow("Example位置15",tp_mat_image_bigContoursTwo);
	cvWaitKey(0);//等待用户触发按键
	destroyWindow("Example位置15");
	//以下处理竖直的一列没分开好的
	if (tp_i_bigContoursTwoNumber != 0){

		tp_contours.clear();
		tp_hierarchy.clear();
		findContours(tp_mat_image_bigContoursTwo, tp_contours, tp_hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));
		//bigContoursNum = 0;
		tp_mat_image_bigContoursTwo = Mat::zeros(image_Gray.size(), CV_8UC1);
		for (int i = 0; i < tp_contours.size(); i++){

			tp_contourArea = fabs(contourArea(tp_contours[i]));
			tp_contoursRect = boundingRect(tp_contours[i]);
			tp_contoursRectArea = (tp_contoursRect.height)*(tp_contoursRect.width);
			tp_contoursHeight = tp_contoursRect.height;
			tp_contoursWidth = tp_contoursRect.width;
			tp_centOfContours = Point(tp_contoursRect.x + tp_contoursRect.width / 2, tp_contoursRect.y + tp_contoursRect.height / 2);

			Point  startr = Point(tp_contoursRect.x + tp_contoursRect.width / 2, tp_contoursRect.y);
			Point  endr = Point(tp_contoursRect.x + tp_contoursRect.width / 2, tp_contoursRect.y + tp_contoursRect.height);
			cv::line(tp_mat_image_bigContoursTwo, startr, endr, Scalar(0, 0, 0), 3);
		}
		//继续处理
		tp_contours.clear();
		tp_hierarchy.clear();
		findContours(tp_mat_image_bigContoursTwo, tp_contours, tp_hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));
		tp_i_bigContoursTwoNumber = 0;
		tp_mat_image_bigContoursTwo = Mat::zeros(image_Gray.size(), CV_8UC1);
		for (int i = 0; i < tp_contours.size(); i++){

			tp_contourArea = fabs(contourArea(tp_contours[i]));
			tp_contoursRect = boundingRect(tp_contours[i]);
			tp_contoursRectArea = (tp_contoursRect.height)*(tp_contoursRect.width);
			tp_contoursHeight = tp_contoursRect.height;
			tp_contoursWidth = tp_contoursRect.width;
			tp_centOfContours = Point(tp_contoursRect.x + tp_contoursRect.width / 2, tp_contoursRect.y + tp_contoursRect.height / 2);
			if (tp_contourArea<400 && tp_contourArea>6 && tp_contoursHeight<24 && tp_contoursWidth<21 && tp_contoursRectArea<700 && tp_contoursRectArea>6){//故意增加了取值范围，小于24都可以，由上面的80决定的
				//if (tmparea<maxContourArea && tmparea>minContourArea && contourL<24){
				tp_contours_filter.push_back(tp_contours[i]);
				tp_vector_centofContours.push_back(tp_centOfContours);
				tp_vector_rect.push_back(tp_contoursRect);
			}
			//if ((tmparea >= maxContourArea || (contourL >= 24) || (contourk >= 24)) && isBig2Little){
			if (tp_contourArea >= 400 || (tp_contoursHeight >= 24 && tp_contoursWidth >= 3) || (tp_contoursHeight >= 3 && tp_contoursWidth >= 21)) {
				//if ((tmparea >= maxContourArea || contourL >= 24) && isBig2Little){
				tp_i_bigContoursTwoNumber++;
				drawContours(tp_mat_image_bigContoursTwo, tp_contours, i, cvScalar(255, 255, 255), CV_FILLED);
			}
		}
	}

	for (int count = 0; count<2; count++)
	{
		erode(tp_mat_image_bigContoursTwo, tp_mat_image_bigContoursTwo, getStructuringElement(MORPH_RECT, Size(3, 3)));
		tp_contours.clear();
		tp_hierarchy.clear();
		findContours(tp_mat_image_bigContoursTwo, tp_contours, tp_hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));
		tp_i_bigContoursTwoNumber = 0;
		tp_mat_image_bigContoursTwo = Mat::zeros(image_Gray.size(), CV_8UC1);
		for (int i = 0; i < tp_contours.size(); i++){
			tp_contourArea = fabs(contourArea(tp_contours[i]));
			tp_contoursRect = boundingRect(tp_contours[i]);
			tp_contoursRectArea = (tp_contoursRect.height)*(tp_contoursRect.width);
			tp_contoursHeight = tp_contoursRect.height;
			tp_contoursWidth = tp_contoursRect.width;
			tp_centOfContours = Point(tp_contoursRect.x + tp_contoursRect.width / 2, tp_contoursRect.y + tp_contoursRect.height / 2);
			if (tp_contourArea<400 && tp_contourArea>6 && tp_contoursHeight<24 && tp_contoursWidth<21 && tp_contoursRectArea<700 && tp_contoursRectArea>6){//故意增加了取值范围，小于24都可以，由上面的80决定的
				//if (tmparea<maxContourArea && tmparea>minContourArea && contourL<24){
				tp_contours_filter.push_back(tp_contours[i]);
				tp_vector_centofContours.push_back(tp_centOfContours);
				tp_vector_rect.push_back(tp_contoursRect);
			}
			if (tp_contourArea >= 400 || (tp_contoursHeight >= 24 && tp_contoursWidth >= 3) || (tp_contoursHeight >= 3 && tp_contoursWidth >= 21)) {
				tp_i_bigContoursTwoNumber++;
				drawContours(tp_mat_image_bigContoursTwo, tp_contours, i, cvScalar(255, 255, 255), CV_FILLED);
			}
		}
	}
	tp_mat_image_bigContoursTwo = Mat::zeros(image_Gray.size(),CV_8UC1);
	drawContours(tp_mat_image_bigContoursTwo,tp_contours_filter,-1,Scalar(255),CV_FILLED);
	namedWindow("Example位置最后",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
	imshow("Example位置最后",tp_mat_image_bigContoursTwo);
	cvWaitKey(0);//等待用户触发按键
	destroyWindow("Example位置最后");
	//std::sort(theSortOfContours.begin(), theSortOfContours.end(), SortByM2);
	//针对

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//分割线  对图形的基本轮廓处理已经完成
	Mat ImageAbout_Contours;
	cProcessFunction::getImgAboutContours(image_Gray,ImageAbout_Contours,tp_contours_filter);
	namedWindow("Example轮廓链接",CV_WINDOW_NORMAL);//创建一个名为Example1的窗口
	imshow("Example轮廓链接",ImageAbout_Contours);
	cvWaitKey(0);//等待用户触发按键
	destroyWindow("Example轮廓链接");

	//
	vector <int > tp_IndexOfVector;

	image_Gray.release();
	return 0;
	}
