#include "Tests.h"
#include <assert.h>
#include "Image.h"

void TestRectangleTranslate() {
	Rectangle r1{ 0,3,6,3 };
	assert(r1 - Point(-1, 6) == Rectangle(1, -3, 6, 3));
	assert(r1 + Point(-1, 6) == Rectangle(-1, 9, 6, 3));
}

void TestRectangleOther() {
	Rectangle r1{ 0,3,6,3 }, r2{ 2,1,5,2 }, r3{0,1,5,2};
	assert((r1 & r2) == Rectangle(2, 1, 4, 1));
	assert((r1 & r1) == r1);
	assert((r2 & r1) == Rectangle(2, 1, 4, 1));
	assert((r1 & r3) == Rectangle(0, 1, 5, 1));
	assert((r1 | r2) == Rectangle(0, 3, 7, 4));
	assert((r2 | r1) == Rectangle(0, 3, 7, 4));
	assert((r1 | r1) == Rectangle(0, 3, 6, 3));
	assert((r3 | r2) == Rectangle(0, 1, 7, 2));
}

void TestRectangle() {
	TestRectangleTranslate();
	TestRectangleOther();
}

void TestImageOther() {
	Image i1{ 4,4 };
	assert(i1.at(0, 0) == 0);
	i1.at(0, 0) = 5;
	assert(i1.at(Point(0, 0)) == 5);
	i1.at(Point(1, 3)) = 4;
	assert(i1.at(1, 3) == 4);
	i1.at(0, 3) = 7;
	assert(i1.at(Point(0, 3)) == 7);
}

void TestImageOperators() {
	
	Image i1 = Image::ones(4, 4);
	assert(i1.width() == 4 && i1.height() == 4);
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(int(i1.at(j, i)) == 1);
		}
	}
	
	i1 = i1 * 5;
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(int(i1.at(j, i)) == 5);
		}
	}
	
	Image i2 = Image::ones(4, 4);
	i1 = i1 + i2;
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(int(i1.at(j, i)) == 6);
		}
	}
	
	Image i3 = Image::ones(4, 4);
	i3 = i3 * 4;
	i1 = i1 - i3;
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(int(i1.at(j, i)) == 2);
		}
	}
}

void TestImageRoi() {
	
	Image i1, i2;
	i1.load("TestImage.txt");

	i1.getROI(i2, 0, 0, 1, 1);
	assert(i2.width() == 1 && i2.height() == 1);
	assert(i2.at(0, 0) == 9);

	i1.getROI(i2, 1, 3, 2, 3);
	assert(i2.width() == 2 && i2.height() == 3);
	assert(i2.at(0, 0) == 1);
	assert(i2.at(0, 1) == 8);
	assert(i2.at(1, 0) == 1);
	assert(i2.at(1, 1) == 2);
	assert(i2.at(0, 2) == 3);
	assert(i2.at(1, 2) == 3);

	i1.getROI(i2, Rectangle(0,0,1,1));
	assert(i2.width() == 1 && i2.height() == 1);
	assert(i2.at(0, 0) == 9);

	i1.getROI(i2, Rectangle(1, 3, 2, 3));
	assert(i2.width() == 2 && i2.height() == 3);
	assert(i2.at(0, 0) == 1);
	assert(i2.at(0, 1) == 8);
	assert(i2.at(1, 0) == 1);
	assert(i2.at(1, 1) == 2);
	assert(i2.at(0, 2) == 3);
	assert(i2.at(1, 2) == 3);
}

void TestImage() {
	TestImageOther();
	TestImageOperators();
	TestImageRoi();
}

void TestEverything() {
	TestRectangle();
	TestImage();
}