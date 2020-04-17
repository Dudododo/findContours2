#include <iostream>
#include <opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat srcMat = imread("die_on_chip.png", 1);
	Mat dstMat, binMat;
	cvtColor(srcMat, dstMat, COLOR_BGR2GRAY);
	threshold(dstMat, binMat, 140, 255, THRESH_BINARY);

	//通过findContours函数寻找连通域
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binMat, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

	//绘制轮廓
	for (int i = 0; i < contours.size(); i++) 
	{
		RotatedRect rbox = minAreaRect(contours[i]);
		if (fabs(rbox.size.width / rbox.size.height - 1) < 0.1 && rbox.size.width > 15 && rbox.size.height > 15)
		{
			drawContours(srcMat, contours, i, Scalar(0, 255, 255), 1, 8);
			Point2f vtx[4];
			rbox.points(vtx);
			for (int j = 0; j < 4; ++j) {
				cv::line(srcMat, vtx[j], vtx[j < 3 ? j + 1 : 0], Scalar(0, 0, 255), 2, LINE_AA);
			}
		}
	}

	imshow("srcMat", srcMat);
	imshow("binMat", binMat);
	waitKey(0);
}

