#include "TestImage.h"
#include <assert.h>
#include "Image.h" 

void TestImageLoad() {

	Image i1;
	i1.load("TestImage1.txt");
	assert(i1.width() == 4 && i1.height() == 4);

	assert(int(i1.at(0, 0)) == 1);
	assert(int(i1.at(0, 1)) == 2);
	assert(int(i1.at(0, 2)) == 3);
	assert(int(i1.at(0, 3)) == 9);

	assert(int(i1.at(1, 0)) == 1);
	assert(int(i1.at(1, 1)) == 8);
	assert(int(i1.at(1, 2)) == 3);
	assert(int(i1.at(1, 3)) == 4);

	assert(int(i1.at(2, 0)) == 1);
	assert(int(i1.at(2, 1)) == 2);
	assert(int(i1.at(2, 2)) == 3);
	assert(int(i1.at(2, 3)) == 6);

	assert(int(i1.at(3, 0)) == 7);
	assert(int(i1.at(3, 1)) == 2);
	assert(int(i1.at(3, 2)) == 0);
	assert(int(i1.at(3, 3)) == 1);

	i1.load("TestImage2.txt");
	assert(i1.width() == 4 && i1.height() == 4);

	assert(int(i1.at(0, 0)) == 221);
	assert(int(i1.at(0, 1)) == 214);
	assert(int(i1.at(0, 2)) == 36);
	assert(int(i1.at(0, 3)) == 9);

	assert(int(i1.at(1, 0)) == 21);
	assert(int(i1.at(1, 1)) == 218);
	assert(int(i1.at(1, 2)) == 32);
	assert(int(i1.at(1, 3)) == 4);

	assert(int(i1.at(2, 0)) == 16);
	assert(int(i1.at(2, 1)) == 2);
	assert(int(i1.at(2, 2)) == 3);
	assert(int(i1.at(2, 3)) == 65);

	assert(int(i1.at(3, 0)) == 7);
	assert(int(i1.at(3, 1)) == 2);
	assert(int(i1.at(3, 2)) == 40);
	assert(int(i1.at(3, 3)) == 10);
}

void TestImageSave() {
	Image i1, expected;

	expected.load("TestImage1.txt");
	i1.load("TestImage1.txt");
	i1.save("Buffer.txt");
	i1.load("TestImage1.txt");
	assert(i1.width() == 4 && i1.height() == 4);
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(i1.at(j, i) == expected.at(j, i));
		}
	}

	expected.load("TestImage2.txt");
	i1.load("TestImage2.txt");
	i1.save("Buffer.txt");
	i1.load("TestImage2.txt");
	assert(i1.width() == 4 && i1.height() == 4);
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(i1.at(j, i) == expected.at(j, i));
		}
	}

	expected.load("TestImage3.txt");
	i1.load("TestImage3.txt");
	i1.save("Buffer.txt");
	i1.load("TestImage3.txt");
	assert(i1.width() == 4 && i1.height() == 4);
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(i1.at(j, i) == expected.at(j, i));
		}
	}
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

	Image i1 = Image::zeros(4, 4);
	assert(i1.width() == 4 && i1.height() == 4);
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(int(i1.at(j, i)) == 0);
		}
	}

	i1 = Image::ones(4, 4);
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
	i1.load("TestImage1.txt");

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

	i1.getROI(i2, Rectangle(0, 0, 1, 1));
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
	TestImageLoad();
	TestImageSave();
}