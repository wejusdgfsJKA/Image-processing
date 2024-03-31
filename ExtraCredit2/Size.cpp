#include "Size.h"

Size::Size() {
	width = 0;
	height = 0;
}

Size::Size(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
}

unsigned int Size::get_width() const {
	return width;
}

unsigned int Size::get_height() const {
	return height;
}

void Size::set_width(unsigned int width) {
	this->width = width;
}

void Size::set_height(unsigned int height) {
	this->height = height;
}

bool operator==(const Size& s1, const Size& s2) {
	return (s1.width == s2.width && s1.height == s2.height);
}

bool operator<=(const Size& s1, const Size& s2) {
	return (s1.width * s1.height <= s2.height * s2.width);
}

bool operator<(const Size& s1, const Size& s2) {
	return (s1.width * s1.height < s2.height * s2.width);
}

bool operator>=(const Size& s1, const Size& s2) {
	return (s1.width * s1.height >= s2.height * s2.width);
}

bool operator>(const Size& s1, const Size& s2) {
	return (s1.width * s1.height > s2.height * s2.width);
}