#include "ProcessFunction.h"
#include "opencv/cv.h" 
#include "highgui.h"
#include <iostream>
using namespace std;

//������״�ж�
int cProcessFunction::signalContoursJudge(Mat  binaryImage,CvRect theRect)
{
	if (theRect.height < theRect.width ){
		int x1 = theRect.x;
		int y1 = theRect.y;

		int x2 = theRect.x;
		int y2 = theRect.y + theRect.height;

		int x3 = theRect.x + theRect.width;
		int y3 = theRect.y;

		int x4 = theRect.x + theRect.width;
		int y4 = theRect.y + theRect.height;

		int theL = theRect.height / 2;
		int s1 = 1;
		for (int _y = y1, i = 0; i < theL; i++, _y++){
			for (int _x = x1; _x < x1 + theL - i; _x++){
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s1++;
				}
			}
		}

		int s2 = 1;
		for (int _y = y2 - theL, i = 0; i < theL; _y++, i++){
			for (int _x = x2; _x < x2 + i; _x++){
				//blackG.at<uchar>(_y, _x) = 200;
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s2++;
				}
			}
		}

		int s3 = 1;
		for (int _y = y3, i = 0; i < theL; _y++, i++){
			for (int _x = x3 - theL + i; _x < x3; _x++){
				//blackG.at<uchar>(_y, _x) = 128;
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s3++;
				}
			}
		}

		int s4 = 1;
		for (int _y = y4 - theL, i = 0; i < theL; _y++, i++){
			for (int _x = x4 - i; _x < x4; _x++){
				//blackG.at<uchar>(_y, _x) = 240;
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s4++;
				}
			}
		}



		int s9 = 1;
		for (int _y = y1, i = 0; i < theRect.height; i++, _y++){
			for (int _x = x1; _x < (x1 + x3) / 2; _x++){
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s9++;
				}
			}
		}
		int s10 = 1;
		for (int _y = y1, i = 0; i < theRect.height; i++, _y++){
			for (int _x = (x1 + x3) / 2; _x < x3; _x++){
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s10++;
				}
			}
		}


		int s12 = 1;
		for (int _y = y1, i = 0; i < theRect.height; i++, _y++){
			for (int _x = x1; _x < x1 + ((x3 - x1) / 3); _x++){
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s12++;
				}
			}
		}

		int s13 = 1;
		for (int _y = y1, i = 0; i < theRect.height; i++, _y++){
			for (int _x = x1 + ((x3 - x1) / 3); _x < x1 + (((x3 - x1) / 3) * 2); _x++){
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s13++;
				}
			}
		}

		int s14 = 1;
		for (int _y = y1, i = 0; i < theRect.height; i++, _y++){
			for (int _x = x1 + (((x3 - x1) / 3) * 2); _x < x3; _x++){
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s14++;
				}
			}
		}


		if (((s1 / s3*1.0>2) || (s2 / s4*1.0>2)) && (s12 >= s13) && (s9 - s10 >= 1)){
			//�ұ�ȱ

			return 2;
		}
		if (((s3 / s1*1.0>2) || (s4 / s2*1.0 > 2)) && (s14 >= s13) && (s10 - s9 >= 1)){
			//���ȱ
			return 1;
		}

	}
	if (theRect.height >= theRect.width){
		int x1 = theRect.x;
		int y1 = theRect.y;

		int x2 = theRect.x;
		int y2 = theRect.y + theRect.height;

		int x3 = theRect.x + theRect.width;
		int y3 = theRect.y;

		int x4 = theRect.x + theRect.width;
		int y4 = theRect.y + theRect.height;

		int theL = theRect.width / 2;
		int s1 = 1;
		for (int _y = y1, i = 0; i < theL; i++, _y++){
			for (int _x = x1; _x < x1 + theL - i; _x++){
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s1++;
				}
			}
		}

		int s2 = 1;
		for (int _y = y2 - theL, i = 0; i < theL; _y++, i++){
			for (int _x = x2; _x < x2 + i; _x++){
				//blackG.at<uchar>(_y, _x) = 200;
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s2++;
				}
			}
		}

		int s3 = 1;
		for (int _y = y3, i = 0; i < theL; _y++, i++){
			for (int _x = x3 - theL + i; _x < x3; _x++){
				//blackG.at<uchar>(_y, _x) = 128;
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s3++;
				}
			}
		}

		int s4 = 1;
		for (int _y = y4 - theL, i = 0; i < theL; _y++, i++){
			for (int _x = x4 - i; _x < x4; _x++){
				//blackG.at<uchar>(_y, _x) = 240;
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s4++;
				}
			}
		}



		int s9 = 1;
		for (int _y = y1, i = 0; i < theRect.height; i++, _y++){
			for (int _x = x1; _x < (x1 + x3) / 2; _x++){
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s9++;
				}
			}
		}
		int s10 = 1;
		for (int _y = y1, i = 0; i < theRect.height; i++, _y++){
			for (int _x = (x1 + x3) / 2; _x < x3; _x++){
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s10++;
				}
			}
		}


		int s12 = 1;
		for (int _y = y1, i = 0; i < theRect.height; i++, _y++){
			for (int _x = x1; _x < x1 + ((x3 - x1) / 3); _x++){
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s12++;
				}
			}
		}

		int s13 = 1;
		for (int _y = y1, i = 0; i < theRect.height; i++, _y++){
			for (int _x = x1 + ((x3 - x1) / 3); _x < x1 + (((x3 - x1) / 3) * 2); _x++){
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s13++;
				}
			}
		}

		int s14 = 1;
		for (int _y = y1, i = 0; i < theRect.height; i++, _y++){
			for (int _x = x1 + (((x3 - x1) / 3) * 2); _x < x3; _x++){
				if (binaryImage.at<uchar>(_y, _x) == 255){
					s14++;
				}
			}
		}


		if (((s1 / s3*1.0>2) || (s2 / s4*1.0>2)) && (s12 >= s13) && (s9 - s10 >= 1)){
			//�ұ�ȱ

			return 2;
		}
		if (((s3 / s1*1.0>2) || (s4 / s2*1.0 > 2)) && (s14 >= s13) && (s10 - s9 >= 1)){
			//���ȱ
			return 1;
		}

	}
	return 0;
};


