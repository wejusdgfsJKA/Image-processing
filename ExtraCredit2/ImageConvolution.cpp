#include "ImageConvolution.h"
#include<iostream>
using std::cout;
#define kwidth 3
#define kheight 3
ImageConvolution::ImageConvolution(ScaleFct scale, const int kernel[3][3]) {
	this->scale = scale;
	for (int i = 0; i < kheight; i++) {
		for (int j = 0; j < kwidth; j++) {
			this->kernel[i][j] = kernel[i][j];
		}
	}
}

int ImageConvolution::Convolve(Image& roi) const{
	int s = 0;
	for (unsigned int i = 0; i < roi.height(); i++) {
		for (unsigned int j = 0; j < roi.width(); j++) {
			s += kernel[i][j] * roi.at(j, i);
		}
	}
	return scale(s);
}

void ImageConvolution::process(const Image& src, Image& dst) {
	Image dummy{ src }, temp;
	dst = Image(src.width() - (kwidth - 1), src.height() - (kheight - 1));
	for (unsigned int i = 1; i < src.height() - kheight / 2; i++) {
		for (unsigned int j = 1; j < src.width() - kwidth / 2; j++) {
			dummy.getROI(temp, j - kwidth / 2, src.height() - kheight / 2 - i + 1, kwidth, kheight);
			dst.at(j - kwidth / 2, i - kheight / 2) = Convolve(temp);
		}
	}
}