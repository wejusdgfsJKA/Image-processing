#include "ImageProcessing.h"
#include "ImageAdjustment.h"
#include "ImageCorrection.h"
#include "ImageConvolution.h"
#include <assert.h>
#include<iostream>
using std::cout;

int IdentityScaling(int x) {
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
	Image kernel;
	Image target;
	Image expected;
	
	expected.load("ConvolutedImage1.txt");
	img.load("TestImage1.txt");
	kernel.load("Kernel1.txt");
	ImageConvolution conv = ImageConvolution(IdentityScaling, kernel);
	conv.process(img, target);
	assert(target.width() == img.width() - (kernel.width() - 1) && target.height() == img.height() - (kernel.height() - 1));
	for (unsigned int i = 0; i < target.height(); i++) {
		for (unsigned int j = 0; j < target.width(); j++) {
			assert(target.at(j, i) == expected.at(j, i));
		}
	}

	expected.load("ConvolutedImage2.txt");
	img.load("TestImage2.txt");
	kernel.load("MeanBlurKernel.txt");
	conv = ImageConvolution(MeanBlurScaling, kernel);
	conv.process(img, target);
	assert(target.width() == img.width() - (kernel.width() - 1) && target.height() == img.height() - (kernel.height() - 1));
	for (unsigned int i = 0; i < target.height(); i++) {
		for (unsigned int j = 0; j < target.width(); j++) {
			assert(target.at(j, i) == expected.at(j, i));
		}
	}

	expected.load("ConvolutedImage3.txt");
	img.load("TestImage4.txt");
	kernel.load("Kernel2.txt");
	conv = ImageConvolution(IdentityScaling, kernel);
	conv.process(img, target);
	assert(target.width() == img.width() - (kernel.width() - 1) && target.height() == img.height() - (kernel.height() - 1));
	for (unsigned int i = 0; i < target.height(); i++) {
		for (unsigned int j = 0; j < target.width(); j++) {
			assert(target.at(j, i) == expected.at(j, i));
		}
	}
}

void TestImageProcessing() {
	TestImageAdjustment();
	TestImageCorrection();
	TestImageConvolution();
}
