#include "TestDrawing.h"
#include <assert.h>
#include<iostream>
using std::cout;

void TestDrawLine() 
{
	Image i1{15,15}, expected;
	DrawingModule draw;
	
	expected.load("DrawnLine3.txt");
	draw.drawLine(i1, Point(4, 5), Point(8, 11), 7);
	for (int i = 0; i < expected.height(); i++) {
		for (int j = 0; j < expected.width(); j++) {
			assert(i1.at(j, i) == expected.at(j, i));
		}
	}
	
	i1 = Image(15, 15);
	expected.load("DrawnLine1.txt");
	draw.drawLine(i1, Point(0, 14), Point(0, 0), 7);
	for (int i = 0; i < expected.height(); i++){
		for (int j = 0; j < expected.width(); j++) {
			assert(i1.at(j, i) == expected.at(j, i));
		}
	}

	i1 = Image(15, 15);
	expected.load("DrawnLine2.txt");
	draw.drawLine(i1, Point(0, 0), Point(14, 0), 7);
	for (int i = 0; i < expected.height(); i++) {
		for (int j = 0; j < expected.width(); j++) {
			assert(i1.at(j, i) == expected.at(j, i));
		}
	}
}

void TestDrawCircle() 
{
	Image i1{15,15}, expected;
	DrawingModule draw;

	expected.load("DrawnCircle1.txt");
	draw.drawCircle(i1, Point(7, 7), 7, 7);
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(i1.at(j, i) == expected.at(j, i));
		}
	}

	i1 = Image{ 15,15 };
	expected.load("DrawnCircle2.txt");
	draw.drawCircle(i1, Point(7, 7), 8, 7);
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(i1.at(j, i) == expected.at(j, i));
		}
	}

	i1 = Image{ 20,20 };
	draw.drawCircle(i1, Point(9, 9), 8, 4);
	expected.load("DrawnCircle3.txt");
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(i1.at(j, i) == expected.at(j, i));
		}
	}
}
void TestDrawRectangle1() {
	
	Image i1, expected;
	DrawingModule draw;
	
	i1.load("TestImage4.txt");
	expected.load("DrawnRectangle1.txt");
	draw.drawRectangle(i1, Rectangle(0, 6, 7, 7), 20);
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(i1.at(j, i) == expected.at(j, i));
		}
	}

	i1.load("TestImage4.txt");
	expected.load("DrawnRectangle2.txt");
	draw.drawRectangle(i1, Rectangle(0, 4, 3, 5), 200);
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(i1.at(j, i) == expected.at(j, i));
		}
	}

	i1.load("TestImage4.txt");
	draw.drawRectangle(i1, Rectangle(5, 0, 0, 0), 13);
	expected.load("DrawnRectangle3.txt");
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(i1.at(j, i) == expected.at(j, i));
		}
	}
}

void TestDrawRectangle2() {

	Image i1, expected;
	DrawingModule draw;

	i1.load("TestImage4.txt");
	expected.load("DrawnRectangle1.txt");
	draw.drawRectangle(i1, Point(0, 6), Point(6, 0), 20);
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(i1.at(j, i) == expected.at(j, i));
		}
	}

	i1.load("TestImage4.txt");
	draw.drawRectangle(i1, Point(0,4), Point(2, 0), 200);
	expected.load("DrawnRectangle2.txt");
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(i1.at(j, i) == expected.at(j, i));
		}
	}

	i1.load("TestImage4.txt");
	draw.drawRectangle(i1, Point(5, 0), Point(6, 0), 13);
	expected.load("DrawnRectangle3.txt");
	for (int i = 0; i < i1.height(); i++) {
		for (int j = 0; j < i1.width(); j++) {
			assert(i1.at(j, i) == expected.at(j, i));
		}
	}
}

void TestDrawing() 
{
	TestDrawLine();
	TestDrawCircle();
	TestDrawRectangle1();
	TestDrawRectangle2();
}