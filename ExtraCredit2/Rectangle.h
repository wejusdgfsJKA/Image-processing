#pragma once
#include<ostream>
#include "Point.h"

using std::ostream;
class Rectangle {
public:
	Rectangle();
	Rectangle(int x, int y, int width, int height);
	int get_x() const;
	void set_x(int x);
	int get_y() const;
	void set_y(int y);
	int get_width() const;
	void set_width(int width);
	int get_height() const;
	void set_height(int height);
	bool operator==(const Rectangle& other) const;
	Rectangle& operator=(const Rectangle& other);
	Rectangle operator+(const Point& point) const;
	Rectangle operator-(const Point& point) const;
	Rectangle operator&(const Rectangle& other)const;
	Rectangle operator|(const Rectangle& other)const;
	friend ostream& operator<<(ostream& os, const Rectangle& r);

private:
	int x, y;
	int width, height;
};