//��������ͼ�εķ�ʽ���ֳ���
void   cProcessFunction::getImgAboutContours(Mat &binImg,Mat &MarkImg ,vector<vector<Point> > &theContours){//the v is (index +1)
	MarkImg = Mat::zeros(binImg.size(), CV_16UC1);
	//�������ĵ�  ����ͬ��С��ͼ���϶�Ӧ����б�ע
	for (int i = 0; i < theContours.size(); i++){
		for (int j = 0; j < theContours[i].size(); j++){
			MarkImg.at<unsigned short>(theContours[i][j].y, theContours[i][j].x) = i+1;
		}
	}

	//��������Ӧͼ�� ��   ͬһ����ͬһ�ŵ��������������
	for (int i = 0; i < MarkImg.rows; i++){
		for (int j = 0; j < MarkImg.cols;j++ ){

			int _j = 1;
			int theV = 0;
			int vS = 0;
			if ( (theV = MarkImg.at<unsigned short>(i, j))!=0 ){
				for (_j = 1; j + _j < MarkImg.cols; _j++){
					if (MarkImg.at<unsigned short>(i, j + _j) != 0){
						if (MarkImg.at<unsigned short>(i, j + _j) == theV){
							vS = 1;
						}
						break;
					}
				}

				for (int jj = 1; jj < _j && vS && j + jj < MarkImg.cols; jj++){
					MarkImg.at<unsigned short>(i, j + jj) = theV;
					//temp.at<uchar>(i, j + jj) = 255;
				}

				j += _j-1;    
			}
		}
	}

}

