#include "Image.h"
#include<fstream>
#include <string>
#include<stdlib.h>
#include <iostream>
using std::string;
using std::cout;
Image Image::zeros(unsigned int width, unsigned int height) {
	return Image(width, height);
}

Image Image::ones(unsigned int width, unsigned int height) {
	Image img = Image(width, height);
	for (int i = 0; i < img.m_height; i++) {
		for (int j = 0; j < img.m_width; j++) {
			img.m_data[i][j] = 1;
		}
	}
	return img;
}

Image::Image() {
	m_data = nullptr;
	m_width = 0;
	m_height = 0;
}

Image::Image(unsigned int w,unsigned int h) {
	m_width = w;
	m_height = h;
	m_data = new unsigned char* [m_height * sizeof(unsigned char*)];
	for (int i = 0; i < m_height; i++) {
		m_data[i] = new unsigned char[m_width * sizeof(unsigned char)];
		for (int j = 0; j < m_width; j++) {
			m_data[i][j] = 0;
		}
	}
}

Image::Image(const Image& other) {
	m_width = other.m_width;
	m_height = other.m_height;
	m_data = new unsigned char* [m_height * sizeof(unsigned char*)];
	for (int i = 0; i < m_height; i++) {
		m_data[i] = new unsigned char[m_width * sizeof(unsigned char)];
		for (int j = 0; j < m_width; j++) {
			m_data[i][j] = other.m_data[i][j];
		}
	}
}

Image& Image::operator=(const Image& other) {
	release();
	m_width = other.m_width;
	m_height = other.m_height;
	m_data = new unsigned char* [m_height * sizeof(unsigned char*)];
	for (int i = 0; i < m_height; i++) {
		m_data[i] = new unsigned char[m_width * sizeof(unsigned char)];
		for (int j = 0; j < m_width; j++) {
			m_data[i][j] = other.m_data[i][j];
		}
	}
	return *this;
}

Image::~Image() {
	release();
}

bool Image::load(string imagePath) {
	
	if (imagePath.length() == 0)return false;
	std::ifstream file(imagePath);
	if (!file.is_open())return false;
	string str;
	std::getline(file, str);

	if (str.compare("P2") != 0) {
		return false;
	}

	bool read_size = false;
	bool read_intensity = false;

	int new_width = 0, new_height = 0, new_intensity = 0;
	Image new_image;
	int line = 0;
	int c = 0;

	while (std::getline(file, str)) {
		if (str[0] != '#') {
			//the line is not a comment
			if (!read_size) {
				//we try to read the size
				int i = 0;
				int counter = 0;
				while (i < str.length()) {
					if (!isdigit(str[i]) && str[i] != ' ')return false;
					if (isdigit(str[i]) && (i == 0 || !isdigit(str[i - 1]))) {
						//found a nr
						counter++;
						if (counter > 2)return false;
						int j = i;
						while (j < str.length() && isdigit(str[j]))j++;
						if (counter == 1) {
							new_width = std::stoi(str.substr(i, j - i));
						}
						else {
							new_height = std::stoi(str.substr(i, j - i));
						}
						i = j + 1;
					}
					else i++;
				}
				read_size = true;
			}
			else if (!read_intensity) {
				//we try to read the intensity
				if (str.find_first_not_of("0123456789") == string::npos) {
					new_intensity = std::stoi(str);
				}
				else return false;
				read_intensity = true;
				new_image = Image(new_width, new_height);
				int a = 0;
			}
			else {
				//we now read the image
				if (line < new_height)
				{
					int i = 0;
					while (i < str.length()) {
						if (!isdigit(str[i]) && str[i] != ' ')return false;
						if (isdigit(str[i]) && (i == 0 || !isdigit(str[i - 1]))) {
							//found a nr
							int j = i;
							while (j < str.length() && isdigit(str[j]))j++;
							if (j != i)
							{
								int a = std::stoi(str.substr(i, j - i)); int L = line; int C = c;
								if (a > new_intensity)return false;
								new_image.at(c, line) = a;
								c++;
								if (c == new_width) {
									line++;
									c = 0;
								}
							}
							i = j + 1;
						}
						else i++;
					}
				}
			}
		}
	}
	if (!read_size || !read_intensity)return false;
	*this = new_image;
	file.close();
	return true;
}

