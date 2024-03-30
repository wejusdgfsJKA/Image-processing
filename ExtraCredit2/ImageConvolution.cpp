#include "ImageConvolution.h"
#include<iostream>
using std::cout;

ImageConvolution::ImageConvolution(ScaleFct scale, const Image& kernel) {
	this->scale = scale;
	this->kernel = kernel;
}

int ImageConvolution::Convolve(Image& roi) {
	int s = 0;
	for (unsigned int i = 0; i < roi.height(); i++) {
		for (unsigned int j = 0; j < roi.width(); j++) {
			s += kernel.at(j, i) * roi.at(j, i);
		}
	}
	return scale(s);
}

void ImageConvolution::process(const Image& src, Image& dst) {
	Image dummy{ src }, temp;
	dst = Image(src.width() - (kernel.width() - 1), src.height() - (kernel.height() - 1));
	for (unsigned int i = 1; i < src.height() - kernel.height() / 2; i++) {
		for (unsigned int j = 1; j < src.width() - kernel.width() / 2; j++) {
			//int a = j - kernel.width() / 2;
			//int b = src.height() - kernel.height() / 2 - i + 1;
			dummy.getROI(temp, j - kernel.width() / 2, src.height() - kernel.height() / 2 - i + 1, kernel.width(), kernel.height());
			dst.at(j - kernel.width() / 2, i - kernel.height() / 2) = Convolve(temp);
		}
	}
}