bool cProcessFunction::check2Rect310190117(Rect &r1, Rect &r2, int theLevel)
{
	//int para1	=	5;
	int para1 = 6;
	int para5 = r1.width * 0.5f+0.5f;
	int para2 = 9;
	int para6 = r1.width * 0.6f+0.5f;
	int para3 = 20;
	int para4 = r1.height * 2;

	if (theLevel == 2){
		para1 = 6;
		para2 = 9;
		//para3	=	30;
		para3 = 29;
		para4 = r1.height * 2;
		para5 = r1.width * 0.5f+0.5f;
		para6 = r1.width * 0.6f+0.5f;

	}

	bool left1 = (abs(r1.x - r2.x) < para1) || (abs(r1.x - r2.x) < para5);
	bool left2 = (abs(r1.x + r1.width - r2.x - r2.width) < min(para2, min(r1.width, r2.width))) || (abs(r1.x + r1.width - r2.x - r2.width) < min(para6, min(r1.width, r2.width)));
	bool left3 = (r2.y - (r1.y + r1.height) < para3) || (r2.y - (r1.y + r1.height) < para4);

	bool right1 = (abs(r1.x - r2.x) < min(para2, min(r1.width, r2.width))) || (abs(r1.x - r2.x) < min(para6, min(r1.width, r2.width)));
	bool right2 = (abs(r1.x + r1.width - r2.x - r2.width) < para1) || (abs(r1.x + r1.width - r2.x - r2.width) < para5);
	bool right3 = (r2.y - (r1.y + r1.height) < para3) || (r2.y - (r1.y + r1.height) < para4);


	bool flag1 = (left1) && (left2) && (left3);//������
	bool flag2 = (right1) && (right2) && (right3);//�Ҳ����
	if ((r1.x == 9073) && (r1.y == 111) && (r1.width == 14) && (r1.height == 8))
	{
		cv::waitKey();
	}

	if (flag1 || flag2){
		return 1;
	}
	else{
		return 0;
	}
}
bool cProcessFunction::check1cent310190117(Rect &r1, Rect &r2)
{
	Point  theCent1 = Point(r1.x + r1.width / 2, r1.y + r1.height / 2);
	Point  theCent2 = Point(r2.x + r2.width / 2, r2.y + r2.height / 2);
	if ((r1.x == 12770) && (r1.y == 204) && (r1.width == 7) && (r1.height == 27)){
		cv::waitKey();
	}
	int x1 = 0;
	x1 = abs(theCent1.x - theCent2.x);

	bool flag3 = (x1 <9) || (x1 < (r1.width*0.6+0.5));

	if (flag3){
		return 1;
	}
	else{
		return 0;
	}
}

bool cProcessFunction::check3cent311290117(Rect &r0, Rect &r1, Rect &r2)
{
	Point  theCent0 = Point(r0.x + r0.width / 2, r0.y + r0.height / 2);
	Point  theCent1 = Point(r1.x + r1.width / 2, r1.y + r1.height / 2);
	Point  theCent2 = Point(r2.x + r2.width / 2, r2.y + r2.height / 2);
	int theArea0 = r0.width*r0.height;
	int theArea1 = r1.width*r1.height;
	int theArea2 = r2.width*r2.height;

	if ((r1.x == 12770) && (r1.y == 204) && (r1.width == 7) && (r1.height == 27))
	{
		cv::waitKey();
	}
	int x1 = 0;
	int x3 = 0;
	x1 = abs(theCent1.x - theCent2.x);
	x3 = abs(theCent0.x - theCent2.x);
	double x2 = 0.00;
	double x4 = 0.00;
	double x5 = 0.00;
	double x6 = 0.00;
	double xh1 = 0.00;
	double xh2 = 0.00;


	x2 = (r2.width*1.0) / (r1.width);
	x4 = (r2.width*1.0) / (r0.width);

	x5 = theArea2*1.0 / theArea1;
	x6 = theArea2*1.0 / theArea0;

	xh1 = (r2.height*1.0) / (r1.height);
	xh2 = (r2.height*1.0) / (r0.height);

	bool choosecent1 = (x1 < 4) || (x1 < (r1.width*0.2+0.5));
	bool choosecent2 = ((x1 >= 4) || (x1 >= (r1.width*0.2+0.5))) && ((x1 <9) || (x1<(r1.width*0.6+0.5)));
	bool choosecent3 = (x3 < 4) || (x3 < (r0.width*0.2+0.5));

	bool flag3 = (choosecent1) && (0.35 < x2) && (x2 < 2.55) && (0.25 < x5) && (x5 < 4) && (0.3 < xh1) && (xh2 < 3.3);//�ȽϾ�����������С��6���������εĿ�����
	//bool flag3 = (x2 >= 2.5) && (x2 <= 0.4);
	bool flag4 = (choosecent2) && (0.52 < x2) && (x2 < 1.92) && (0.25 < x5) && (x5 < 4) && (0.4 < xh1) && (xh1 < 2.5);//�Ƚϴ���6��ʱ������
	bool flag5 = (choosecent3) && (0.35 < x2) && (x2 < 2.55) && (x4 < 2.55) && (0.25 < x6) && (x6 < 4) && (0.3 < xh2) && (xh2 < 3.3);//�Ƚϵ�ǰ������һ���ı�ֵ
	//	bool flag6 = (x3 < 20);
	//bool flag6 = 1;
	//if ((flag3 || flag4|| flag5)&&flag6){
	if (flag3 || flag4 || flag5){
		return 1;
	}
	else{
		return 0;
	}
}

