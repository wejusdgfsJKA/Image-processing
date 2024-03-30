#pragma once
#include "ImageProcessing.h"

typedef int (*ScaleFct)(int input);

class ImageConvolution : public ImageProcessing {

public:
	ImageConvolution(ScaleFct scale, const int kernel[3][3]);
	void process(const Image& src, Image& dst);
	

private:
	int kernel[3][3];
	int Convolve(Image& roi)const;
	ScaleFct scale;
};