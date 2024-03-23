#include "Rectangle.h"
#include<algorithm>
Rectangle::Rectangle() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}
Rectangle::Rectangle(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	if (height >= 0)
		this->height = height;
	else
		this->height = 0;
	if (width >= 0)
		this->width = width;
	else
		this->width = 0;
}
int Rectangle::get_x() const {
	return x;
}
void Rectangle::set_x(int x) {
	this->x = x;
}
int Rectangle::get_y() const {
	return y;
}
void Rectangle::set_y(int y) {
	this->y = y;
}
int Rectangle::get_width() const {
	return width;
}
void Rectangle::set_width(int width) {
	if (width >= 0)
		this->width = width;
	else
		this->width = 0;
}
int Rectangle::get_height() const {
	return height;
}
void Rectangle::set_height(int height) {
	if (height >= 0)
		this->height = height;
	else
		this->height = 0;
}
bool Rectangle::operator==(const Rectangle& other) const {
	return (this->x == other.x && this->y == other.y && this->width == other.width && this->height == other.height);
}
Rectangle Rectangle::operator+(const Point& point) const {
	return Rectangle(this->x+point.get_x(), this->y + point.get_y(), width, height);
}
Rectangle Rectangle::operator-(const Point& point) const {
	return Rectangle(x - point.get_x(), y - point.get_y(), width, height);
}
Rectangle Rectangle::operator&(const Rectangle& other) const{
	int new_x = std::max(this->x, other.x);
	int new_y = std::min(this->y, other.y);
	int new_width = std::min(x + width - new_x, other.x + other.width - new_x);
	int new_height = std::min(new_y - y + height, new_y - other.y + other.height);
	return Rectangle(new_x, new_y, new_width, new_height);
}
Rectangle Rectangle::operator|(const Rectangle& other) const{
	int new_x = std::min(this->x, other.x);
	int new_y = std::max(this->y, other.y);
	int x2 = std::max(this->x + this->width, other.x + other.width);
	int y2 = std::min(this->y - this->height, other.y - other.height);
	//unsigned int new_width = width + other.get_width() - std::min(x + width - new_x, other.get_x() + other.get_width() - new_x);
	//unsigned int new_height = height + other.get_height() - std::min(new_y - y + height, new_y - other.get_y() + other.get_height());
	return Rectangle(new_x, new_y, x2 - new_x, new_y - y2);
}
Rectangle& Rectangle::operator=(const Rectangle& other) {
	this->x = other.x;
	this->y = other.y;
	this->width = other.width;
	this->height = other.height;
	return *this;
}
ostream& operator<<(ostream& os, const Rectangle& r) {
	os << r.x << " " << r.y << " " << r.width << " " << r.height;
	return os;
}