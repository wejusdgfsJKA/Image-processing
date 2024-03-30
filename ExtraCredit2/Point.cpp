#include "Point.h"

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

int Point::get_x() const {
	return x;
}

int Point::get_y() const {
	return y;
}

void Point::set_x(int x) {
	this->x = x;
}

void Point::set_y(int y) {
	this->y = y;
}