bool Image::save(string imagePath) const {
	if (imagePath.length() == 0)return false;
	std::ofstream file(imagePath);
	if (!file.is_open())return false;
	file << *this;
	file.close();
	return true;
}

Image Image::operator+(const Image& i) {
	if (this->m_width != i.m_width || this->m_height != i.m_height)throw("Different sized images!");
	Image img(m_width, m_height);
	for (int p = 0; p < m_height; p++) {
		for (int j = 0; j < m_width; j++) {
			img.m_data[p][j] = this->m_data[p][j] + i.m_data[p][j];
		}
	}
	return img;
}

Image Image::operator-(const Image& i) {
	if (this->m_width != i.m_width || this->m_height != i.m_height)throw("Different sized images!");
	Image img(m_width, m_height);
	for (int p = 0; p < m_height; p++) {
		for (int j = 0; j < m_width; j++) {
			img.m_data[p][j] = this->m_data[p][j] - i.m_data[p][j];
		}
	}
	return img;
}

Image Image::operator*(double s) {
	Image img(m_width, m_height);
	for (int p = 0; p < m_height; p++) {
		for (int j = 0; j < m_width; j++) {
			img.m_data[p][j] = this->m_data[p][j] * s;
		}
	}
	return img;
}

bool Image::getROI(Image& roiImg, Rectangle roiRect) {
	
	if (roiRect.get_width() == 0 || roiRect.get_height() == 0) {
		roiImg = Image();
		return true;
	}

	unsigned int x = roiRect.get_x(), y = roiRect.get_y(), width = roiRect.get_width(), height = roiRect.get_height();
	if (width < 1 || height < 1)return false;
	if (y >= m_height || x >= m_width)return false;
	if (height > m_height || width > m_width)return false;
	if (abs(int(y) - int(height)) > m_height || abs(int(x) + int(width)) > m_width)return false;
	
	roiImg = Image(width, height);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int a = i + abs(int(x) - int(m_height)) - 1;
			roiImg.at(j, i) = int(m_data[i + abs(int(y) - int(m_height)) - 1][j + x]);
		}
	}
	return true;
}

bool Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	
	if (width == 0 or height == 0) {
		roiImg = Image();
		return true;
	}

	if (width < 1 || height < 1)return false;
	if (y >= m_height || x >= m_width)return false;
	if (height > m_height || width > m_width)return false;
	if (abs(int(y) - int(height)) > m_height || abs(int(x) + int(width)) > m_width)return false;
	if (m_height - y + height - 2 > m_height)return false;
	roiImg = Image(width, height);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int I = i + abs(int(y) - int(m_height)) - 1;
			int Y = j + x;
			int a = int(m_data[i + abs(int(y) - int(m_height)) - 1][j + x]);
			roiImg.at(j, i) = a;
		}
	}
	return true;
}

bool Image::isEmpty() const{
	return (m_data == nullptr && m_height == 0 && m_width == 0);
}

Size Image::size() const{
	return Size(m_width, m_height);
}

unsigned int Image::width() const {
	return m_width;
}

unsigned int Image::height() const {
	return m_height;
}

unsigned char& Image::at(unsigned int x, unsigned int y) {
	return m_data[y][x];
}

unsigned char& Image::at(Point pt) {
	return m_data[pt.get_y()][pt.get_x()];
}

unsigned char* Image::row(int y) {
	return m_data[y];
}

void Image::release() {
	if (m_data)
	{
		for (int i = 0; i < m_height; i++) {
			if (m_data[i])
				delete[] m_data[i];
		}
		delete[] m_data;
	}
}

std::ostream& operator<<(std::ostream& os, const Image& dt) {
	os << "P2\n" << dt.m_width << " " << dt.m_height << "\n255";
	for (int i = 0; i < dt.m_height; i++) {
		os << "\n";
		for (int j = 0; j < dt.m_width; j++) {
			os << int(dt.m_data[i][j]) << " ";
		}
	}
	os << "\n";
	return os;
}

std::istream& operator>>(std::istream& is, Image& dt) {
	int maxsize;
	is >> dt.m_width >> dt.m_height >> maxsize;
	dt = Image(dt.m_width, dt.m_height);
	for (int i = 0; i < dt.m_height; i++) {
		for (int j = 0; j < dt.m_width; j++) {
			int a;
			is >> a;
			if (a > maxsize) {
				throw("Pixel value too large!");
			}
			dt.m_data[i][j] = unsigned char(a);
		}
	}
	return is;
}