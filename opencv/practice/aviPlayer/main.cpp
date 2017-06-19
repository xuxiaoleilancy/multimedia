#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include "smoothImage.h"
#include "opencv2/opencv.hpp"

int g_slider_position = 0;
CvCapture* g_capture = NULL;

void onTrackbarSlide(int pos)
{
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos);
}

int main(int argc , char** argv)
{
	cvNamedWindow("aviPlayer", CV_WINDOW_AUTOSIZE);
	g_capture = cvCreateFileCapture(argv[1]);
	
	int frames = (int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_COUNT);
	if (frames != 0){
		cvCreateTrackbar("Position", "aviPlayer", &g_slider_position, frames, onTrackbarSlide);
	}
	IplImage* frame;
	IplImage* outImage;
	while (1){
		frame = cvQueryFrame(g_capture);

		if (!frame) break;
		//smoothImage(frame);
		outImage = doPyrDown(frame);
		cvShowImage("aviPlayer",outImage);
		char c = cvWaitKey(33);

		cvReleaseImage(&outImage); 
		if (c == 27)break;
	}

	cvReleaseCapture(&g_capture);
	cvDestroyWindow("aviPlayer");

	return 0;
}