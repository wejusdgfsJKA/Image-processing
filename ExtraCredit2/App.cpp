#include<iostream>
#include "Tests.h"
#include "Image.h"
#include<fstream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <string>
#include "ImageAdjustment.h"
#include "ImageCorrection.h"
#include "ImageConvolution.h"
using std::cout;
using std::cin;
using std::string;
using std::ifstream;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	TestEverything();

	{
		Image i1;
		bool b = i1.load("baboon.ascii.pgm");
		cout << b << "\n";
		b = i1.save("Output1.ascii.pgm");
		cout << b;
	}

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
}