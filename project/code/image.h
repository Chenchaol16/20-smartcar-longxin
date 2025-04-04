#ifndef IMAGE_h
#define IMAGE_h


#include "zf_common_headfile.h"


#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

short GetOSTU (unsigned char tmImage[UVC_HEIGHT][UVC_WIDTH]);
void Bin_Image_Filter(unsigned char Bin_Image[UVC_HEIGHT][UVC_WIDTH]);
void Horizontal_line(unsigned char Pixle[UVC_HEIGHT][UVC_WIDTH], int Row, int Col, int midline[], int leftline[], int rightline[]);
void binary_ipsdrawline();



#endif