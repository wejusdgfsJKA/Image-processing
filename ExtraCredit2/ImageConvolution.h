#pragma once
#include "ImageProcessing.h"

typedef int (*ScaleFct)(int input);

class ImageConvolution : public ImageProcessing {

public:
	ImageConvolution(ScaleFct scale, const Image& kernel);
	void process(const Image& src, Image& dst);
	

private:
	Image kernel;
	int Convolve(Image& roi);
	ScaleFct scale;
};