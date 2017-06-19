#include "smoothImage.h"
#include "opencv2/opencv.hpp"

void smoothImage(IplImage* image)
{
	IplImage* outImage = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
	cvSmooth(image, outImage, CV_GAUSSIAN, 3, 3);
	cvShowImage("aviPlayer", outImage);
	cvReleaseImage(&outImage);
}

IplImage* doPyrDown(IplImage* image)
{
	IplImage* outImage = cvCreateImage(cvSize(image->width,image->height), image->depth, image->nChannels);
	cvPyrDown(image, outImage);
	return (outImage);
	//cvReleaseImage(&outImage);
}

