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

	Mat img,imgGray,img1,imgGray1,temp,temp1,temp2,dst,dst1;
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
			
		}
		else
		{
			imgGray = img;
			imgGray1 = img1;
		}
		
		
		
		
		vector<KeyPoint> keypoints;
		vector<KeyPoint> keypoints1;

		Mat descriptors1, descriptors2;
		Ptr<ORB> orb = ORB::create();
		orb->detect(imgGray, keypoints);
		orb->detect(imgGray1, keypoints1);

		orb->compute(imgGray, keypoints, descriptors1);
		orb->compute(imgGray1, keypoints1, descriptors2);

		Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
		vector< DMatch> matches;
		matcher->match(descriptors1, descriptors2, matches);

		cout << matches.size() << endl;

		drawKeypoints(imgGray,keypoints,temp,-1, DrawMatchesFlags::DEFAULT);
		drawKeypoints(imgGray1, keypoints1, temp1, -1, DrawMatchesFlags::DEFAULT);
		imshow("origin", temp); // 显示
		imshow("shift", temp1); // 显示


		cout <<"the key points of imgGray: " <<  keypoints.size() << endl;
		cout <<"the key points of imgGray1: " << keypoints1.size() << endl;
		Point2d phase_shift;
		imgGray.convertTo(dst, CV_32FC1);
		imgGray1.convertTo(dst1, CV_32FC1);
		phase_shift = phaseCorrelate(dst, dst1); //get the shift degree
		cout << endl << "warp :" << endl << "\tX shift : " << phase_shift.x << "\tY shift : " << phase_shift.y << endl;
		drawMatches(imgGray, keypoints, imgGray, keypoints1, matches, temp2);
		
		imshow("compare", temp2);
		
		
//imshow("test", temp2);
		if (waitKey(1) == 27)		// delay ms 等待按键退出
		{
			break;
		}
		i++;
	}

	return 0;
}

