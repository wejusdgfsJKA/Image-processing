#pragma once
#include "ImageProcessing.h"

class ImageAdjustment : public ImageProcessing {

public:
	ImageAdjustment();
	ImageAdjustment(float gain, float bias);
	void process(const Image& src, Image& dst);

private:
	float gain, bias;
};