#include<iostream>
#include "Tests.h"
#include "Image.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "ImageAdjustment.h"
#include "ImageCorrection.h"
#include "ImageConvolution.h"
using std::cout;
using std::cin;
using std::string;
using std::ifstream;

int SobelScaling(int x) {
	//scaling function for Sobel kernels
	return x / 16 + 255 / 2;
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	{
		Image i1;

		bool b = i1.load("baboon.ascii.pgm");
		cout << b << "\n";
		int h_kernel[3][3] = { 0 };
		h_kernel[0][0] = h_kernel[0][2] = 1;
		h_kernel[2][0] = h_kernel[2][2] = -1;
		h_kernel[0][1] = 2;
		h_kernel[2][1] = -2;
		ImageConvolution conv(SobelScaling, h_kernel);
		
		Image output;
		conv.process(i1, output);
		b = output.save("Output1.ascii.pgm");
		cout << b<<"\n";

		b = i1.load("balloons.ascii.pgm");
		cout << b << "\n";
		h_kernel[3][3] = { 0 };
		h_kernel[0][0] = h_kernel[2][0] = 1;
		h_kernel[0][2] = h_kernel[2][2] = -1;
		h_kernel[1][0] = 2;
		h_kernel[1][2] = -2;
		conv = ImageConvolution(SobelScaling, h_kernel);
		conv.process(i1, output);
		b = output.save("Output2.ascii.pgm");
		cout << b;
	}
	
	TestEverything();

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
}