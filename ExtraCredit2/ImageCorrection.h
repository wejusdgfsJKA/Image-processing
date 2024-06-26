#pragma once
#include "ImageProcessing.h"

class ImageCorrection: public ImageProcessing {
public:
	ImageCorrection(float gamma);
	void process(const Image& src, Image& dst) override;
private:
	float gamma;
};