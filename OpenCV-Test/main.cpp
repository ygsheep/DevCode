/*
 * author: yysheep
 * date: date
 *
 */

#include <opencv2/opencv.hpp>
#include <stdio.h>

int main(int argc, char **argv) {
  cv::Mat image; // variable image of datatype Matrix
  image = cv::imread("./test.jpg");
	auto size = image.size();
	int w = size.width;
	int h = size.height;
	cv::Mat re_image;
	cv::resize(image,re_image,cv::Size((int)w/2, (int)h/2));
  cv::imshow("Display Image", image);
  cv::waitKey(0);
  return 0;
}
