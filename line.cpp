#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;


int	main() {
	Mat src = imread("D:/OpenCV/picture zone/wenben1.png");
	if (!src.data)
	{
		printf("ERROR");
	}
	namedWindow("input",CV_WINDOW_AUTOSIZE);
	imshow("input",src);

	Mat src_gray;
	cvtColor(src,src_gray,COLOR_BGR2GRAY);

	Mat src_hold;
	threshold(src_gray,src_hold,0,255,THRESH_BINARY_INV|THRESH_OTSU);
	imshow("threshold",src_hold);

	
	Mat src_erode;
	Mat qcol = getStructuringElement(MORPH_RECT, Size(src.cols / 16, 1), Point(-1, -1));
	//dilate(src_canny,src_erode,structureElement);
	morphologyEx(src_hold,src_erode,CV_MOP_OPEN,qcol);
	imshow("open",src_erode);

	vector<Vec4f>pline;
	HoughLinesP(src_erode,pline,1,CV_PI/180,30,30.0,0);


	for (size_t i = 0; i < pline.size(); i++)
	{
		Vec4f hine = pline[i];
		line(src,Point(hine[0],hine[1]),Point(hine[2],hine[3]),Scalar(0,0,255),3,0);

	}
	imshow("output", src);
	
	waitKey(0);
	return 0;
}