#include "ImageCorrection.h"
#include <cmath>

ImageCorrection::ImageCorrection(float gamma) {
	this->gamma = gamma;
}

void ImageCorrection::process(const Image& src, Image& dst) {
	dst = Image(src);
	for (unsigned int i = 0; i < dst.height(); i++) {
		for (unsigned int j = 0; j < dst.width(); j++) {
			dst.at(j, i) = pow(dst.at(j, i), this->gamma);
		}
	}
}