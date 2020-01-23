#include<opencv2/objdetect/objdetect.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<opencv2/imgproc/imgproc.hpp>  
#include<opencv2/video/video.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <iostream>

using namespace cv;
using namespace std;

Mat translateImg(Mat& img, int offsetx, int offsety) {
	Mat trans_mat = (Mat_<double>(2, 3) << 1, 0, offsetx, 0, 1, offsety);
	warpAffine(img, img, trans_mat, img.size());
	return img;
}

int main()
{
	VideoCapture capture;
	capture.open(0); // 打开摄像头
	if (!capture.isOpened())
	{
		cout << "open camera failed. " << endl;
		return -1;
	}

	Mat img, imgGray;
	while (1)
	{	
		
		capture >> img;// 读取图像至img

		if (img.empty())
		{
			continue;
		}
		if (img.channels() == 3)
		{
			cvtColor(img, imgGray, 7);
		}
		else
		{
			imgGray = img;
		}
		translateImg(img, 50, 50);
		imshow("Cameral shifting", img); // 显示
		if (waitKey(1) == 27)		// delay ms 等待按键退出
		{
			break;
		}
	}

	return 0;
}

