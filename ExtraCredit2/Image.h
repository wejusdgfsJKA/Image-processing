#pragma once
#include <ostream>
#include "Rectangle.h"
#include "Size.h"
class Image
{
public:
	Image();
	Image(unsigned int w, unsigned int h);
	Image(const Image& other);
	Image& operator=(const Image& other);
	~Image();
	bool load(std::string imagePath);
	bool save(std::string imagePath) const;
	Image operator+(const Image& i);
	Image operator-(const Image& i);
	Image operator*(double s);
	bool getROI(Image& roiImg, Rectangle roiRect);
	bool getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	bool isEmpty() const;
	Size size() const;
	unsigned int width() const;
	unsigned int height() const;
	unsigned char& at(unsigned int x, unsigned int y);
	unsigned char& at(Point pt);
	unsigned char* row(int y);
	void release();
	friend std::ostream& operator<<(std::ostream& os, const Image& dt);
	friend std::istream& operator>>(std::istream& is, Image& dt);
	static Image zeros(unsigned int width, unsigned int height);
	static Image ones(unsigned int width, unsigned int height);
	unsigned char** m_data;
private:
	
	unsigned int m_width;
	unsigned int m_height;
};