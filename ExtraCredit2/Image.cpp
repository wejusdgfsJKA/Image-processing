#include "Image.h"
#include<fstream>
#include <string>
#include<stdlib.h>
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
	string str;
	int line = 0;
	std::getline(file, str);
	if (str.compare("P2") != 0) {
		return false;
	}
	bool read_size = false;
	bool read_intensity = false;
	int new_width = 0, new_height = 0, new_intensity = 0;
	Image new_image;
	while (std::getline(file, str)) {
		if (str[0] != '#') {
			//the line is not a comment
			if (!read_size) {
				//we try to read the size
				size_t found = str.find_first_of(' ');
				if (found == string::npos ||found==0) return false;
				string w = str.substr(0, found);
				if (w.find_first_not_of("0123456789") == string::npos) {
					new_width = std::stoi(w);
				}
				else return false;
				string h = str.substr(found + 1, str.length() - 1);
				if (h.length() == 0)return false;
				if (h.find_first_not_of("0123456789") == string::npos) {
					new_height = std::stoi(h);
				}
				else return false;
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
			}
			else {
				//we now read the image
				if (str.find_first_not_of(" 0123456789") != string::npos)return false;
				for (int i = 0; i < new_width; i++) {
					size_t found = str.find_first_of(' ');
					string s = str.substr(0, found);
					if (s.length() == 0)return false;
					if (s.find_first_not_of(" 0123456789") != string::npos)return false;
					int a = std::stoi(s);
					if (a > new_intensity)return false;
					new_image.at(i, line) = a;
					int j = found;
					if (j >= str.length()) str = "";
					else
					str = str.substr(j + 1, str.length());
				}
				line++;
			}
		}
	}
	if (!read_size || !read_intensity)return false;
	if (line < new_height)return false;
	*this = new_image;
	return true;
}

bool Image::save(string imagePath) const {
	if (imagePath.length() == 0)return false;
	std::ofstream file(imagePath);
	file << "P2\n" << m_width << " " << m_height << "\n255";
	if (m_width > 0)
	{
		for (int i = 0; i < m_height; i++) {
			file << "\n";
			file << int(m_data[i][0]);
			for (int j = 1; j < m_width; j++) {
				file << " " << int(m_data[i][j]);
			}
		}
	}
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
	unsigned int x = roiRect.get_x(), y = roiRect.get_y(), width = roiRect.get_width(), height = roiRect.get_height();
	if (width < 1 || height < 1)return false;
	if (y >= m_height || x >= m_width)return false;
	if (height > m_height || width > m_width)return false;
	if (abs(int(y) - int(height)) > m_height || abs(int(x) - int(width)) > m_width)return false;
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
	if (width < 1 || height < 1)return false;
	if (y >= m_height || x >= m_width)return false;
	if (height > m_height || width > m_width)return false;
	if (abs(int(y) - int(height)) > m_height || abs(int(x) - int(width)) > m_width)return false;
	roiImg = Image(width, height);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int a = i + abs(int(x) - int(m_height))-1;
			roiImg.at(j, i) = int(m_data[i + abs(int(y) - int(m_height))-1][j + x]);
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