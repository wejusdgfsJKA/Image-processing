#include "DrawingModule.h"
#include <exception>
#include <math.h>
#include <stdlib.h>
#include <exception>
using std::invalid_argument;
using std::pow;

void DrawingModule::drawCircle(Image& img, Point center, int radius, unsigned char color) {
	
	//set up delimiters
	int up = img.height() - (center.get_y() + radius);
	int down = img.height() - (center.get_y() - radius + 2);
	int right = center.get_x() + radius - 1;
	int left = center.get_x() - radius + 1;
	if (right >= img.width() || left < 0)throw std::invalid_argument("Invalid input!");
	if (up < 0 || down >= img.height())throw std::invalid_argument("Invalid input!");
	
	for (int i = up; i <= down; i++) {
		for (int j = left; j <= right; j++) {
			int x = sqrt(pow(abs(center.get_x() - j), 2) + pow(abs(int((img.height() - center.get_y() - 1) - i)), 2));
			if (x <= radius && radius <= x + 1)
			{
				//this point is in the circle
				img.at(j, i) = color;
			}
		}
	}
}

void DrawingModule::drawLine(Image& img, Point p1, Point p2, unsigned char color) 
{
	//set delimiters
	int x1, x2;
	if (p1.get_x() < p2.get_x()) 
	{
		x1 = p1.get_x();
		x2 = p2.get_x();
	}
	else 
	{
		x2 = p1.get_x();
		x1 = p2.get_x();
	}
	
	int y1, y2;
	if (p1.get_y() > p2.get_y()) 
	{
		y1 = img.height() - p1.get_y() - 1;
		y2 = img.height() - p2.get_y() - 1;
	}
	else
	{
		y2 = img.height() - p1.get_y() - 1;
		y1 = img.height() - p2.get_y() - 1;
	}
	
	//get equation
	if (x1 == x2) 
	{
		//straight line
		for (int i = y1; i <= y2; i++) {
			img.at(x1, i) = color;
		}
	}
	else if (y1 == y2) 
	{
		//straight line
		for (int j = x1; j <= x2; j++) {
			img.at(j, y1) = color;
		}
	}
	else
	{
		for (int i = y1; i <= y2; i++) 
		{
			for (int j = x1; j <= x2; j++) 
			{
				//check if point is on the line
				if (((j - p1.get_x()) * (p2.get_y() - p1.get_y()))/ (p2.get_x() - p1.get_x()) == (img.height() - i - p1.get_y()))
				{
					img.at(j, i) = color;
				}
			}
		}
	}
}

void DrawingModule::drawRectangle(Image& img, Rectangle r, unsigned char color) {
	
	unsigned int x = r.get_x(), y = r.get_y(), width = r.get_width(), height = r.get_height();
	if (width == 0 || height == 0)return;
	if (width < 1 || height < 1)throw invalid_argument("Invalid input!");
	if (y >= img.height() || x >= img.width())throw invalid_argument("Invalid input!");
	if (height > img.height()|| width > img.width())throw invalid_argument("Invalid input!");
	if (abs(int(y) - int(height)) > img.height() || abs(int(x) + int(width)) > img.width())throw invalid_argument("Invalid input!");
	if (img.height() - y + height - 2 >= img.height())throw invalid_argument("Invalid input!");
	x;
	for (unsigned int j = x; 
		j < x + width; 
		j++) 
	{
		img.at(j, img.height() - y - 1) = color;
		img.at(j, img.height() - y + height - 2) = color;
	}

	for (int i = img.height() - y - 1; i < img.height() - y + height - 2; i++) {
		img.at(x, i) = color;
		img.at(x + width - 1, i) = color;
	}
}

void DrawingModule::drawRectangle(Image& img, Point tl, Point br, unsigned char color) {
	
	if (br.get_x() <= tl.get_x())return;
	if (tl.get_y() <= br.get_y())return;
	if (tl.get_x() < 0 || tl.get_x() >= img.width())throw invalid_argument("Invalid input!");
	if (br.get_x() < 0 || br.get_x() >= img.width() || br.get_x() < tl.get_x())throw invalid_argument("Invalid input!");
	if (tl.get_y() >= img.height() || br.get_y() >= img.height())throw invalid_argument("Invalid input!");
	if (tl.get_y() < 0 || br.get_y() < 0)throw invalid_argument("Invalid input!");
	
	for (int i = img.height() - tl.get_y(); i < img.height() - br.get_y(); i++) {
		img.at(tl.get_x(), i) = color;
		img.at(br.get_x(), i) = color;
	}

	for (int j = tl.get_x(); j <= br.get_x(); j++) {
		img.at(j, img.height() - tl.get_y() - 1) = color;
		img.at(j, img.height() - br.get_y() - 1) = color;
	}
}