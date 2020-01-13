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
	//capture.open("C:\\Users\\huang\\Desktop\\VS_repos\\videos\\sample2.mp4");// 打开视频
	if (!capture.isOpened())
	{
		cout << "open camera failed. " << endl;
		return -1;
	}

	Mat img, imgGray;
	int width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	cv::VideoWriter writer("C:\\Users\\huang\\Desktop\\VS_repos\\videos\\sample2.avi", CV_FOURCC('M', 'J', 'P', 'G'), 34, Size(width, height));
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
		/*for (int i = img.rows-1 ; i > 0; i--) {
			if (i <= 100) {
				img2.row(i) = 0;
			}
			else {
				img2.row(i) = img.row(i);
				if(i == 101){
					cout << "copy:" << endl;
					cout << img2.row(i) << endl;
					cout << "original " << endl;
					cout << img.row(i) << endl;
				}
			}
		}*/
		translateImg(img, 50, 50);
		writer.write(img);
		imshow("Cameral shifting", img); // 显示
		if (waitKey(1) > 0)		// delay ms 等待按键退出
		{
			break;
		}
	}

	return 0;
}

