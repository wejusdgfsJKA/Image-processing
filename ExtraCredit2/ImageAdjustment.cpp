#include "ImageAdjustment.h"

ImageAdjustment::ImageAdjustment() {
	gain = 1;
	bias = 0;
}

ImageAdjustment::ImageAdjustment(float gain,float bias) {
	if (gain == 0)throw("Invalid gain!");
	this->gain = gain;
	this->bias = bias;
}

void ImageAdjustment::process(const Image& src, Image& dst) {
	dst = Image(src);
	for (unsigned int i = 0; i < dst.height(); i++) {
		for (unsigned int j = 0; j < dst.width(); j++) {
			float a = gain * float(dst.at(j, i)) + bias;
			if (a < 0)
				a = 0;
			if (a > 255)
				a = 255;
			dst.at(j, i) = a;
		}
	}
}

float ImageAdjustment::get_gain()const {
	return gain;
}

float ImageAdjustment::get_bias()const {
	return bias;
}