bool cProcessFunction::check2cent311290117(Rect &r0, Rect &r1)
{
	Point  theCent0 = Point(r0.x + r0.width / 2, r0.y + r0.height / 2);
	Point  theCent1 = Point(r1.x + r1.width / 2, r1.y + r1.height / 2);
	int theArea0 = r0.width*r0.height;
	int theArea1 = r1.width*r1.height;


	if ((r1.x == 12770) && (r1.y == 204) && (r1.width == 7) && (r1.height == 27))
	{
		cv::waitKey();
	}
	int x1 = 0;
	int x3 = 0;
	x1 = abs(theCent1.x - theCent0.x);
	double x2 = 0.00;
	double x5 = 0.00;
	double xh = 0.00;
	x2 = (r1.width*1.0) / (r0.width);
	x5 = theArea1*1.0 / theArea0;
	xh = (r1.height*1.0) / (r0.height);
	bool choosecent1 = (x1 < 4) || (x1 < (r0.width*0.2+0.5));
	bool choosecent2 = ((x1 >= 4) || (x1 >= (r0.width*0.2+0.5))) && ((x1 <9) || (x1<(r0.width*0.6+0.5)));

	bool flag3 = (choosecent1) && (0.35 < x2) && (x2 < 2.55) && (0.25 < x5) && (x5 < 4) && (0.3 < xh) && (xh < 3.3);//�ȽϾ�����������С��6���������εĿ�����
	//bool flag3 = (x2 >= 2.5) && (x2 <= 0.4);
	bool flag4 = (choosecent2) && (0.52 < x2) && (x2 < 1.92) && (0.25 < x5) && (x5 < 4) && (0.4 < xh) && (xh < 2.5);//�Ƚϴ���6��ʱ������

	if (flag3 || flag4){
		return 1;
	}
	else{
		return 0;
	}
}

