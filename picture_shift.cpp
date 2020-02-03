#include<opencv2/objdetect/objdetect.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<opencv2/imgproc/imgproc.hpp>  
#include<opencv2/video/video.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <iostream>
#include <opencv2/features2d/features2d.hpp>


using namespace cv;
using namespace std;

Mat translateImg(Mat& img, int offsetx, int offsety) {
	Mat trans_mat = (Mat_<double>(2, 3) << 1, 0, offsetx, 0, 1, offsety);
	warpAffine(img, img, trans_mat, img.size());
	return img;
}
bool ArrayCheck(int a) {
	return true;
}

int main()
{
	VideoCapture capture,capture1;
	capture.open("C:\\Users\\huang\\Desktop\\VS_repos\\videos\\original.avi"); // 打开摄像头
	capture1.open("C:\\Users\\huang\\Desktop\\VS_repos\\videos\\shift.avi");
	if (!capture.isOpened())
	{
		cout << "open camera failed. " << endl;
		return -1;
	}

	if (!capture1.isOpened()) {
		cout << "open camera failed " << endl;
		return -1;
	}

	Mat img,imgGray,img1,imgGray1,temp,temp1,dst,dst1;
	int i = 0;
	while (1)
	{

		capture >> img;// 读取图像至img
		capture1 >> img1;

		if (img.empty())
		{
			break;
		}
		if (img.channels() == 3)
		{
			cvtColor(img, imgGray, 7);
			cvtColor(img1, imgGray1, 7);
			imgGray.convertTo(dst, CV_32FC1);
			imgGray1.convertTo(dst1, CV_32FC1);
		}
		else
		{
			imgGray = img;
			imgGray1 = img1;
			imgGray.convertTo(dst, CV_32FC1);
			imgGray1.convertTo(dst1, CV_32FC1);
		}
		vector<KeyPoint> keypoints;
		vector<KeyPoint> keypoints1;

		//FastFeatureDetector fast(imgGray,keypoints,40);
		//fast.detect(imgGray, keypoints);
		FAST(imgGray, keypoints, 10);
		FAST(imgGray1, keypoints1, 10);
		


		drawKeypoints(imgGray,keypoints,temp,-1, DrawMatchesFlags::DEFAULT);
		drawKeypoints(imgGray1, keypoints1, temp1, -1, DrawMatchesFlags::DEFAULT);
		
		cout <<"the key points of imgGray: " <<  keypoints.size() << endl;
		cout <<"the key points of imgGray1: " << keypoints1.size() << endl;

		FlannBasedMatcher matcher;
		vector<DMatch> matchPoints;
		//matcher.match(imgGray,imgGray1,matchPoints,Mat());

		//cout << "total match points : " << matchPoints.size() << endl;
		//Point2d phase_shift;
		//phase_shift = phaseCorrelate(dst1, dst); get the shift degree
		/*
		cout << endl << "warp :" << endl << "\tX shift : " << phase_shift.x << "\tY shift : " << phase_shift.y << endl;
		double radius = sqrt(phase_shift.x * phase_shift.x + phase_shift.y * phase_shift.y);
		if (radius > 1) {
			Point center(imgGray.cols >> 1, imgGray.rows >> 1);
			circle(img, center, (int)radius, Scalar(0, 255, 0), 3, LINE_AA);
			line(img, center, Point(center.x + (int)phase_shift.x, center.y + (int)phase_shift.y), Scalar(0, 255, 0), 3, LINE_AA);
		}
		//phaseCorrelate(imgGray,imgGray1,NULL,0.5);*/
		imshow("origin", temp); // 显示
		imshow("shift", temp1); // 显示
		imshow("test",img);
		if (waitKey(1) == 27)		// delay ms 等待按键退出
		{
			break;
		}
		i++;
	}

	return 0;
}

