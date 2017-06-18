#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

int main(int argc , char** argv)
{
	IplImage* img = cvLoadImage(argv[1]);
	cvNamedWindow("Example",CV_WINDOW_AUTOSIZE);
	cvShowImage("Example",img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow("Example");
}