#pragma once

class Size {

public:

	Size();
	Size(unsigned int width, unsigned int height);
	unsigned int get_width() const;
	unsigned int get_height() const;
	void set_width(unsigned int width);
	void set_height(unsigned int height);
	friend bool operator==(const Size& s1, const Size& s2);
	friend bool operator<=(const Size& s1, const Size& s2);
	friend bool operator<(const Size& s1, const Size& s2);
	friend bool operator>=(const Size& s1, const Size& s2);
	friend bool operator>(const Size& s1, const Size& s2);

private:
	unsigned int width, height;
};