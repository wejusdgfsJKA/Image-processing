#pragma once
#include "ImageProcessing.h"

class ImageAdjustment : public ImageProcessing {

public:
	ImageAdjustment();
	ImageAdjustment(float gain, float bias);
	void process(const Image& src, Image& dst) override;
	float get_gain()const;
	float get_bias()const;

private:
	float gain, bias;
};