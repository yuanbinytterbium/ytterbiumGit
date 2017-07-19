#include "ProcessFunction.h"
#include "opencv/highgui.h"


//单个形状判断
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
			//右边缺

			return 2;
		}
		if (((s3 / s1*1.0>2) || (s4 / s2*1.0 > 2)) && (s14 >= s13) && (s10 - s9 >= 1)){
			//左边缺
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
			//右边缺

			return 2;
		}
		if (((s3 / s1*1.0>2) || (s4 / s2*1.0 > 2)) && (s14 >= s13) && (s10 - s9 >= 1)){
			//左边缺
			return 1;
		}

	}
	return 0;
};


//将轮廓以图形的方式表现出来
void   cProcessFunction::getImgAboutContours(Mat &binImg,Mat &MarkImg ,vector<vector<Point> > &theContours){//the v is (index +1)
	MarkImg = Mat::zeros(binImg.size(), CV_16UC1);
	//对轮廓的点  在相同大小的图像上对应点进行标注
	for (int i = 0; i < theContours.size(); i++){
		for (int j = 0; j < theContours[i].size(); j++){
			MarkImg.at<unsigned short>(theContours[i][j].y, theContours[i][j].x) = i+1;
		}
	}

	//将轮廓对应图像 上   同一属性同一排的轮廓点进行连线
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


	bool flag1 = (left1) && (left2) && (left3);//左侧对齐
	bool flag2 = (right1) && (right2) && (right3);//右侧对齐
	if ((r1.x == 9073) && (r1.y == 111) && (r1.width == 14) && (r1.height == 8))
	{
		waitKey();
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

	bool flag3 = (choosecent1) && (0.35 < x2) && (x2 < 2.55) && (0.25 < x5) && (x5 < 4) && (0.3 < xh1) && (xh2 < 3.3);//比较矩形坐标中心小于6相邻两矩形的宽和面积
	//bool flag3 = (x2 >= 2.5) && (x2 <= 0.4);
	bool flag4 = (choosecent2) && (0.52 < x2) && (x2 < 1.92) && (0.25 < x5) && (x5 < 4) && (0.4 < xh1) && (xh1 < 2.5);//比较大于6的时候的情况
	bool flag5 = (choosecent3) && (0.35 < x2) && (x2 < 2.55) && (x4 < 2.55) && (0.25 < x6) && (x6 < 4) && (0.3 < xh2) && (xh2 < 3.3);//比较当前和上上一个的比值
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

	bool flag3 = (choosecent1) && (0.35 < x2) && (x2 < 2.55) && (0.25 < x5) && (x5 < 4) && (0.3 < xh) && (xh < 3.3);//比较矩形坐标中心小于6相邻两矩形的宽和面积
	//bool flag3 = (x2 >= 2.5) && (x2 <= 0.4);
	bool flag4 = (choosecent2) && (0.52 < x2) && (x2 < 1.92) && (0.25 < x5) && (x5 < 4) && (0.4 < xh) && (xh < 2.5);//比较大于6的时候的情况

	if (flag3 || flag4){
		return 1;
	}
	else{
		return 0;
	}
}

void  cLayer::Caclute()
{
	m_i_PointCentXMax = m_vector_LayerPoint[0].x;
	m_i_PointCentXMin = m_vector_LayerPoint[0].x;
	for (int i= 0; i <m_vector_LayerPoint.size();i++)
	{

	}
};