//ɸѡ����
bool cProcessFunction::delateSomeClass1101710119(Mat &graySrc, Mat &m_mat_binContourImg_, cMultiLayers & theSetOfserial)
{

	////////////////////////////////////////
	Mat   img, cannySrc1, edge, cannySrc2, edge1, graySrc1;
	Mat   img2;
	cvtColor(graySrc, img, CV_GRAY2BGR);
	graySrc.copyTo(graySrc1);
	//medianBlur(graySrc1, edge1, 5);
	blur(graySrc1, edge1, Size(4, 4));
	cv::Mat kernela(3, 3, CV_32F, cv::Scalar(0)); //����һ���˺��� 
	kernela.at<float>(1, 1) = 5.0;
	//kernela.at<float>(0, 2) = 1.0;
	//kernela.at<float>(2, 2) = 1.0;
	//kernela.at<float>(0, 0) = 1.0;
	//kernela.at<float>(2, 0) = 1.0;
	kernela.at<float>(0, 1) = -1.0;
	kernela.at<float>(2, 1) = -1.0;
	kernela.at<float>(1, 0) = -1.0;
	kernela.at<float>(1, 2) = -1.0;
	filter2D(edge1, edge1, edge1.depth(), kernela);
	filter2D(graySrc, edge, graySrc.depth(), kernela);
	blur(edge1, edge1, Size(4, 4));
	//medianBlur(edge, edge, 5);
	blur(edge, edge, Size(4, 4));
	Canny(edge1, cannySrc1, 30, 130, 3);
	Canny(edge, cannySrc2, 30, 130, 3);
	img.copyTo(img2);
	///////////////////////////////////////
	vector<int> classrect;
	theSetOfserial.ArrangeLayer();
	if (theSetOfserial.m_vector_indexLegal.size() <= 2){
		return 0;
	}
	for (int i = 0; i < theSetOfserial.size(); i++){
		//�Ƚϵ�ǰ������һ�����һ��֮��Ĺ�ϵ.
		cLayer   *currentClass = theSetOfserial.at(i);
		currentClass->GetFitLine();

		if (currentClass->m_b_LayerLegal == 0){ continue; }

		vector<int> eachHistR;
		eachHistR.resize(2200);//�˴�������Խ��
		for (int i = 0; i < currentClass->m_vecotr_contoursRect.size(); i++){
			int curarea = (currentClass->m_vecotr_contoursRect[i].height)*(currentClass->m_vecotr_contoursRect[i].width);
			if (curarea >= 2200){
				curarea = 2100;
			}
			eachHistR[curarea]++;

		}

		int collect1010Con = 0;
		int collectIndex10 = 0;

		for (int i = eachHistR.size() - 1; i > 0; i--){
			collect1010Con += eachHistR[i];
			if (collect1010Con > (currentClass->m_vecotr_contoursRect.size() / 2)){
				collectIndex10 = i;
				break;
			}
		}

		classrect.push_back(collectIndex10);
		eachHistR.clear();
		////////////////////////////////////////////////////////////
		currentClass->m_vector_FitLayerCentPoint.clear();
	}

	vector<int> therectHist;
	therectHist.resize(3000);////������������м�ֵ
	for (int i = 0; i<classrect.size(); i++){
		therectHist[classrect[i]]++;
	}

	int collect1011Con = 0;
	int collectIndex4 = 0;
	for (int i = therectHist.size() - 1; i > 0; i--){
		collect1011Con += therectHist[i];
		if (collect1011Con > (classrect.size() / 2)){
			collectIndex4 = i;
			break;
		}
	}

	for (int i = 0; i < theSetOfserial.size(); i++){
		//�Ƚϵ�ǰ������һ�����һ��֮��Ĺ�ϵ.
		cLayer   *currentClass = theSetOfserial.at(i);
		currentClass->GetFitLine();
		if (currentClass->m_b_LayerLegal == 0){ continue; }

		bool	fitlineresult1 = thefitlineAnaly1(cannySrc1, currentClass->theSetOfCentfit[0], currentClass->theSetOfCentfit.back(), currentClass->theSetOfCent.size());
		bool	fitlineresult2 = thefitlineAnaly2(cannySrc2, currentClass->theSetOfCentfit[0], currentClass->theSetOfCentfit.back(), currentClass->theSetOfCent.size());

		if ((fitlineresult1 == 0) || (fitlineresult1 == 0)){
			if (classrect[i] < 0.5*collectIndex4){
				//if ((currentClass->theSetOfCent.back().y - currentClass->theSetOfCent[0].y >= 400) && (currentClass->theSetOfCent.size() >= 22)){ continue; }
				if ((currentClass->theSetOfCent.back().y - currentClass->theSetOfCent[0].y >= grayrowscount) && (currentClass->theSetOfCent.size() >= 32)){ continue; }
				currentClass->isThisSerialOK = 0;

			}
		}
	}
	return 0;
}


cLayer::cLayer()
{
	m_b_LayerLegal = TRUE;
}

//����ƽ��Xֵ
void  cLayer::Caclute()
{
	m_i_PointCentXMax = m_vector_LayerPoint[0].x;
	m_i_PointCentXMin = m_vector_LayerPoint[0].x;
	m_i_CentSum = 0;
	for (int i= 0; i <m_vector_LayerPoint.size();i++)
	{
		m_i_CentSum += m_vector_LayerPoint[i].x;
		m_i_PointCentXMax = m_i_PointCentXMax>m_vector_LayerPoint[i].x?m_i_PointCentXMax:m_vector_LayerPoint[i].x;
		m_i_PointCentXMin = m_i_PointCentXMin<m_vector_LayerPoint[i].x?m_i_PointCentXMin:m_vector_LayerPoint[i].x;
	}
	m_i_PointCentXAverage = m_i_CentSum/m_vector_LayerPoint.size();
	return ;
};

