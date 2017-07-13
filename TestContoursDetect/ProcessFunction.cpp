#include "ProcessFunction.h"


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

	//将轮廓对应图像 上   同意属性的轮廓进行连线
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