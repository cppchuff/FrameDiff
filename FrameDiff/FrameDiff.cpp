
#include "core/core.hpp"

#include "highgui/highgui.hpp"

#include "imgproc/imgproc.hpp"



using namespace cv;



int main(int argc, char* argv[])

{

	VideoCapture videoCap("EZVZ0048.mp4");

	if (!videoCap.isOpened())

	{

		return -1;

	}

	double videoFPS = videoCap.get(CV_CAP_PROP_FPS);  //获取帧率

	double videoPause = 1000 / videoFPS;



	Mat framePre; //上一帧

	Mat frameNow; //当前帧

	Mat frameDet; //运动物体

	videoCap >> framePre;

	cvtColor(framePre, framePre, CV_RGB2GRAY);

	GaussianBlur(framePre, framePre, Size(7, 7), 0);

	Canny(framePre, framePre, 100, 250);

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //隔开物体

	dilate(framePre, framePre, element);//膨胀

	erode(framePre, framePre, element);//腐蚀
	

	while (true)

	{

		videoCap >> frameNow;

		if (frameNow.empty() || waitKey(2500) == 27)

		{

			break;

		}

		cvtColor(frameNow, frameNow, CV_RGB2GRAY);

		absdiff(frameNow, framePre, frameDet);

		framePre = frameNow;

		namedWindow("Video", WINDOW_NORMAL);
		//imshow("Video", frameNow);

		namedWindow("Detection",WINDOW_NORMAL);


		Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //隔开物体

		dilate(frameDet, frameDet, element);//膨胀

		erode(frameDet, frameDet, element);//腐蚀
		imshow("Detection", frameDet);

	}

	return 0;

}
