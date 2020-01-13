#include<opencv2/objdetect/objdetect.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<opencv2/imgproc/imgproc.hpp>  
#include<opencv2/video/video.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <iostream>

using namespace cv;
using namespace std;

CascadeClassifier faceCascade;

int main()
{
	faceCascade.load("C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt2.xml");

	VideoCapture capture;
	capture.open(0); // 打开摄像头
	//capture.open("C:\\Users\\huang\\Desktop\\VS_repos\\videos\\sample2.mp4");// 打开视频
	if (!capture.isOpened())
	{
		cout << "open camera failed. " << endl;
		return -1;
	}

	Mat img, imgGray;
	vector<Rect> faces;
	int num = 0;
	int width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	cv::VideoWriter writer("C:\\Users\\huang\\Desktop\\VS_repos\\videos\\sample2.avi", CV_FOURCC('M', 'J', 'P', 'G'), 34, Size(width, height));
	cout << capture.get(CV_CAP_PROP_FPS);
	//视频的帧数会影响生成视频的速度。视频的size是不可以变化的，
	//必须依照capture.get(CV_CAP_PROP_FRAME_WIDTH);和capture.get(CV_CAP_PROP_FRAME_HEIGHT);

	while (1)
	{	
		
		capture >> img;// 读取图像至img

		for (int i = 0; i < img.cols-50;i++){
			img.col(i + 50) = img.col(i);
			img.col(i) = 0;
			
		}

		// 480*240 col的数值就是480；row的数值就是240；
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
	
		writer.write(img);
		imshow("CamerFace", img); // 显示
		
		if (waitKey(1) > 0)		// delay ms 等待按键退出
		{
			break;
		}
	}

	return 0;
}

