#include "ImageProcessing.h"
#include "ImageAdjustment.h"
#include "ImageCorrection.h"
#include "ImageConvolution.h"
#include <assert.h>
#include <fstream>
using std::ifstream;

int IdScaling(int x) {
	return x;
}

int MeanBlurScaling(int x) {
	return x / 9;
}

void TestImageAdjustment() {
	
	Image img;
	Image expected;
	Image target;
	ImageAdjustment adj;

	adj = ImageAdjustment(2, 1);
	img.load("TestImage1.txt");
	expected.load("AdjustedImage1.txt");
	adj.process(img, target);
	assert(target.width() == img.width() && target.height() == img.height());
	for (unsigned int i = 0; i < target.height(); i++) {
		for (unsigned int j = 0; j < target.width(); j++) {
			assert(target.at(j, i) == expected.at(j, i));
		}
	}

	adj = ImageAdjustment(.1, 3);
	img.load("TestImage2.txt");
	expected.load("AdjustedImage2.txt");
	adj.process(img, target);
	assert(target.width() == img.width() && target.height() == img.height());
	for (unsigned int i = 0; i < target.height(); i++) {
		for (unsigned int j = 0; j < target.width(); j++) {
			assert(target.at(j, i) == expected.at(j, i));
		}
	}

	adj = ImageAdjustment(.5, 2);
	img.load("TestImage3.txt");
	expected.load("AdjustedImage3.txt");
	adj.process(img, target);
	assert(target.width() == img.width() && target.height() == img.height());
	for (unsigned int i = 0; i < target.height(); i++) {
		for (unsigned int j = 0; j < target.width(); j++) {
			assert(target.at(j, i) == expected.at(j, i));
		}
	}
}

void TestImageCorrection() {

	Image img;
	Image expected;
	Image target;

	img.load("TestImage1.txt");
	expected.load("CorrectedImage1.txt");
	ImageCorrection corr(.5);
	corr.process(img, target);
	assert(target.width() == img.width() && target.height() == img.height());
	for (unsigned int i = 0; i < target.height(); i++) {
		for (unsigned int j = 0; j < target.width(); j++) {
			assert(target.at(j, i) == expected.at(j, i));
		}
	}

	img.load("TestImage2.txt");
	expected.load("CorrectedImage2.txt");
	corr = ImageCorrection(.3);
	corr.process(img, target);
	assert(target.width() == img.width() && target.height() == img.height());
	for (unsigned int i = 0; i < target.height(); i++) {
		for (unsigned int j = 0; j < target.width(); j++) {
			assert(target.at(j, i) == expected.at(j, i));
		}
	}

	img.load("TestImage3.txt");
	expected.load("CorrectedImage3.txt");
	corr=ImageCorrection(1.1);
	corr.process(img, target);
	assert(target.width() == img.width() && target.height() == img.height());
	for (unsigned int i = 0; i < target.height(); i++) {
		for (unsigned int j = 0; j < target.width(); j++) {
			assert(target.at(j, i) == expected.at(j, i));
		}
	}
}

void TestImageConvolution() {
	
	Image img;
	Image target;
	Image expected;
	int kernel[3][3] = { 0 };

	kernel[1][1] = 1;
	expected.load("ConvolutedImage1.txt");
	img.load("TestImage1.txt");
	ImageConvolution conv = ImageConvolution(IdScaling, kernel);
	conv.process(img, target);
	assert(target.width() == img.width() - 2 && target.height() == img.height() - 2);
	for (unsigned int i = 0; i < target.height(); i++) {
		for (unsigned int j = 0; j < target.width(); j++) {
			assert(target.at(j, i) == expected.at(j, i));
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			kernel[i][j] = 1;
		}
	}
	expected.load("ConvolutedImage2.txt");
	img.load("TestImage2.txt");
	conv = ImageConvolution(MeanBlurScaling, kernel);
	conv.process(img, target);
	assert(target.width() == img.width() - 2 && target.height() == img.height() - 2);
	for (unsigned int i = 0; i < target.height(); i++) {
		for (unsigned int j = 0; j < target.width(); j++) {
			assert(target.at(j, i) == expected.at(j, i));
		}
	}

	kernel[0][1] = 0;
	kernel[1][2] = 0;
	kernel[2][1] = 0;
	kernel[1][0] = 0;
	expected.load("ConvolutedImage3.txt");
	img.load("TestImage4.txt");
	conv = ImageConvolution(IdScaling, kernel);
	conv.process(img, target);
	assert(target.width() == img.width() - 2 && target.height() == img.height() - 2);
	for (unsigned int i = 0; i < target.height(); i++) {
		for (unsigned int j = 0; j < target.width(); j++) {
			int a = target.at(j, i); int b = expected.at(j, i);
			assert(target.at(j, i) == expected.at(j, i));
		}
	}
}

void TestImageProcessing() {
	TestImageAdjustment();
	TestImageCorrection();
	TestImageConvolution();
}