void cLayer::GetFitLine()
{
	Vec4f line;
	cv::fitLine(Mat(m_vector_LayerPoint), line, CV_DIST_HUBER, 0, 0.01, 0.01);
	m_d_fitLine_k = line[1]/line[0];
	m_d_fitLine_b = line[3] - m_d_fitLine_k * line[2];
	double fitX = 0;
	Point tp_point;
	for (int i = 0; i < m_vector_LayerPoint.size();i++)
	{
		fitX = (m_vector_LayerPoint[i].y - m_d_fitLine_b)/m_d_fitLine_k;
		m_vector_FitLayerCentPoint.push_back(Point(fitX,m_vector_LayerPoint[i].y));
	}
	m_i_FitPointXSum  = 0;
	m_i_FitPointCentXMin = m_vector_FitLayerCentPoint[0].x;
	m_i_FitPointCentXMax = m_vector_FitLayerCentPoint[0].x;
	m_i_FitPointCentXAverage = 0;
	for (int i = 0; i < m_vector_FitLayerCentPoint.size(); i++)
	{
		m_i_FitPointXSum += m_vector_FitLayerCentPoint[i].x;
		m_i_FitPointCentXMax = m_i_FitPointCentXMax>m_vector_FitLayerCentPoint[i].x?m_i_FitPointCentXMax:m_vector_FitLayerCentPoint[i].x;
		m_i_FitPointCentXMax = m_i_FitPointCentXMax<m_vector_FitLayerCentPoint[i].x?m_i_FitPointCentXMax:m_vector_FitLayerCentPoint[i].x;
	}
	m_i_FitPointCentXAverage = m_i_PointCentXAverage/m_vector_FitLayerCentPoint.size();
	return ;
};

void  cLayer::AddMember(int &layerIndex,Rect &ContoursRect,Point &contoursCentPoint)
{
	m_vector_contoursIndex.push_back(layerIndex);
	m_vecotr_contoursRect.push_back(ContoursRect);
	m_vector_LayerPoint.push_back(contoursCentPoint);
};


//������Ҫʹ��
bool cMultiLayers::SortCompareFunction(Point & one,Point &two)
{
	return one.x>two.x;  //��������
};
//�ֲ�
void cMultiLayers::SortLayer()
{
	//�����е�����vector������ȥ��ʼ��sorIndexOfLayer
	m_vector_SortLayer.clear();
	if (m_vector_clayer_AllLayer.size() <3 )
	{
		//�������ٵ����
		return ;
	}
	m_vector_sortIndexOfLayer.resize(m_vector_clayer_AllLayer.size());
	for (int i = 0 ;i < m_vector_clayer_AllLayer.size(); i++)
	{
		//�������ĵ�
		m_vector_clayer_AllLayer[i].Caclute();
		m_vector_SortLayer.push_back(Point(m_vector_clayer_AllLayer[i].m_i_PointCentXAverage,i));
	}
	//�������и���
	std::sort(m_vector_SortLayer.begin(),m_vector_SortLayer.end(),cMultiLayers::SortCompareFunction);
	for (int i = 0 ; i < m_vector_SortLayer.size(); i++)
	{
		m_vector_sortIndexOfLayer[i] = m_vector_SortLayer[i].y;
		m_vector_Layerstatus[i] = m_vector_clayer_AllLayer[m_vector_sortIndexOfLayer[i]].m_b_LayerLegal;
		m_vector_clayer_AllLayer[m_vector_sortIndexOfLayer[i]].m_i_LayerId = i;
	}
}

void cMultiLayers::ArrangeLayer()
{
	SortLayer();
	m_vector_indexLegal.clear();
	for (int i = 0; i < m_vector_clayer_AllLayer.size(); i++)
	{
		if (m_vector_Layerstatus[i])m_vector_indexLegal.push_back(m_vector_Layerstatus[i]);
	}
}

void  cMultiLayers::AddMember(cLayer & inputLayer)
{
	m_vector_clayer_AllLayer.push_back(inputLayer);
};

int cMultiLayers::size()
{
	return m_vector_indexLegal.size();
};

cLayer * cMultiLayers::at(int i)
{
	return &m_vector_clayer_AllLayer[i];
};