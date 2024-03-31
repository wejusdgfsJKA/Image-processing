#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <string>
#include <exception>
#include <iostream>
#include "Tests.h"
#include "Image.h"
#include "ImageAdjustment.h"
#include "ImageCorrection.h"
#include "ImageConvolution.h"
#include "DrawingModule.h"
using std::cout;
using std::cin;
using std::getline;
using std::string;
using std::ifstream;
using std::invalid_argument;

int SobelScaling(int x) {
	//scaling function for Sobel kernels
	return x / 16 + 255 / 2;
}

int IdentityScaling(int x) {
	return x;
}

int BlurScaling(int x) {
	return x / 9;
}

int GaussianBlurScaling(int x) {
	return x / 16;
}

float ReadNumber() 
{
	cout << "\nOption: ";
	string s;
	getline(cin, s);
	return std::stof(s);
}

float ReadNumber(string o) 
{
	cout << o;
	string s;
	getline(cin, s);
	return std::stof(s);
}

void ImageOptions(Image& img) 
{
	Image tmp;
	string img_commands = "\n1 - Display all commands.\n2 - Display current image.\n3 - Load from default input file.\n4 - Save to default output file.\n5 - Load from given file.\n6 - Save to given file.\n7 - Get ROI.\n0 - Exit.\n";
	int opt = 1;
	cout << img_commands;
	while (opt != 0) 
	{
		opt = unsigned int(ReadNumber());
		if (opt == 1) 
		{
			cout << img_commands;
		}
		if (opt == 2) 
		{
			cout << img;
		}
		if (opt == 3) 
		{
			if (tmp.load("TestImage4.txt")) 
			{
				img = tmp;
			}
		}
		if (opt == 4) 
		{
			img.save("Output1.ascii.pgm");
		}
		if (opt == 5) 
		{
			string s;
			getline(cin, s);
			if (tmp.load(s)) 
			{
				img = tmp;
			}
		}
		if (opt == 6)
		{
			string s;
			getline(cin, s);
			img.save(s);
		}
		if (opt == 7) {
			unsigned int x = unsigned int(ReadNumber("X: "));
			unsigned int y = unsigned int(ReadNumber("Y: "));
			unsigned int width = unsigned int(ReadNumber("Width: "));
			unsigned int height = unsigned int(ReadNumber("Height: "));
			img.getROI(tmp, x, y, width, height);
			cout << tmp;
		}
		if (opt > 7)throw invalid_argument("Invalid option!");
	}
}

void ProcOptions(Image& img) 
{
	Image tmp;
	ImageAdjustment adj{ 1,0 };
	ImageCorrection corr{ 1 };
	int kernel[3][3] = { 0 };
	kernel[1][1] = 1;
	ImageConvolution conv{ IdentityScaling,kernel };
	string proc_commands = "\n1 - Display commands.\n2 - Display image.\n3 - Adjust image (saves result in Output2.ascii.pgm).\n4 - Correct image (saves result in Output2.ascii.pgm).\n5 - Convolute image (saves result in Output2.ascii.pgm).\n6 - Change adjustment params.\n7 - Change correction params.\n8 - Change convolution params.\n0 - Exit.\n";
	unsigned int opt = 1;

	while (opt != 0) 
	{
		cout << proc_commands;

		opt = unsigned int(ReadNumber());

		if (opt == 1) 
		{
			cout << proc_commands;
		}
		
		if (opt == 2) 
		{
			cout << img;
		}
		
		if (opt == 3) 
		{
			adj.process(img, tmp);
			bool b=tmp.save("Output2.ascii.pgm");
			b;
		}
		
		if (opt == 4)
		{
			corr.process(img, tmp);
			tmp.save("Output2.ascii.pgm");
		}
		
		if (opt == 5)
		{
			conv.process(img, tmp);
			tmp.save("Output2.ascii.pgm");
		}
		
		if (opt == 6)
		{
			float gain, bias;
			gain = ReadNumber("Gain: ");
			bias = ReadNumber("Bias: ");
			adj = ImageAdjustment(gain, bias);
		}
		
		if (opt == 7)
		{
			float gamma = ReadNumber("Gamma: ");
			corr = ImageCorrection(gamma);
		}
		
		if (opt == 8)
		{
			cout << "\n0 - Identity conv.\n1 - Blur conv.\n2 - Gaussian blur conv.\n3 - Vertical Sobel conv.\n4 - Horizontal Sobel conv.\n";
			unsigned int o = unsigned int(ReadNumber());
			if (o > 4)throw invalid_argument("Invalid input!");

			if (o == 0)
			{
				int k[3][3] = { 0 };
				k[1][1] = 1;
				conv = ImageConvolution{ IdentityScaling,k };
			}

			if (o == 1) 
			{
				int k[3][3];
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++) {
						k[i][j] = 1;
					}
				}
				conv = ImageConvolution{ BlurScaling,k };
			}

			if (o == 2)
			{
				int k[3][3];
				k[0][0] = k[2][0] = k[2][2] = k[0][2] = 1;
				k[1][1] = 4;
				k[0][1] = k[1][0] = k[1][2] = k[2][1] = 2;
				conv = ImageConvolution{ GaussianBlurScaling,k };
			}

			if (o == 3)
			{
				int k[3][3] = { 0 };
				k[0][0] = k[2][0] = 1;
				k[0][2] = k[2][2] = -1;
				k[1][0] = 2;
				k[1][2] = -2;
				conv = ImageConvolution{ SobelScaling,k };
			}

			if (o == 4)
			{
				int k[3][3] = { 0 };
				k[0][0] = k[0][2] = 1;
				k[0][1] = 2;
				k[2][1] = -2;
				k[2][0] = k[2][2] = -1;
				conv = ImageConvolution{ SobelScaling,k };
			}

		}
		
		if (opt > 8)throw invalid_argument("Invalid input!");
	}
}

