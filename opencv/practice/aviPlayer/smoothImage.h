#ifndef SMOOTHIMAGE_H
#define SMOOTHIMAGE_H

#include <opencv2/highgui.hpp>

void smoothImage(IplImage* image);
IplImage* doPyrDown(IplImage* image);

#endif // !SMOOTHIMAGE_H
