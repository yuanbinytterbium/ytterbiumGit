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
#define Test 0

int main()
{

	//const char *imgpath = "stitch1.bmp";
	string tp_imagePath ="C:/VC/����/TestContoursDetect/Debug/26stitch-1-501.bmp";
	//IplImage *img = cvLoadImage(imgpath);//����ͼ���ļ����ڴ�
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
	//�ı����С
	resize(image, image_Resized, cvSize(image.cols*tp_f_sizeScaler, image.rows*tp_f_sizeScaler*1.3f),0,0,2);
	image.release();
	namedWindow("Example1",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
	imshow("Example1",image_Resized);
	cvWaitKey(0);//�ȴ��û���������
	destroyWindow("Example1");
	//imag.release();
	Mat image_Gray;
	Mat image_Color;
	//�����С�жϲ������Լ����ɺڰ�ͼ
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
	//��ʾ�ü���ͼ��
#if Test
	namedWindow("Example4",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
	imshow("Example4",image_Color);
	cvWaitKey(0);//�ȴ��û���������
	destroyWindow("Example4");
#endif
	//image_Resized.release();
	//ģ��ͼ��
	Mat  image_Gray_Blur;
	blur (image_Gray,image_Gray_Blur,cvSize(2,3));
#if Test
	namedWindow("Example2",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
	imshow("Example2",image_Gray_Blur);
	cvWaitKey(0);//�ȴ��û���������
	destroyWindow("Example2");
#endif
	//��ֵ��
	Mat  image_Gray_adaptiveThreshold;
	adaptiveThreshold(image_Gray_Blur, image_Gray_adaptiveThreshold, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, 11, 5);
	int tp_sizeofBinaryHeight = image_Gray_adaptiveThreshold.size().height;
	int tp_sizeofBinaryWidth = image_Gray_adaptiveThreshold.size().width;
	int tp_type = image_Gray_adaptiveThreshold.type();
	int tp_pointOfImage = image_Gray_adaptiveThreshold.at<uchar>(20,15);
#if Test
	namedWindow("Example3",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
	imshow("Example3",image_Gray_Blur);
	cvWaitKey(0);//�ȴ��û���������
	destroyWindow("Example3");
#endif 
	//��������
	Mat image_element1 = getStructuringElement(MORPH_RECT, Size(3, 3));
	//��̬ѧ����
	Mat image_GetElementl;
	morphologyEx(image_Gray_adaptiveThreshold, image_GetElementl, MORPH_OPEN, image_element1);
#if Test
	namedWindow("Example5",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
	imshow("Example5",image_GetElementl);
	cvWaitKey(0);//�ȴ��û���������
	destroyWindow("Example5");
#endif 
	//��������
	vector<vector<Point> > tp_contours;
	cv::vector<Vec4i> tp_hierarchy;
	findContours(image_GetElementl,tp_contours,tp_hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE,Point(0, 0));
	Scalar color( rand()&255, rand()&255, rand()&255 );
	//�����л�ȡ����������ȥ
	//drawContours(image_Color,tp_contours,-1,color,CV_FILLED,8,tp_hierarchy);
#if Test
	namedWindow("Example6",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
	imshow("Example6",image_Color);
	cvWaitKey(0);//�ȴ��û���������
	destroyWindow("Example6");
#endif 
	//����������ɸѡ
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	vector <Point>  tp_SortOfContours;
	vector<vector<Point> > tp_contours_filter;
	vector<Point>		   tp_vector_centofContours;
	vector<Rect>		   tp_vector_rect;
	vector<vector<Point> >  tp_hull(tp_contours.size());
	//�洢�ϴ������
	int tp_bigContoursNumber = 0;  //�ϴ�����������
	int tp_i_bigContoursOneNumber = 0;
	int tp_i_bigContoursTwoNumber = 0;
	vector <int >    tp_vector_contoursIndex_bigone;
	vector <int >    tp_vector_contoursIndex_bigtwo;
	//forѭ������ʱʹ��
	double tp_contourArea;
	Rect tp_contoursRect;
	double tp_contoursRectArea;
	int  tp_contoursHeight;
	int  tp_contoursWidth;
	Point tp_centOfContours;
	//���������з���,�ϴ���������������
	for (int i =0; i < tp_contours.size();i++)
	{
		tp_contourArea = fabs(contourArea(tp_contours[i]));
		tp_contoursRect = boundingRect(tp_contours[i]);
		tp_contoursRectArea = (tp_contoursRect.height)*(tp_contoursRect.width);
		tp_contoursHeight = tp_contoursRect.height;
		tp_contoursWidth = tp_contoursRect.width;
		tp_centOfContours = Point(tp_contoursRect.x + tp_contoursRect.width / 2, tp_contoursRect.y + tp_contoursRect.height / 2);
		if (tp_contourArea<400 && tp_contourArea>6 && tp_contoursHeight<24 && tp_contoursWidth<21 && tp_contoursRectArea<700 && tp_contoursRectArea>6){
			//����������Ϊ����Ҫ�����ȷ����
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
	//��ȷ��������ʾ
	Mat tp_mat_image_normal = Mat::zeros(image_Gray.size(), CV_8UC1);
	//drawContours(tp_mat_image_normal,tp_contours_filter,-1,Scalar(255,255,255),CV_FILLED);
	//namedWindow("Example7",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
	//imshow("Example7",tp_mat_image_normal);
	//cvWaitKey(0);//�ȴ��û���������
	//destroyWindow("Example7");

	//����������ɺ�  ��Ҫ�Խϴ��������е�������
	Mat  tp_mat_image_bigContoursOne =  Mat::zeros(image_Gray.size(), CV_8UC1);
	if ( tp_vector_contoursIndex_bigone.size() > 0 )
	{
		for (int i =0 ; i <tp_vector_contoursIndex_bigone.size(); i++ )
		{
			drawContours(tp_mat_image_bigContoursOne,tp_contours,tp_vector_contoursIndex_bigone[i],Scalar(255),CV_FILLED);
		}
	}
	tp_vector_contoursIndex_bigone.clear();
	namedWindow("Example7",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
	imshow("Example7",tp_mat_image_bigContoursOne);
	cvWaitKey(0);//�ȴ��û���������
	destroyWindow("Example7");

	Mat  tp_mat_image_bigContoursTwo =  Mat::zeros(image_Gray.size(), CV_8UC1);
	if (tp_vector_contoursIndex_bigtwo.size() > 0) {
		for (int i =0 ; i < tp_vector_contoursIndex_bigtwo.size(); i++ )
		{
			drawContours(tp_mat_image_bigContoursTwo,tp_contours,tp_vector_contoursIndex_bigtwo[i],Scalar(255),CV_FILLED);
		}
	}
	tp_vector_contoursIndex_bigtwo.clear();
	namedWindow("Example8",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
	imshow("Example8",tp_mat_image_bigContoursTwo);
	cvWaitKey(0);//�ȴ��û���������
	destroyWindow("Example8");
	//��һ���ϴ�����
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
			//�����������ж�
			if (tp_contourArea < 400 && tp_contourArea > 6 && tp_contoursHeight < 24 && tp_contoursWidth < 24 && tp_contoursRectArea < 700 && tp_contoursRectArea>6){
				tp_contours_filter.push_back(tp_contours[i]);
				tp_vector_centofContours.push_back(tp_centOfContours);
				tp_vector_rect.push_back(tp_contoursRect);
			}
			else {//�������
				convexHull(tp_contours[i],tp_hull[i],false);
				Mat tp_convexhull = Mat::zeros(image_Gray.size(),CV_8UC1);
				drawContours(tp_convexhull,tp_hull,i,Scalar(255),CV_FILLED,8, vector<Vec4i>(), 0, Point());
				int tp_int = tp_convexhull.rows;
				tp_int = tp_convexhull.cols;
				//�Լ�⵽�Ķ���ν����ж�
				int tp_checktriangle = cProcessFunction::signalContoursJudge(tp_convexhull,tp_contoursRect);
				if (tp_checktriangle){
					//��⵽��������
					tp_contours_filter.push_back(tp_contours[i]);
					tp_vector_centofContours.push_back(tp_centOfContours);
					tp_vector_rect.push_back(tp_contoursRect);
				}
				else 
				{
					tp_vector_contoursIndex_bigone.push_back(i);
				}
				//namedWindow("Example����",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
				//imshow("Example����",tp_convexhull);
				//cvWaitKey(0);//�ȴ��û���������
				//destroyWindow("Example����");
			}
		}
		namedWindow("Example�ָ�����",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
		imshow("Example�ָ�����",tp_mat_image_bigContoursOne);
		cvWaitKey(0);//�ȴ��û���������
		destroyWindow("Example�ָ�����");
	}

	//�ٴζ��޷������������д���
	//λ��10
	if (tp_vector_contoursIndex_bigone.size() > 0)
	{
		for (int i =0 ; i < tp_vector_contoursIndex_bigone.size(); i++ )
		{
			drawContours(tp_mat_image_bigContoursOne,tp_contours,tp_vector_contoursIndex_bigone[i],Scalar(255),CV_FILLED);
		}
#if Test
		namedWindow("Exampleλ��10",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
		imshow("Exampleλ��10",tp_mat_image_bigContoursOne);
		cvWaitKey(0);//�ȴ��û���������
		destroyWindow("Exampleλ��10");
#endif 

		tp_contours.clear(); //�������
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
		//λ��11
#if Test
		namedWindow("Exampleλ��11",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
		imshow("Exampleλ��11",tp_mat_image_bigContoursOne);
		cvWaitKey(0);//�ȴ��û���������
		destroyWindow("Exampleλ��11");
#endif 
		tp_contours.clear(); //�������
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
			if (tp_contourArea<400 && tp_contourArea>6 && tp_contoursHeight<24 && tp_contoursWidth<21 && tp_contoursRectArea<700 && tp_contoursRectArea>6){//����������ȡֵ��Χ��С��24�����ԣ��������80������
				tp_contours_filter.push_back(tp_contours[i]);
				tp_vector_centofContours.push_back(tp_centOfContours);
				tp_vector_rect.push_back(tp_contoursRect);
			}
			if ((tp_contourArea >= 400 || (tp_contoursHeight >= 24 && tp_contoursWidth >= 3) || (tp_contoursHeight >= 3 && tp_contoursWidth >= 21)) ){
				tp_i_bigContoursOneNumber++;
				drawContours(tp_mat_image_bigContoursOne, tp_contours, i, cvScalar(255, 255, 255), CV_FILLED);
			}
		}
		//λ��12
#if Test
		namedWindow("Exampleλ��12",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
		imshow("Exampleλ��12",tp_mat_image_bigContoursOne);
		cvWaitKey(0);//�ȴ��û���������
		destroyWindow("Exampleλ��12");
#endif
	
	}

	//�ڶ����ϴ�����
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
			if (tp_contourArea<400 && tp_contourArea>6 && tp_contoursHeight<24 && tp_contoursWidth<21 && tp_contoursRectArea<700 && tp_contoursRectArea>6){//����������ȡֵ��Χ��С��24�����ԣ��������80������
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

	//λ��13
#if Test
	namedWindow("Exampleλ��13",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
	imshow("Exampleλ��13",tp_mat_image_bigContoursTwo);
	cvWaitKey(0);//�ȴ��û���������
	destroyWindow("Exampleλ��13");
#endif
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


		//λ��14
#if Test
		namedWindow("Exampleλ��14",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
		imshow("Exampleλ��14",tp_mat_image_bigContoursTwo);
		cvWaitKey(0);//�ȴ��û���������
		destroyWindow("Exampleλ��14");
#endif

		//��������
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
			if (tp_contourArea<400 && tp_contourArea>6 && tp_contoursHeight<24 && tp_contoursWidth<21 && tp_contoursRectArea<700 && tp_contoursRectArea>6){//����������ȡֵ��Χ��С��24�����ԣ��������80������
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


	//λ��15
#if Test
	namedWindow("Exampleλ��15",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
	imshow("Exampleλ��15",tp_mat_image_bigContoursTwo);
	cvWaitKey(0);//�ȴ��û���������
	destroyWindow("Exampleλ��15");
#endif
	//���´�����ֱ��һ��û�ֿ��õ�
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
		//��������
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
			if (tp_contourArea<400 && tp_contourArea>6 && tp_contoursHeight<24 && tp_contoursWidth<21 && tp_contoursRectArea<700 && tp_contoursRectArea>6){//����������ȡֵ��Χ��С��24�����ԣ��������80������
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
			if (tp_contourArea<400 && tp_contourArea>6 && tp_contoursHeight<24 && tp_contoursWidth<21 && tp_contoursRectArea<700 && tp_contoursRectArea>6){//����������ȡֵ��Χ��С��24�����ԣ��������80������
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
#if 0
	tp_mat_image_bigContoursTwo = Mat::zeros(image_Gray.size(),CV_8UC1);
	drawContours(tp_mat_image_bigContoursTwo,tp_contours_filter,-1,Scalar(255),CV_FILLED);
	namedWindow("Exampleλ�����",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
	imshow("Exampleλ�����",tp_mat_image_bigContoursTwo);
	cvWaitKey(0);//�ȴ��û���������
	destroyWindow("Exampleλ�����");
#endif
	//std::sort(theSortOfContours.begin(), theSortOfContours.end(), SortByM2);
	//���

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//�ָ���  ��ͼ�εĻ������������Ѿ����

	//���¿�ʼ���������зֲ�
	Mat ImageAbout_Contours_Mask;  //ͨ��ͼ��
	cProcessFunction::getImgAboutContours(image_Gray,ImageAbout_Contours_Mask,tp_contours_filter);
	namedWindow("Example��������",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
	imshow("Example��������",ImageAbout_Contours_Mask);
	cvWaitKey(0);//�ȴ��û���������
	destroyWindow("Example��������");

	//ȷ��ͼ����mat����δ洢
	Mat imageTest = Mat::zeros(image_Gray.size(),CV_8UC1);
	for (int j = 0; j <100;j++)
	{
		for (int i =0 ;i <100;i++)
		{
			imageTest.at<uchar>(j,i) = 255;
		}
	}
	namedWindow("ExampleTest",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
	imshow("ExampleTest",imageTest);
//	cvWaitKey(0);//�ȴ��û���������
	waitKey();
	destroyWindow("ExampleTest");


	//�������������зֲ㴦��
	vector<bool > contoursUsed;
	vector< vector<int> > indexSeriers;  //�����һ�����ϵ�����  �������ֲ�
	contoursUsed.resize(tp_vector_rect.size());  //

	//���������зֲ�
	for (int i = 0; i < tp_vector_rect.size(); i++) 
	{
		//�������Ѿ���ʹ��
		if (contoursUsed[i])
		{
			continue;
		}
		vector<int> tp_upTodown_Seriers;
		//vector<int> tp_downToup_Seriers; 
		int    tp_delete_ContoursIndex = -1; //���ڴ洢ͨ�����м�ⲻ����ͬһ���������index
		tp_upTodown_Seriers.push_back(i);
		//tp_downToup_Seriers.push_back(i);
		int StartX = tp_vector_centofContours[i].x;
		if (StartX <3 || StartX > ImageAbout_Contours_Mask.cols -4 )
		{
			contoursUsed[i] = TRUE;
			continue;
		}
		//�������±���
		for ( int j = tp_vector_rect[i].y+tp_vector_rect[i].height;j < ImageAbout_Contours_Mask.rows; j++)
		{
			if (StartX <3 || StartX > ImageAbout_Contours_Mask.cols -4 )
			{
				break;
			}
			int currentIndex = -1;
			int lastIndex = -1;
			if (ImageAbout_Contours_Mask.at<unsigned short>(j, StartX) != 0)
			{
				currentIndex = ImageAbout_Contours_Mask.at<unsigned short>(j, StartX) - 1;
			}
			else
			{
				if (ImageAbout_Contours_Mask.at<unsigned short>(j, StartX - 3) != 0)
				{
					currentIndex = ImageAbout_Contours_Mask.at<unsigned short>(j, StartX - 3) - 1;
				}
				else
				{
					if (ImageAbout_Contours_Mask.at<unsigned short>(j, StartX + 3) != 0)
					{
						currentIndex = ImageAbout_Contours_Mask.at<unsigned short>(j, StartX + 3) - 1;
					}
				}
			}
			if (-1 == currentIndex )
			{
				continue;
			}
			//�����ȡ����index���Ѿ�
			lastIndex =  tp_upTodown_Seriers.back();
			if (currentIndex == lastIndex)
			{
				continue;
			}
			//�����жϹ� ����ͬһ�������ɾ��
			if (currentIndex == tp_delete_ContoursIndex )
			{
				continue;
			}
			//ʹ��rect�����ж��Ƿ�����ͬһ��
			Rect currentRect = tp_vector_rect[currentIndex];
			Rect lastRect = tp_vector_rect[lastIndex];

			int lastLastIndex;
			Rect lastLastRect;
			if (tp_upTodown_Seriers.size()< 2)
			{
				if (1 == cProcessFunction::check2Rect310190117(lastRect, currentRect, 0) &&(1 == cProcessFunction::check2cent311290117(lastRect, currentRect)))
				{
					tp_upTodown_Seriers.push_back(currentIndex);
					contoursUsed[currentIndex] = TRUE;
					StartX = tp_vector_centofContours[currentIndex].x;
					j = tp_vector_rect[currentIndex].y + tp_vector_rect[currentIndex].height;
					//rectangle(img1, m_vect_contourRect[currentIndex], color[j % 10], 2);
				}
			}
			//ͬһ���ж������������� (��indexVector���ڶ��������λ��)
			else
			{
				lastLastIndex = tp_upTodown_Seriers[tp_upTodown_Seriers.size() - 2];
				lastLastRect = tp_vector_rect[lastLastIndex];
				//�����ж��Ƿ�����ͬһ������
				if (1 == cProcessFunction::check2Rect310190117(lastRect, currentRect, 0) && 1 == cProcessFunction::check3cent311290117(lastLastRect, lastRect, currentRect) && 1 == cProcessFunction::check1cent310190117(lastLastRect, currentRect))
				{
					tp_upTodown_Seriers.push_back(currentIndex);
					contoursUsed[currentIndex] = TRUE;
					StartX = tp_vector_centofContours[currentIndex].x;
					j = tp_vector_rect[currentIndex].y + tp_vector_rect[currentIndex].height;
					//rectangle(img1, m_vect_contourRect[currentIndex], color[j % 10], 2);
				}
				else
				{
					//�ж��Ƿ���ͬһ��
					if (1 == cProcessFunction:: check2Rect310190117(lastLastRect, currentRect, 2) && 1 == cProcessFunction::check3cent311290117(lastLastRect, lastRect, currentRect) && 1 == cProcessFunction::check1cent310190117(lastLastRect, currentRect))
					{//��ǰ������һ�����бȽ�	
						tp_upTodown_Seriers.push_back(currentIndex);
						contoursUsed[currentIndex] = TRUE;
						StartX = tp_vector_centofContours[currentIndex].x;
						j = tp_vector_rect[currentIndex].y + tp_vector_rect[currentIndex].height;
					}
					else  //���������ͬһ��
					{
						tp_delete_ContoursIndex = currentIndex;
						continue;
					}
				}
			}
		}
		//�������±������

		StartX = tp_vector_centofContours[i].x;
		tp_delete_ContoursIndex  = -1;
		//�������ϱ���
		for (int j = tp_vector_rect[i].y; j > 0; j--)
		{
			if (StartX <3 || StartX > ImageAbout_Contours_Mask.cols -4 )
			{
				break;
			}
			int currentIndex = -1;
			int lastIndex = -1;
			if (ImageAbout_Contours_Mask.at<unsigned short>(j, StartX) != 0)
			{
				currentIndex = ImageAbout_Contours_Mask.at<unsigned short>(j, StartX) - 1;
			}
			else
			{
				if (ImageAbout_Contours_Mask.at<unsigned short>(j, StartX - 3) != 0)
				{
					currentIndex = ImageAbout_Contours_Mask.at<unsigned short>(j, StartX - 3) - 1;
				}
				else
				{
					if (ImageAbout_Contours_Mask.at<unsigned short>(j, StartX + 3) != 0)
					{
						currentIndex = ImageAbout_Contours_Mask.at<unsigned short>(j, StartX + 3) - 1;
					}
				}
			}
			if (-1 == currentIndex )
			{
				continue;
			}
			//�����ȡ����index���Ѿ�
			lastIndex =  tp_upTodown_Seriers.at(0);
			if (currentIndex == lastIndex)
			{
				continue;
			}
			//�����жϹ� ����ͬһ�������ɾ��
			if (currentIndex == tp_delete_ContoursIndex )
			{
				continue;
			}
			//ʹ��rect�����ж��Ƿ�����ͬһ��
			Rect currentRect = tp_vector_rect[currentIndex];
			Rect lastRect = tp_vector_rect[lastIndex];

			int lastLastIndex;
			Rect lastLastRect;
			if (tp_upTodown_Seriers.size()< 2)
			{
				if (1 == cProcessFunction::check2Rect310190117(lastRect, currentRect, 0) &&(1 == cProcessFunction::check2cent311290117(lastRect, currentRect)))
				{
					//�����Ǵ������� ��Ҫ���뵽����
					//tp_upTodown_Seriers.push_back(currentIndex);
					tp_upTodown_Seriers.insert(tp_upTodown_Seriers.begin(),currentIndex);
					contoursUsed[currentIndex] = TRUE;
					StartX = tp_vector_centofContours[currentIndex].x;
					j = tp_vector_rect[currentIndex].y;
					//rectangle(img1, m_vect_contourRect[currentIndex], color[j % 10], 2);
				}
			}
			//ͬһ���ж������������� (��indexVector���ڶ��������λ��)
			else
			{
				lastLastIndex = tp_upTodown_Seriers.at(1);
				lastLastRect = tp_vector_rect[lastLastIndex];
				//�����ж��Ƿ�����ͬһ������
				if (1 == cProcessFunction::check2Rect310190117(lastRect, currentRect, 0) && 1 == cProcessFunction::check3cent311290117(lastLastRect, lastRect, currentRect) && 1 == cProcessFunction::check1cent310190117(lastLastRect, currentRect))
				{
					//�����Ǵ������� ��Ҫ���뵽����
					//tp_upTodown_Seriers.push_back(currentIndex);
					tp_upTodown_Seriers.insert(tp_upTodown_Seriers.begin(),currentIndex);
					contoursUsed[currentIndex] = TRUE;
					StartX = tp_vector_centofContours[currentIndex].x;
					j = tp_vector_rect[currentIndex].y ;
					//rectangle(img1, m_vect_contourRect[currentIndex], color[j % 10], 2);
				}
				else
				{
					//�ж��Ƿ���ͬһ��
					if (1 == cProcessFunction:: check2Rect310190117(lastLastRect, currentRect, 2) && 1 == cProcessFunction::check3cent311290117(lastLastRect, lastRect, currentRect) && 1 == cProcessFunction::check1cent310190117(lastLastRect, currentRect))
					{//��ǰ������һ�����бȽ�	
						//�����Ǵ������� ��Ҫ���뵽����
						//tp_upTodown_Seriers.push_back(currentIndex);
						tp_upTodown_Seriers.insert(tp_upTodown_Seriers.begin(),currentIndex);
						contoursUsed[currentIndex] = TRUE;
						StartX = tp_vector_centofContours[currentIndex].x;
						j = tp_vector_rect[currentIndex].y;
					}
					else  //���������ͬһ��
					{
						tp_delete_ContoursIndex = currentIndex;
						continue;
					}
				}
			}	
		}
		//�������ϱ������
		indexSeriers.push_back(tp_upTodown_Seriers);

	}//�����ֲ����

	//�Էֲ��������
	vector <int > sortIndexOfSeriers; //�����ĸ����˳��
	for (int i = 0; i < indexSeriers.size();i++)
	{
		if (indexSeriers[i].size() < 3 || indexSeriers[i].size() > 100)
		{
			//����������Ҳ�ᱻɾ��
			continue ;
		};

	}

	//��ʾ���߽��
	cv::Size tp_size = image_Color.size();
	Mat imageTest22= Mat::zeros(tp_size,CV_8UC1);
	Mat image_ColorFul;
	cvtColor(image_Gray, image_ColorFul, CV_GRAY2BGR);
	for (int ii = 0; ii <indexSeriers.size(); ii++)
	{
		Point PointOne = tp_vector_centofContours[indexSeriers[ii].at(0)];
		Point PointTwo = tp_vector_centofContours[indexSeriers[ii].back()];
	    cv::line(image_ColorFul,PointOne,PointTwo, Scalar(255,0,255),2);
	}
	namedWindow("ExampleTest",CV_WINDOW_NORMAL);//����һ����ΪExample1�Ĵ���
	imshow("ExampleTest",image_ColorFul);
	//	cvWaitKey(0);//�ȴ��û���������
	waitKey();
	destroyWindow("ExampleTest");


	image_Gray.release();
	return 0;
	}