void DrawOptions(Image& img) 
{
	DrawingModule draw;
	unsigned int opt = 1;
	string draw_commands = "\n1 - Display commands.\n2 - Display image.\n3 - Draw a circle (saves result in Output2.ascii.pgm).\n4 - Draw a line (saves result in Output2.ascii.pgm).\n5 - Draw a rectangle (saves result in Output2.ascii.pgm).\n0 - Exit.\n";
	cout << draw_commands;
	Image tmp;

	while (opt != 0) {
		
		opt = unsigned int(ReadNumber());
		
		if (opt == 1) {
			cout << draw_commands;
		}

		if (opt == 2) {
			cout << img;
		}
		
		if (opt == 3) {
			tmp = img;
			int x = int(ReadNumber("X: "));
			int y = int(ReadNumber("Y: "));
			int radius = int(ReadNumber("Radius: "));
			unsigned int color = unsigned int(ReadNumber("Color: "));
			draw.drawCircle(tmp, Point(x, y), radius, color);
			cout << tmp;
			tmp.save("Output2.ascii.pgm");
		}

		if (opt == 4) {
			tmp = img;
			int x1 = int(ReadNumber("X1: "));
			int y1 = int(ReadNumber("Y1: "));
			int x2 = int(ReadNumber("X2: "));
			int y2 = int(ReadNumber("Y2: "));
			unsigned int color = unsigned int(ReadNumber("Color: "));
			draw.drawLine(tmp, Point(x1, y1), Point(x2,y2), color);
			cout << tmp;
			tmp.save("Output2.ascii.pgm");
		}

		if (opt == 5) {
			tmp = img;
			int x1 = int(ReadNumber("X1: "));
			int y1 = int(ReadNumber("Y1: "));
			int x2 = int(ReadNumber("X2: "));
			int y2 = int(ReadNumber("Y2: "));
			unsigned int color = unsigned int(ReadNumber("Color: "));
			draw.drawRectangle(tmp, Point(x1, y1), Point(x2, y2), color);
			cout << tmp;
			tmp.save("Output2.ascii.pgm");
		}
	}
}

int main() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	TestEverything();

	{
		Image current{ 15,15 };
		int opt = 1;
		string commands = "1 - Image commands.\n2 - Image processing commands.\n3 - Drawing commands.\n0 - Exit.\n";
		
		while (opt != 0) 
		{
			cout << commands;

			try
			{
				opt = unsigned int(ReadNumber());

				if (opt == 1) 
				{
					ImageOptions(current);
				}

				if (opt == 2) 
				{
					ProcOptions(current);
				}

				if (opt == 3) 
				{
					DrawOptions(current);
				}

				if (opt > 3)throw invalid_argument("Invalid option!");
			}
			catch (...) 
			{
				cout << "An error occurred.\n";
			}
		}
	}

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
}